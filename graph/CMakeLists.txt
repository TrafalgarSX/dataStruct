# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
#同一目录，多个源文件
# 项目信息
project (fuckcmake)

# 指定生成目标
#add_executable(hello graph.cpp function.cpp) 可以这样写，但是.cpp多了没法弄
aux_source_directory(. DIR_SRCS)# aux_source_directory(<dir> <variable>)
add_executable(graph ${DIR_SRCS})