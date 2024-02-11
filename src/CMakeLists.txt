cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(GMP_DIR "/opt/homebrew/Cellar/gmp/6.3.0")

#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG        v1.14.0
#)
#
#FetchContent_MakeAvailable(googletest)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.84.0 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GMP_DIR})
add_executable(src main.cpp
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
        arrival/generateInstance.cpp
        arrival/generateInstance.h
        arrival/arrivalUtil.cpp
        arrival/arrivalUtil.h
        arrival/simpleWalk.cpp
        arrival/simpleWalk.h
        arrival/arrivalInstance.cpp
        arrival/arrivalInstance.h
        analysis/runAnalysis.cpp
        analysis/runAnalysis.h
        fixpoint/monotoneDecompAlgorithm.cpp
        fixpoint/monotoneDecompAlgorithm.h
        fixpoint/findFixpointByMonotoneDecomp.cpp
        fixpoint/findFixpointByMonotoneDecomp.h
        simple-stochatic-game/simpleStochasticGame.cpp
        simple-stochatic-game/simpleStochasticGame.h
        simple-stochatic-game/simpleStochasticGame.h
        simple-stochatic-game/simpleStochasticGame.h
        config.h
)

target_link_libraries(src ${Boost_LIBRARIES})
