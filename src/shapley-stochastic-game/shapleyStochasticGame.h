//
// Created by angus on 03/03/2024.
//

#ifndef SRC_SHAPLEYSTOCHASTICGAME_H
#define SRC_SHAPLEYSTOCHASTICGAME_H

#include <vector>
#include "../config.h"

#define EPSILON 0.001

using namespace std;

struct shapleySuccessor {
    int i;
    f_t p;
};

struct shapleyVertex {
    // successor indexing is assumed to be the same as in the vertex vector
    // as in etessami et al., the probabilities are assumed to sum to strictly < 1.
    vector<vector<vector<shapleySuccessor>>> succs;
    vector<vector<int>> payoffs;
};

struct shapleyStochasticGame {
    vector<shapleyVertex> vertices;
    function<vector<int_t>(const vector<int_t>& v)> getMonotoneFunction();
    vector<int_t> getBot();
    vector<int_t> getTop();
    shapleyStochasticGame(vector<shapleyVertex> vertices);
    vector<f_t> scaleDown(const vector<int_t>& v);
    vector<int_t> scaleUp(const vector<f_t>& v);

private:
    int_t N;
    f_t scale;
};

f_t getZeroSumVal(const vector<vector<f_t>>& payoffMatrix);

#endif //SRC_SHAPLEYSTOCHASTICGAME_H
