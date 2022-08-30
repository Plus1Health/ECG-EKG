# CMakeList.txt: TinewServer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.10)

project ("ECGReader")

#add_definitions("/MP")


# require C++17
set(CMAKE_CXX_STANDARD 17)

 set(CMAKE_CXX_STANDARD_REQUIRED ON)

 #set(CMAKE_CXX_EXTENSIONS OFF)

#SET(CMAKE_CXX_COMPILER "g++")

add_definitions("-Wall -g -fPIC")

# 将源代码添加到此项目的可执行文件。
add_executable (ECGReader "ECGReader.cpp")