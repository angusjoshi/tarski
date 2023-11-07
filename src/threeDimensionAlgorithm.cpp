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
    auto monotonePoint = findMonotonePoint3(bot, top, f, sliceDimension, sliceMiddleValue);

    vector<int> currentBot = bot;
    vector<int> currentTop = top;

    while(!isFixpoint(monotonePoint, f)) {
        assert(isUp(monotonePoint, f) || isDown(monotonePoint, f));

        if(isUp(monotonePoint, f)) {
            currentBot = monotonePoint;
        } else {
            currentTop = monotonePoint;
        }

        sliceDimension = getLargeEnoughSliceIndex(currentBot, currentTop);

        if(sliceDimension == -1) {
            return searchSmallInstance(currentBot, currentTop, f);
        }

        sliceMiddleValue = getSliceMiddle(currentBot, currentTop, sliceDimension);
        monotonePoint = findMonotonePoint3(currentBot, currentTop, f, sliceDimension, sliceMiddleValue);
    }

    assert(isFixpoint(monotonePoint, f));
    return monotonePoint;
}
