//
// Created by angus on 05/11/2023.
//

#ifndef SRC_MONOTONEFUNCTION_H
#define SRC_MONOTONEFUNCTION_H

#include <functional>
#include <ranges>
#include <iostream>

using namespace std;
namespace rng = std::ranges;

enum direction {
    up = 1,
    down = -1,
    fix = 0
};

typedef struct {
    vector<int> slicedBot;
    vector<int> slicedTop;
    function<vector<direction>(const vector<int> &)> slicedFunction;
} slicedLattice;


// returns a function [n]^{d-1} to direction^d, where the last element
// in the result is guaranteed to be the sliced dimension.
function<vector<direction> (const vector<int>&)> getSlicedFunction(
        const function<vector<direction> (const vector<int>&)>& f,
        int sliceDimension,
        int sliceVal);

void printDirections(const vector<direction>& directions);
function<vector<direction> (const vector<int>&)> getDirectionFunction(
        const function<vector<int> (const vector<int>&)>& f
        );

slicedLattice getSlicedLattice(const vector<int>& bot,
                               const vector<int>& top,
                               const function<vector<direction>(const vector<int> &)> &f,
                               int sliceDimension,
                               int sliceValue);

bool isAllWeakUp(const vector<direction>& directions);
bool isAllWeakDown(const vector<direction>& directions);
bool isAllFixed(const vector<direction>& directions);

#endif //SRC_MONOTONEFUNCTION_H
