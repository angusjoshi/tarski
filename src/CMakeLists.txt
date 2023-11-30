cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG        v1.14.0
#)
#
#FetchContent_MakeAvailable(googletest)

add_executable(src main.cpp
        fixpoint/examples.h
        fixpoint/innerAlgorithm.h
        fixpoint/innerAlgorithm.cpp
        fixpoint/kleeneTarski.h
        fixpoint/kleeneTarski.cpp
        fixpoint/latticeUtil.cpp
        fixpoint/latticeUtil.h
        fixpoint/monotoneFunction.cpp
        fixpoint/monotoneFunction.h
        fixpoint/threeDimensionAlgorithm.cpp
        fixpoint/threeDimensionAlgorithm.h
        fixpoint/fixDecompAlgorithm.cpp
        fixpoint/fixDecompAlgorithm.h
        fixpoint/recursiveBinarySearch.cpp
        fixpoint/recursiveBinarySearch.h
        arrival/preprocessInstance.cpp
        arrival/preprocessInstance.h
        arrival/examples.h
        arrival/generateRandomInstance.cpp
        arrival/generateRandomInstance.h
        arrival/arrivalUtil.cpp
        arrival/arrivalUtil.h
        arrival/simpleWalk.cpp
        arrival/simpleWalk.h
        arrival/arrivalInstance.cpp
        arrival/arrivalInstance.h
)

