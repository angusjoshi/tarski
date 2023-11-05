cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 23)

add_executable(src main.cpp
        examples.h
        innerAlgorithm.h
        innerAlgorithm.cpp
        kleeneTarski.h
        kleeneTarski.cpp
        latticeUtil.cpp
        latticeUtil.h
        monotoneFunction.cpp
        monotoneFunction.h
)
