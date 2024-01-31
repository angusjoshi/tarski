//
// Created by angus on 28/01/2024.
//

#include "findFixpointByMonotoneDecomp.h"
#include "latticeUtil.h"
#include "monotoneDecompAlgorithm.h"

pair<vector<int>, vector<direction>> findMonotonePoint(const vector<int>& bot,
                                         const vector<int>& top,
                                         const function<vector<direction> (const vector<int>&)>& f,
                                         int sliceDimension,
                                         int sliceValue) {
    auto slicedLattice = getSlicedLattice(bot, top, f, sliceDimension, sliceValue);
    auto slicedBot = slicedLattice.slicedBot;
    auto slicedTop = slicedLattice.slicedTop;
    auto slicedF = slicedLattice.slicedFunction;
    auto monotonePoint = findMonotonePointByDecomposition(slicedBot, slicedTop, slicedF);
    monotonePoint.first.insert(monotonePoint.first.begin() + sliceDimension, sliceValue);
    return monotonePoint;
}

vector<int> findFixpointByMonotoneDecomp(const vector<int>& bot,
                                         const vector<int>& top,
                                         const function<vector<direction> (const vector<int>&)>& f) {
    assert(bot.size() > 1);
    assert(top.size() == bot.size());

    int sliceDimension = getLargeEnoughSliceIndex(bot, top);
    int sliceValue = getSliceMiddle(bot, top, sliceDimension);

    if(sliceDimension == -1) {
        return searchSmallInstance(bot, top, f);
    }

    auto monotonePointPair = findMonotonePoint(bot, top, f, sliceDimension, sliceValue);
    auto monotonePoint = monotonePointPair.first;
    auto monotonePointDirections = monotonePointPair.second;

    assert(isAllWeakUp(monotonePointDirections) || isAllWeakDown(monotonePointDirections));

    vector<int> currentBot = bot;
    vector<int> currentTop = top;

    while(!isAllFixed(monotonePointDirections)) {
        assert(isAllWeakUp(monotonePointDirections) || isAllWeakDown(monotonePointDirections));

        if(isAllWeakUp(monotonePointDirections)) {
            currentBot = monotonePoint;
        } else {
            currentTop = monotonePoint;
        }

        sliceDimension = getLargeEnoughSliceIndex(currentBot, currentTop);

        if(sliceDimension == -1) {
            auto fixpoint = searchSmallInstance(currentBot, currentTop, f);
            assert(isAllFixed(f(fixpoint)));
            return fixpoint;
        }

        sliceValue = getSliceMiddle(currentBot, currentTop, sliceDimension);
        monotonePointPair = findMonotonePoint(currentBot, currentTop, f, sliceDimension, sliceValue);
        monotonePoint = monotonePointPair.first;
        monotonePointDirections = monotonePointPair.second;
    }

    assert(isAllFixed(monotonePointDirections));
    return monotonePoint;
}
