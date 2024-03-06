#include "analysis/runAnalysis.h"
#include <soplex.h>
#include <soplex/gzstream.h>
#include "shapley-stochastic-game/shapleyStochasticGame.h"
#include <glpk.h>

using namespace std;
using namespace soplex;


int main() {
//    f_t x = 0.65;
//    int_t sum = 0;
//    int_t y = 20;
//    sum += y * x;
//
//    cout << "sum is: " << sum;

    vector<vector<f_t>> rockPaperScissors {
        {0, 1, -1},
        {-1, 0, 1},
        {1, -1, 0},
    };

    vector<vector<f_t>> example2 {
        {1, 2, 3},
        {-1, -2, 5},
        {8, -6, 2},
        {-2, -3, 10},
    };

    auto x = getZeroSumVal(rockPaperScissors);
    auto y = getZeroSumVal(example2);

    runAndPrintAnalysis();
    return 0;
}


