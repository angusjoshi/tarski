//
// Created by angus on 07/11/2023.
//

#ifndef SRC_THREEDIMENSIONALGORITHM_H
#define SRC_THREEDIMENSIONALGORITHM_H

#include "innerAlgorithm.h"
#include <functional>

vector<int> findFixpoint3(const vector<int>& bot,
                         const vector<int>& top,
                         const function<vector<direction> (const vector<int>&)>& f);



#endif //SRC_THREEDIMENSIONALGORITHM_H
