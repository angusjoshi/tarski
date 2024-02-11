//
// Created by angus on 10/02/2024.
//

#ifndef SRC_SIMPLESTOCHASTICGAME_H
#define SRC_SIMPLESTOCHASTICGAME_H
#include <vector>
#include <functional>
#include <boost/multiprecision/gmp.hpp>
#include "../config.h"

using namespace std;

enum vertexType {
    mini,
    maxi,
    chance,
};

// indexing with is assumed to be the same as the vertices vector.
struct successor {
    int i;
    f_t p;
    bool isMaxSink;
    bool isMinSink;
};

struct vertex {
    vertexType type;
    vector<successor> succs;
};

struct simpleStochasticGame {
    vector<vertex> vertices;

    function<vector<int_t>(const vector<int_t>& v)> getMonotoneFunction();
    int_t discretize(f_t d);
    vector<f_t> unDiscretize(const vector<int_t>& v);
};



#endif //SRC_SIMPLESTOCHASTICGAME_H
