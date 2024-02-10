//
// Created by angus on 10/02/2024.
//

#ifndef SRC_SIMPLESTOCHASTICGAME_H
#define SRC_SIMPLESTOCHASTICGAME_H
#include <vector>
#include <functional>
#include <boost/multiprecision/gmp.hpp>

using namespace std;

enum vertexType {
    mini,
    maxi,
    chance,
    minSink,
    maxSink
};

typedef struct {
    int i;
    double p;
} successor;

typedef struct {
    vertexType type;
    vector<successor> succs;
} vertex;

typedef struct {
    vector<vertex> vertices;

    function<vector<int>(const vector<int>& v)> getMonotoneFunction();
} simpleStochasticGame;


#endif //SRC_SIMPLESTOCHASTICGAME_H
