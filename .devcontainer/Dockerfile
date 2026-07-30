# ============================================================
# Dev Container 基础镜像
# Ubuntu 24.04 LTS + C++ 开发工具链
# ============================================================
FROM ubuntu:24.04

# 避免交互式安装提示
ENV DEBIAN_FRONTEND=noninteractive

# ============================================================
# 替换为清华大学 Ubuntu 镜像源（国内加速）
# ============================================================
RUN sed -i 's@//.*archive.ubuntu.com@//mirrors.tuna.tsinghua.edu.cn@g' /etc/apt/sources.list.d/ubuntu.sources

# ============================================================
# 安装 C++ 工具链
# ============================================================
RUN apt-get update && apt-get install -y --no-install-recommends \
    # 编译器
    g++-14 \
    gdb \
    # 构建工具
    cmake \
    ninja-build \
    make \
    # 代码质量
    clang-format \
    clang-tidy \
    # 版本控制
    git \
    # 其他工具
    ca-certificates \
    curl \
    wget \
    && rm -rf /var/lib/apt/lists/*

# .NET 下载超时延长（国内网络慢）
ENV DOTNET_INSTALL_TIMEOUT=600

# 设置 g++-14 为默认编译器
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 100 \
    && update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-14 100

# ============================================================
# 设置工作目录
# ============================================================
WORKDIR /workspaces/Cpp

# 重置环境变量
ENV DEBIAN_FRONTEND=

# ============================================================
# 彻底禁用 debuginfod（国内 debuginfod.ubuntu.com 不可达，会导致
# gdb 在 MI 模式下运行程序时联网下载 libstdc++ 等调试符号，TCP 连上
# 但服务器不返回数据 → gdb 永久等待 → VS Code 调试一直转圈）。
#
# 三层防御，缺一不可：
# ============================================================

# 1) 清空 elfutils 的默认 URL 列表（libdebuginfod-common 包提供，原本含
#    https://debuginfod.ubuntu.com）。当 DEBUGINFOD_URLS 环境变量为空时，
#    elfutils 会回退读取此文件作为默认 URL，所以必须清空。
RUN : > /etc/debuginfod/elfutils.urls

# 2) 在 gdb 系统级初始化文件里关闭 debuginfod
RUN echo "set debuginfod enabled off" >> /etc/gdb/gdbinit

# 3) 环境变量层面也清空（Dockerfile 层；VS Code 会话由 devcontainer.json
#    的 remoteEnv 再覆盖一次，确保派生的 gdb 进程也拿到空值）
ENV DEBUGINFOD_URLS=""
ENV DEBUGINFOD_CACHE_DIR=""
