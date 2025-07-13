//
// Created by angus on 05/07/2024.
//

#ifndef SRC_ODDEVEN_H
#define SRC_ODDEVEN_H
#include <vector>
#include "../config.h"

using namespace std;

struct OddEven {
    void reset(int newK, int_t newN);
    void resetHelper(int i, bool even, vector<int_t>& current);
    bool isBalanced(const vector<int_t>& point);
    vector<int_t> someBalancedPoint();
    void removePyramids(const vector<int_t>& queried, const vector<int_t>& result);
    void printAll();


    // k is the dimension of the cube, n is side length
    int k;
    int_t n;
    vector<vector<int_t>> points;
};

#endif //SRC_ODDEVEN_H
