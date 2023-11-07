//
// Created by angus on 07/11/2023.
//

#ifndef SRC_RECURSIVEBINARYSEARCH_H
#define SRC_RECURSIVEBINARYSEARCH_H
#include <vector>
#include "latticeUtil.h"

using namespace std;

int binarySearch(int bot, int top, const function<direction(int)>& f);
vector<int> findFixpointRecBin(const vector<int>& bot,
                               const vector<int>& top,
                               const function<vector<direction>(const vector<int>&)>& f);

#endif //SRC_RECURSIVEBINARYSEARCH_H
