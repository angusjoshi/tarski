//
// Created by angus on 05/11/2023.
//

#ifndef SRC_MONOTONEFUNCTION_H
#define SRC_MONOTONEFUNCTION_H

#include <functional>
#include <ranges>
#include <iostream>
#include "../config.h"

using namespace std;
namespace rng = std::ranges;

enum direction {
    up = 1,
    down = -1,
    fix = 0
};

typedef struct {
    vector<int_t> slicedBot;
    vector<int_t> slicedTop;
    function<vector<direction>(const vector<int_t> &)> slicedFunction;
} slicedLattice;


// returns a function [n]^{d-1} to direction^d, where the last element
// in the result is guaranteed to be the sliced dimension.
function<vector<direction> (const vector<int_t>&)> getSlicedFunction(
        const function<vector<direction> (const vector<int_t>&)>& f,
        int sliceDimension,
        int_t sliceVal);

void printDirections(const vector<direction>& directions);
function<vector<direction> (const vector<int_t>&)> getDirectionFunction(
        const function<vector<int_t> (const vector<int_t>&)>& f
        );

slicedLattice getSlicedLattice(const vector<int_t>& bot,
                               const vector<int_t>& top,
                               const function<vector<direction>(const vector<int_t> &)> &f,
                               int sliceDimension,
                               int_t sliceValue);

bool isAllWeakUp(const vector<direction>& directions);
bool isAllWeakDown(const vector<direction>& directions);
bool isAllFixed(const vector<direction>& directions);

#endif //SRC_MONOTONEFUNCTION_H
