cmake_minimum_required(VERSION 3.10)

# 项目名称
project(ObserverPattern)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加可执行文件
add_executable(Observer Observer.cpp)

# 如果需要链接额外的库，可以在这里添加
# target_link_libraries(Observer ...)