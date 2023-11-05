//
// Created by angus on 05/11/2023.
//

#ifndef SRC_MONOTONEFUNCTION_H
#define SRC_MONOTONEFUNCTION_H

#include <functional>
#include <ranges>

using namespace std;
namespace rng = std::ranges;

enum direction {
    up = 1,
    down = -1,
    fixed = 0
};

// returns a function [n]^{d-1} to direction^d, where the last element
// in the result is guaranteed to be the sliced dimension.
function<vector<direction> (const vector<int>&)> getSlicedFunction(
        const function<vector<direction> (const vector<int>&)>& f,
        int sliceDimension,
        int sliceVal);

function<vector<direction> (const vector<int>&)> getDirectionFunction(
        const function<vector<int> (const vector<int>&)>& f
        );

bool isAllWeakUp(const vector<direction>& directions);
bool isAllWeakDown(const vector<direction>& directions);

#endif //SRC_MONOTONEFUNCTION_H
