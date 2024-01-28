//
// Created by angus on 28/01/2024.
//

#ifndef SRC_FINDFIXPOINTBYMONOTONEDECOMP_H
#define SRC_FINDFIXPOINTBYMONOTONEDECOMP_H

#include "monotoneFunction.h"

vector<int> findFixpointByMonotoneDecomp(const vector<int>& bot,
                          const vector<int>& top,
                          const function<vector<direction> (const vector<int>&)>& f);
#endif //SRC_FINDFIXPOINTBYMONOTONEDECOMP_H
