cmake_minimum_required(VERSION 3.21)

# ============================================================
# 项目名称
# ============================================================
project(CppExamples
    VERSION 1.0.0
    DESCRIPTION "C++ 学习示例项目"
    LANGUAGES CXX
)

# ============================================================
# C++ 标准（也可通过 CMakePresets.json 覆盖）
# ============================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================
# 通用编译选项
# ============================================================
if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# ============================================================
# 根目录示例程序（每个 .cpp 独立编译为可执行文件）
# ============================================================
file(GLOB root_sources "*.cpp")
foreach(source ${root_sources})
    get_filename_component(target_name ${source} NAME_WE)
    add_executable(${target_name} ${source})
endforeach()

# ============================================================
# 设计模式示例
# ============================================================
# 独立 .cpp 文件（如 singleto.cpp）
file(GLOB dp_standalone
    "design pattern/*.cpp"
)
foreach(source ${dp_standalone})
    get_filename_component(target_name ${source} NAME_WE)
    add_executable(${target_name} ${source})
endforeach()

# 包含子目录（如 1.Observer 有自己的 CMakeLists.txt）
add_subdirectory("design pattern/1.Observer")