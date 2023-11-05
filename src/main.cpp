#include <iostream>
#include "innerAlgorithm.h"
#include "examples.h"
#include "latticeUtil.h"


int main() {
    int N = 3;

    int queryCounter = 0;
    auto f = [&queryCounter](auto v) {
        queryCounter++;
        cout << "query! count is: " << queryCounter << endl;
        return example1[v[0]][v[1]][v[2]];
    };

    vector<int> bot {0, 0, 0};
    vector<int> top {N, N, N};

    int sliceDimension = getLargeEnoughSliceIndex(bot, top);
    int sliceMiddleValue = getSliceMiddle(bot, top, sliceDimension);
    auto monotonePoint = findMonotonePoint3(bot, top, f, sliceDimension, sliceMiddleValue);

    while(!isFixpoint(monotonePoint, f)) {
        if(isUp(monotonePoint, f)) {
            bot = monotonePoint;
        } else {
            top = monotonePoint;
        }

        sliceDimension = getLargeEnoughSliceIndex(bot, top);

        if(sliceDimension == -1) {
            bot.insert(bot.begin() + sliceDimension, sliceMiddleValue);
            top.insert(top.begin() + sliceDimension, sliceMiddleValue);
            monotonePoint = searchSmallInstance(bot, top, f);
            break;
        }

        sliceMiddleValue = getSliceMiddle(bot, top, sliceDimension);
        monotonePoint = findMonotonePoint3(bot, top, f, sliceDimension, sliceMiddleValue);
    }

    assert(isFixpoint(monotonePoint, f));

    cout << "result is: ";
    printVec(monotonePoint);

    auto fMonotonePoint = f(monotonePoint);
    cout << "f m is : ";
    printVec(fMonotonePoint);
    cout << endl;


    cout << endl;
    cout << "query count is: ";
    cout << queryCounter << endl;

    return 0;
}


