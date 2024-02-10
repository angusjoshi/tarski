//
// Created by angus on 07/11/2023.
//

#ifndef SRC_RECURSIVEBINARYSEARCH_H
#define SRC_RECURSIVEBINARYSEARCH_H
#include <vector>
#include "latticeUtil.h"

using namespace std;

int_t oneDimensionExhaustiveSearch(int_t bot, int_t top, const function<direction(const int_t&)>& f);
int_t binarySearch(int_t bot, int_t top, const function<direction(const int_t&)>& f);

vector<int_t> findFixpointRecBin(const vector<int_t>& bot,
                               const vector<int_t>& top,
                               const function<vector<direction>(const vector<int_t>&)>& f);

#endif //SRC_RECURSIVEBINARYSEARCH_H
