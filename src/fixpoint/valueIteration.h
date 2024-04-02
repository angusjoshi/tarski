//
// Created by angus on 30/03/2024.
//

#ifndef SRC_VALUEITERATION_H
#define SRC_VALUEITERATION_H
#include "../config.h"
#include "../simple-stochatic-game/simpleStochasticGame.h"

f_t dist(const vector<f_t>& x, const vector<f_t>& y);
vector<f_t> valueIteration(const function<vector<f_t>(const vector<f_t>& v)>& f, const vector<f_t>& start, f_t EPSILON);

#endif //SRC_VALUEITERATION_H
