//
// Created by angus on 30/03/2024.
//
#include "valueIteration.h"
#include <iostream>

f_t dist(const vector<f_t>& x, const vector<f_t>& y) {
    assert(x.size() == y.size());
    f_t dist = 0.f;

    for(int i = 0; i < x.size(); i++) {
        dist = max(dist, abs(x[i] - y[i]));
    }

    return dist;
}

vector<f_t> valueIteration(const function<vector<f_t>(const vector<f_t>& v)>& f, const vector<f_t>& start, f_t targetDist) {
    vector<f_t> current = start;
    vector<f_t> fCurrent = f(current);
    while(dist(current, fCurrent) > targetDist) {
        current = fCurrent;
        fCurrent = f(current);
    }

    return current;
}
