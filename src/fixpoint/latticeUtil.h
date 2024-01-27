//
// Created by angus on 05/11/2023.
//

#ifndef SRC_LATTICEUTIL_H
#define SRC_LATTICEUTIL_H
#include <functional>
#include <vector>
#include "monotoneFunction.h"

using namespace std;

bool latticeLe(const vector<int>& x, const vector<int>& y);
bool latEq(const vector<int>& a, const vector<int>& b);
bool isFixpoint(const vector<int>& point, const function<vector<direction> (const vector<int>&)>& f);
bool isUp(const vector<int>& point, const function<vector<direction> (const vector<int>&)>& f);
bool isDown(const vector<int>& point, const function<vector<direction> (const vector<int>&)>& f);
int getSliceMiddle(const vector<int>& bot, const vector<int>& top, int i);
int getLargeEnoughSliceIndex(const vector<int>& bot, const vector<int>& top);
void printVec(const vector<long long>& v);
void printVec(const vector<int>& v);
int getNextUpIndex(const vector<direction>& a);
vector<int> searchSmallInstance(const vector<int>& bot,
                                const vector<int>& top,
                                const function<vector<direction> (const vector<int>&)>& f);
vector<int> join(vector<int> &&a, const vector<int> &b);
vector<int> meet(vector<int> &&a, const vector<int> &b);

#endif //SRC_LATTICEUTIL_H

