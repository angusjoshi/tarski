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
    vector<int_t> bot;
    vector<int_t> top;
    vector<int_t> a;
    vector<int_t> u;
    vector<int_t> d;
    vector<int_t> b;

    bool useCeilDivision;
    int ceilDivisionDimension;

    function<vector<direction> (const vector<int_t>&)> f;

    bool satisfiesInvariant();
    bool instanceIsWellFormed();
    [[nodiscard]] vector<int_t> getMidInSlice(const vector<int_t>& x, const vector<int_t>& y) const;
    [[nodiscard]] pair<vector<int_t>, vector<direction>> helper();
    bool fixWitnesses();
    bool isNarrowInstance();
    bool isDoublyNarrowInstance();
    bool isWidthZeroInstance();
    void fixNarrowInstance();
    optional<pair<vector<int_t>, vector<direction>>> trySolveWidthZeroInstance();
    pair<vector<int_t>, vector<direction>> solveZeroWidthInstance(int narrowDimension,
                                                                  const vector<int_t>& bot,
                                                                  const vector<int_t>& top);
    pair<vector<int_t>, vector<direction>> exhaustiveSearchInstance();
    int getNarrowDimension();

    static bool sliceWeakUp(const vector<direction>& directions);
    static bool sliceWeakDown(const vector<direction>& directions);
    static bool sliceEq(const vector<int_t>& x, const vector<int_t>& y);
    static int getNeDimension(const vector<int_t>& x, const vector<int_t>& y);

public:
    InnerAlgorithm(const vector<int_t>& bot, const vector<int_t>& top, const function<vector<direction> (const vector<int_t>&)>& f);
    ~InnerAlgorithm();

    pair<vector<int_t>, vector<direction>> findMonotonePoint();
};

pair<vector<int_t>, vector<direction>> findMonotonePoint3(const vector<int_t>& bot, const vector<int_t>& top,
                              const function<vector<direction> (const vector<int_t>&)>& directionFunction,
                              int sliceDimension,
                              int_t sliceValue);
#endif //SRC_INNERALGORITHM_H
