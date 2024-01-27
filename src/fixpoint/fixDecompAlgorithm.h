//
// Created by angus on 07/11/2023.
//

#ifndef SRC_FIXDECOMPALGORITHM_H
#define SRC_FIXDECOMPALGORITHM_H

#include <vector>
#include <functional>
#include "latticeUtil.h"

using namespace std;

vector<int> findFixpointByFixDecomposition(const vector<int>& bot,
                                           const vector<int>& top,
                                           const function<vector<direction> (const vector<int>&)>& f);

#endif //SRC_FIXDECOMPALGORITHM_H
