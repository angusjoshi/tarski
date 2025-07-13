#include "analysis/runAnalysis.h"
#include "contraction/OddEven.h"
#include <iostream>
#include "simple-stochatic-game/simpleContractionSolver.h"
#include "simple-stochatic-game/simpleStochasticGameGenerator.h"
#include "fixpoint/kleeneTarski.h"
#include "fixpoint/latticeUtil.h"

int main() {
//    simpleStochasticGame g = generateSimpleStochasticGame(6, 0.1);
    auto g = getLongExample(5, 0.1);
//    auto bot = g.getBot();
//    auto fixpoint = kleeneTarski(bot, g.getMonotoneFunction());
//    printVec(fixpoint);
    auto res = simpleContractionSolve(g);

    return 0;
    cout << "hello!\n";

//     runAndPrintAnalysis();

}


