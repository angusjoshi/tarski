//
// Created by angus on 03/03/2024.
//

#ifndef SRC_SHAPLEYSTOCHASTICGAME_H
#define SRC_SHAPLEYSTOCHASTICGAME_H

#include <vector>
#include "../config.h"

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
    function<vector<f_t>(const vector<f_t>& v)> getCtsMonotoneFunction();
    const vector<f_t> getCtsStart();
    const vector<f_t> computeFunction(const vector<f_t>& vf);
    vector<int_t> getBot();
    vector<int_t> getTop();
    shapleyStochasticGame(vector<shapleyVertex> vertices, f_t eps);
    vector<f_t> scaleDown(const vector<int_t>& v);
    vector<int_t> scaleUp(const vector<f_t>& v);
    void print();
    f_t scale;
    f_t q;

private:
    const f_t EPSILON;
    int_t N;
};

f_t getZeroSumVal(const vector<vector<f_t>>& payoffMatrix);

#endif //SRC_SHAPLEYSTOCHASTICGAME_H
