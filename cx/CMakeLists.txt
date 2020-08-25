# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
#export CC=C:/msys32/mingw32/bin/gcc
#export CXX=C:/msys32/mingw32/bin/g++
SET(CMAKE_C_COMPILER "C:/msys32/mingw32/bin/clang.exe")

SET(CMAKE_CXX_COMPILER "C:/msys32/mingw32/bin/clang++.exe")

PROJECT (Demo4)
aux_source_directory(. DIR_SRCS)
# 指定生成目标
add_executable(Demo ${DIR_SRCS})


