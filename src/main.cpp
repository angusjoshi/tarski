#include "analysis/runAnalysis.h"
#include <soplex.h>
#include <soplex/gzstream.h>
#include "shapley-stochastic-game/shapleyStochasticGame.h"
#include <glpk.h>

#include "simple-stochatic-game/simpleStochasticGameGenerator.h"

using namespace std;
using namespace soplex;


int main() {
//    f_t x = 0.65;
//    int_t sum = 0;
//    int_t y = 20;
//    sum += y * x;
//
//    cout << "sum is: " << sum;

//    vector<vector<f_t>> rockPaperScissors {
//        {0, 1, -1},
//        {-1, 0, 1},
//        {1, -1, 0},
//    };
//
//    vector<vector<f_t>> example2 {
//        {1, 2, 3},
//        {-1, -2, 5},
//        {8, -6, 2},
//        {-2, -3, 10},
//    };
//
//    vector<vector<f_t>> example3 {
//        {1, -2, 3},
//        {-1, 2, 1},
//        {4, -5, 2},
//    };
//
//    auto x = getZeroSumVal(rockPaperScissors);
//    auto y = getZeroSumVal(example2);
//    auto z = getZeroSumVal(example3);
//
    runAndPrintAnalysis();

    return 0;
}


