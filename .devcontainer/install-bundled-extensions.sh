#!/bin/bash
# ============================================================
# 把镜像里预装的扩展(/vscode-extensions/)链接到 VS Code Server，
# 并更新 extensions.json 注册表，让 VS Code 识别。
#
# 这样 cpptools 等大扩展可以离线预装进镜像，避免每次创建容器都从
# 国内 Marketplace 下载超时。
# ============================================================
set -e

DEST_DIR="${HOME}/.vscode-server/extensions"
REG_FILE="${DEST_DIR}/extensions.json"

mkdir -p "$DEST_DIR"

# 如果没有 extensions.json，创建空数组
if [ ! -f "$REG_FILE" ]; then
    echo "[]" > "$REG_FILE"
fi

# 如果镜像里没有预装扩展目录，直接退出
if [ ! -d "/vscode-extensions" ] || [ -z "$(ls -A /vscode-extensions 2>/dev/null)" ]; then
    echo "(镜像未预装扩展，跳过)"
    exit 0
fi

# 用 python 更新 extensions.json（避免依赖 jq）
python3 <<'PYEOF'
import json, os, glob

dest = os.path.expanduser("~/.vscode-server/extensions")
reg_path = os.path.join(dest, "extensions.json")

# 读现有注册表
try:
    with open(reg_path) as f:
        registry = json.load(f)
except Exception:
    registry = []

existing_ids = {e.get("identifier", {}).get("id", "").lower() for e in registry}

# 扫描预装目录
for ext_dir in sorted(glob.glob("/vscode-extensions/*")):
    if not os.path.isdir(ext_dir):
        continue
    pkg_path = os.path.join(ext_dir, "package.json")
    if not os.path.exists(pkg_path):
        continue
    with open(pkg_path) as f:
        pkg = json.load(f)
    pub = pkg.get("publisher", "")
    name = pkg.get("name", "")
    version = pkg.get("version", "")
    ext_id = f"{pub}.{name}"
    dirname = os.path.basename(ext_dir)

    # 链接到 vscode-server/extensions
    link_path = os.path.join(dest, dirname)
    if not os.path.exists(link_path):
        os.symlink(ext_dir, link_path)
        print(f"✅ 链接: {ext_id} v{version}")

    # 更新注册表（避免重复）
    if ext_id.lower() not in existing_ids:
        registry.append({
            "identifier": {"id": ext_id},
            "version": version,
            "location": {"path": link_path},
            "relativeLocation": f"extensions/{dirname}",
            "metadata": {"installedTimestamp": 0, "targetPlatform": "linux-x64"},
            "targetPlatform": "linux-x64"
        })
        existing_ids.add(ext_id.lower())

with open(reg_path, "w") as f:
    json.dump(registry, f, indent=2)

print(f"注册表共 {len(registry)} 个扩展")
PYEOF

echo "扩展安装完成"
