cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(GMP_DIR "/opt/homebrew/Cellar/gmp/6.3.0")

set(GMPXX_LIBRARIES "/opt/homebrew/Cellar/gmp/6.3.0/lib/libgmpxx.a")
set(GMP_LIBRARIES "/opt/homebrew/Cellar/gmp/6.3.0/lib/libgmp.a")

set(GLPK_DIR "/opt/homebrew/Cellar/glpk/5.0")
set(GLPK_LIB "/opt/homebrew/Cellar/glpk/5.0/lib/libglpk.a")

set(OR_DIR "/opt/homebrew/Cellar/or-tools/9.8_3")
set(OR_LIB "/opt/homebrew/Cellar/or-tools/9.8_3/lib/libortools.9.8.dylib")

set (SCIP_LIB "/opt/homebrew/Cellar/scip/9.0.0/lib/libscip.9.0.0.0.dylib")
set(SCIP_DIR "/opt/homebrew/Cellar/scip/9.0.0")

set(SOPLEX_LIB "/opt/homebrew/Cellar/soplex/7.0.0.0/lib/libsoplexshared.7.0.0.0.dylib")
set(SOPLEX_LIB2 "/opt/homebrew/Cellar/soplex/7.0.0.0/lib/libsoplex-pic.a")
set(SOPLEX_LIB3 "/opt/homebrew/Cellar/soplex/7.0.0.0/lib/libsoplex.a")

set(SOPLEX_DIR "/opt/homebrew/Cellar/soplex/7.0.0.0")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.84.0 REQUIRED)
find_package(ortools CONFIG REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GMP_DIR})
include_directories(${SOPLEX_DIR})
#include_directories(${GLPK_DIR})
#include_directories(${OR_DIR})
#include_directories(${SCIP_DIR})

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
        config.cpp
        simple-stochatic-game/simpleStochasticGameGenerator.cpp
        simple-stochatic-game/simpleStochasticGameGenerator.h
        shapley-stochastic-game/shapleyStochasticGame.cpp
        shapley-stochastic-game/shapleyStochasticGame.h
        shapley-stochastic-game/shapleyStochasticGameGenerator.cpp
        shapley-stochastic-game/shapleyStochasticGameGenerator.h
        simple-stochatic-game/valueIteration.h
        simple-stochatic-game/valueIteration.cpp
        simple-stochatic-game/strategyImprovement.cpp
        simple-stochatic-game/strategyImprovement.h
)


target_link_libraries(src ${GMP_LIBRARIES})
target_link_libraries(src ${GMPXX_LIBRARIES})
target_link_libraries(src ${GLPK_LIB})
target_link_libraries(src ${Boost_LIBRARIES})

target_link_libraries(src ${SOPLEX_LIB})
target_link_libraries(src ${SOPLEX_LIB2})
target_link_libraries(src ${SOPLEX_LIB3})
#target_link_libraries(src ${OR_LIB})
#target_link_libraries(src ${SCIP_LIB})
