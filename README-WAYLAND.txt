==================================================================
  换电脑/新机器配置 Dev Container 必读：关闭 Wayland 挂载
==================================================================

【问题】
Dev Containers 扩展默认会自动把宿主机的 Wayland socket 挂进容器。
如果某台电脑没有 WSLg（如 WSL 版本旧/未启用、或纯 Linux 宿主机），
这个挂载会找不到源 socket 文件，导致容器启动失败。

【为什么 devcontainer.json 里不能配】
dev.containers.mountWaylandSocket 是 VS Code【用户设置】(application 级)，
不是容器级配置。devcontainer.json 只能覆盖 machine/window 级设置，
挡不住这个挂载动作。containerEnv 设 DISPLAY/WAYLAND_DISPLAY 也无效，
因为那只清空容器内的环境变量，不影响挂载操作。

【每台电脑各做一次】
方法1（推荐，图形界面）：
  VS Code → Ctrl+, 打开设置 → 搜 "mountWaylandSocket"
  → 取消勾选 "Dev > Containers: Mount Wayland Socket"

方法2（直接编辑用户 settings.json）：
  Windows: %APPDATA%\Code\User\settings.json
  Linux:   ~/.config/Code/User/settings.json
  Mac:     ~/Library/Application Support/Code/User/settings.json

  在 JSON 里加一行：
    "dev.containers.mountWaylandSocket": false

【配完后】
Rebuild Container，容器就能正常启动，不再依赖 Wayland socket。
本项目是纯命令行 C++ 开发，不需要图形显示，关掉它没有任何影响。
