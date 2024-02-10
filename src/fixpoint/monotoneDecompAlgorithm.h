//
// Created by angus on 27/01/2024.
//

#ifndef SRC_MONOTONEDECOMPALGORITHM_H
#define SRC_MONOTONEDECOMPALGORITHM_H
#include <vector>
#include "monotoneFunction.h"

pair<vector<int_t>, vector<direction>> findMonotonePointByDecomposition(const vector<int_t> &bot,
                                           const vector<int_t> &top,
                                           const function<vector<direction>(const vector<int_t> &)> &f);
#endif //SRC_MONOTONEDECOMPALGORITHM_H
