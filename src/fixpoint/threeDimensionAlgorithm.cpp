//
// Created by angus on 07/11/2023.
//

#include "threeDimensionAlgorithm.h"
#include "latticeUtil.h"

vector<int> findFixpoint3(const vector<int>& bot,
                         const vector<int>& top,
                         const function<vector<direction> (const vector<int>&)>& f) {
    assert(bot.size() == 3);
    assert(top.size() == 3);

    int sliceDimension = getLargeEnoughSliceIndex(bot, top);
    int sliceMiddleValue = getSliceMiddle(bot, top, sliceDimension);

    if(sliceDimension == -1) {
        return searchSmallInstance(bot, top, f);
    }

    auto monotonePointPair = findMonotonePoint3(bot, top, f, sliceDimension, sliceMiddleValue);
    auto monotonePoint = monotonePointPair.first;
    auto monotonePointDirections = monotonePointPair.second;

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

        sliceMiddleValue = getSliceMiddle(currentBot, currentTop, sliceDimension);
        monotonePointPair = findMonotonePoint3(currentBot, currentTop, f, sliceDimension, sliceMiddleValue);
        monotonePoint = monotonePointPair.first;
        monotonePointDirections = monotonePointPair.second;
    }

    assert(isAllFixed(monotonePointDirections));
    return monotonePoint;
}
