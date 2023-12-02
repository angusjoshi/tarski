//
// Created by angus on 05/11/2023.
//

#ifndef SRC_INNERALGORITHM_H
#define SRC_INNERALGORITHM_H

#include <vector>
#include <functional>
#include "monotoneFunction.h"

using namespace std;

class InnerAlgorithm {

private:
    vector<int> bot;
    vector<int> top;
    vector<int> a;
    vector<int> u;
    vector<int> d;
    vector<int> b;

    bool useCeilDivision;
    int ceilDivisionDimension;

    function<vector<direction> (const vector<int>&)> f;

    bool satisfiesInvariant();
    bool instanceIsWellFormed();
    [[nodiscard]] vector<int> getMidInSlice(const vector<int>& x, const vector<int>& y) const;
    [[nodiscard]] pair<vector<int>, vector<direction>> helper();
    bool fixWitnesses();
    bool isNarrowInstance();
    bool isDoublyNarrowInstance();
    bool isWidthZeroInstance();
    void fixNarrowInstance();
    optional<pair<vector<int>, vector<direction>>> trySolveWidthZeroInstance();
    pair<vector<int>, vector<direction>> solveZeroWidthInstance(int narrowDimension, const vector<int>& bot, const vector<int>& top);
    pair<vector<int>, vector<direction>> exhaustiveSearchInstance();
    int getNarrowDimension();

    static bool sliceWeakUp(const vector<direction>& directions);
    static bool sliceWeakDown(const vector<direction>& directions);
    static bool sliceEq(const vector<int>& x, const vector<int>& y);
    static int getNeDimension(const vector<int>& x, const vector<int>& y);

public:
    InnerAlgorithm(const vector<int>& bot, const vector<int>& top, const function<vector<direction> (const vector<int>&)>& f);
    ~InnerAlgorithm();

    pair<vector<int>, vector<direction>> findMonotonePoint();
};

pair<vector<int>, vector<direction>> findMonotonePoint3(const vector<int>& bot, const vector<int>& top,
                              const function<vector<direction> (const vector<int>&)>& directionFunction,
                              int sliceDimension,
                              int sliceValue);
#endif //SRC_INNERALGORITHM_H
