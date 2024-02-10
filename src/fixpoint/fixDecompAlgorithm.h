//
// Created by angus on 07/11/2023.
//

#ifndef SRC_FIXDECOMPALGORITHM_H
#define SRC_FIXDECOMPALGORITHM_H

#include <vector>
#include <functional>
#include "latticeUtil.h"

using namespace std;

vector<int_t> findFixpointByFixDecomposition(const vector<int_t>& bot,
                                           const vector<int_t>& top,
                                           const function<vector<direction> (const vector<int_t>&)>& f);

#endif //SRC_FIXDECOMPALGORITHM_H
