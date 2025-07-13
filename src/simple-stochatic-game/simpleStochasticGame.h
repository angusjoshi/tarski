//
// Created by angus on 10/02/2024.
//

#ifndef SRC_SIMPLESTOCHASTICGAME_H
#define SRC_SIMPLESTOCHASTICGAME_H
#include <vector>
#include <functional>
#include "../config.h"

using namespace std;

enum simpleVertexType {
    mini = 0,
    maxi = 1,
    chance = 2,
    maxSink = 3,
    last
};

// simpleSuccessor indexing is assumed to be the same as the vertices vector.
struct simpleSuccessor {
    int i;
    f_t p;
};

struct simpleVertex {
    simpleVertexType type;
    vector<simpleSuccessor> succs;
};

struct simpleStochasticGame {
    vector<simpleVertex> vertices;

    const vector<f_t> computeFunction(const vector<f_t>& vf);
    const function<vector<f_t>(const vector<f_t>& v)> getCtsMonotoneFunction();
    const function<vector<int_t>(const vector<int_t>& v)> getMonotoneFunction();
    const vector<f_t> getCtsStart();
    const vector<int_t> getBot();
    const vector<int_t> getTop();
    simpleStochasticGame(vector<simpleVertex> vertices, f_t eps = 0.01);
    const vector<int_t> discretize(const vector<f_t>& d);
    const vector<f_t> unDiscretize(const vector<int_t>& v);
    const void print();
    f_t contractionFactor;
    int_t N;
    int k;

private:
    const f_t EPSILON;
    int maxSinkI;
    const void contract(vector<f_t>& v);
};



#endif //SRC_SIMPLESTOCHASTICGAME_H
