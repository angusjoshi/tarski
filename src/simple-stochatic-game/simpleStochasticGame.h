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
    minSink = 4,
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

    function<vector<int_t>(const vector<int_t>& v)> getMonotoneFunction();
    vector<int_t> getBot();
    vector<int_t> getTop();
    simpleStochasticGame(vector<simpleVertex> vertices);
    vector<int_t> discretize(const vector<f_t>& d);
    vector<f_t> unDiscretize(const vector<int_t>& v);
    void print();

private:
    int_t N;
    int maxSinkI;
    int minSinkI;
    f_t contractionFactor;
    void contract(vector<f_t>& v);
};



#endif //SRC_SIMPLESTOCHASTICGAME_H
