//
// Created by angus on 05/11/2023.
//

#ifndef SRC_LATTICEUTIL_H
#define SRC_LATTICEUTIL_H
#include <functional>
#include <vector>
#include "monotoneFunction.h"

using namespace std;

bool latticeLe(const vector<int_t>& x, const vector<int_t>& y);
bool latEq(const vector<int_t>& a, const vector<int_t>& b);
bool isFixpoint(const vector<int_t>& point, const function<vector<direction> (const vector<int_t>&)>& f);
bool isUp(const vector<int_t>& point, const function<vector<direction> (const vector<int_t>&)>& f);
bool isDown(const vector<int_t>& point, const function<vector<direction> (const vector<int_t>&)>& f);
int_t getSliceMiddle(const vector<int_t>& bot, const vector<int_t>& top, int i);
int getLargeEnoughSliceIndex(const vector<int_t>& bot, const vector<int_t>& top);
void printVec(const vector<long long>& v);
void printVec(const vector<int_t>& v);
int getNextUpIndex(const vector<direction>& a);
vector<int_t> searchSmallInstance(const vector<int_t>& bot,
                                const vector<int_t>& top,
                                const function<vector<direction> (const vector<int_t>&)>& f);
vector<int_t> join(vector<int_t> &&a, const vector<int_t> &b);
vector<int_t> meet(vector<int_t> &&a, const vector<int_t> &b);

#endif //SRC_LATTICEUTIL_H

