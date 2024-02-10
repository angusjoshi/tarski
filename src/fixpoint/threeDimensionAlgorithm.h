//
// Created by angus on 07/11/2023.
//

#ifndef SRC_THREEDIMENSIONALGORITHM_H
#define SRC_THREEDIMENSIONALGORITHM_H

#include "innerAlgorithm.h"
#include <functional>

vector<int_t> findFixpoint3(const vector<int_t>& bot,
                         const vector<int_t>& top,
                         const function<vector<direction> (const vector<int_t>&)>& f);



#endif //SRC_THREEDIMENSIONALGORITHM_H
