cmake_minimum_required(VERSION 3.0)
project(main)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 添加子目录
add_subdirectory(src)
include_directories(include)
# 指定生成目标 
add_executable(${PROJECT_NAME} ${DIR_SRCS})
# 添加链接库
target_link_libraries(${PROJECT_NAME} Src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -ggdb -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall")