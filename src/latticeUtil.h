//
// Created by angus on 05/11/2023.
//

#ifndef SRC_LATTICEUTIL_H
#define SRC_LATTICEUTIL_H
#include <functional>
#include <vector>

using namespace std;

bool latticeLe(const vector<int>& x, const vector<int>& y);
bool latEq(const vector<int>& a, const vector<int>& b);
bool isFixpoint(const vector<int>& point, const function<vector<int> (const vector<int>&)>& f);
bool isUp(const vector<int>& point, const function<vector<int> (const vector<int>&)>& f);
bool isDown(const vector<int>& point, const function<vector<int> (const vector<int>&)>& f);
int getSliceMiddle(const vector<int>& bot, const vector<int>& top, int i);
int getLargeEnoughSliceIndex(const vector<int>& bot, const vector<int>& top);
void printVec(const vector<int>& v);
int getNextNeIndex(int start, const vector<int>& a, const vector<int>& b);
vector<int> searchSmallInstance(const vector<int>& bot,
                                const vector<int>& top,
                                const function<vector<int> (const vector<int>&)>& f);

#endif //SRC_LATTICEUTIL_H

