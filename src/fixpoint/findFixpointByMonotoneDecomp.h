//
// Created by angus on 28/01/2024.
//

#ifndef SRC_FINDFIXPOINTBYMONOTONEDECOMP_H
#define SRC_FINDFIXPOINTBYMONOTONEDECOMP_H

#include "monotoneFunction.h"

vector<int_t> findFixpointByMonotoneDecomp(const vector<int_t>& bot,
                          const vector<int_t>& top,
                          const function<vector<direction> (const vector<int_t>&)>& f);
#endif //SRC_FINDFIXPOINTBYMONOTONEDECOMP_H
