cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(GMP_DIR "/opt/homebrew/Cellar/gmp/6.3.0")
set(GMPXX_LIBRARIES "/opt/homebrew/Cellar/gmp/6.3.0/lib/libgmpxx.a")
set(GMP_LIBRARIES "/opt/homebrew/Cellar/gmp/6.3.0/lib/libgmp.a")
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

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GMP_DIR})
include_directories(${SOPLEX_DIR})

add_library(arrival
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
)

add_library(fixpoint
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
        fixpoint/monotoneDecompAlgorithm.cpp
        fixpoint/monotoneDecompAlgorithm.h
        fixpoint/findFixpointByMonotoneDecomp.cpp
        fixpoint/findFixpointByMonotoneDecomp.h
        fixpoint/valueIteration.h
        fixpoint/valueIteration.cpp
)
add_library(analysis
        analysis/runAnalysis.cpp
        analysis/runAnalysis.h
)
add_library(shapley-stochastic-game
        shapley-stochastic-game/shapleyStochasticGame.cpp
        shapley-stochastic-game/shapleyStochasticGame.h
        shapley-stochastic-game/shapleyStochasticGameGenerator.cpp
        shapley-stochastic-game/shapleyStochasticGameGenerator.h
)
add_library(simple-stochatic-game
        simple-stochatic-game/simpleStochasticGameGenerator.cpp
        simple-stochatic-game/simpleStochasticGameGenerator.h
        simple-stochatic-game/simpleStochasticGame.cpp
        simple-stochatic-game/simpleStochasticGame.h
        simple-stochatic-game/simpleStochasticGame.h
        simple-stochatic-game/simpleStochasticGame.h
        simple-stochatic-game/strategyImprovement.cpp
        simple-stochatic-game/strategyImprovement.h
)

add_executable(src main.cpp
        config.h
        config.cpp
)

target_link_libraries(src arrival
        fixpoint
        simple-stochatic-game
        shapley-stochastic-game
        analysis
)


target_link_libraries(src ${GMP_LIBRARIES})
target_link_libraries(src ${GMPXX_LIBRARIES})
target_link_libraries(src ${GLPK_LIB})
target_link_libraries(src ${Boost_LIBRARIES})
target_link_libraries(src ${SOPLEX_LIB})
target_link_libraries(src ${SOPLEX_LIB2})
target_link_libraries(src ${SOPLEX_LIB3})
