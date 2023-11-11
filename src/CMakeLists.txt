cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

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
        threeDimensionAlgorithm.cpp
        threeDimensionAlgorithm.h
        fixDecompAlgorithm.cpp
        fixDecompAlgorithm.h
        recursiveBinarySearch.cpp
        recursiveBinarySearch.h
)

