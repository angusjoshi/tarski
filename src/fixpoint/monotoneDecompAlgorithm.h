//
// Created by angus on 27/01/2024.
//

#ifndef SRC_MONOTONEDECOMPALGORITHM_H
#define SRC_MONOTONEDECOMPALGORITHM_H
#include <vector>
#include "monotoneFunction.h"

pair<vector<int>, vector<direction>> findMonotonePointByDecomposition(const vector<int> &bot,
                                           const vector<int> &top,
                                           const function<vector<direction>(const vector<int> &)> &f);
#endif //SRC_MONOTONEDECOMPALGORITHM_H
