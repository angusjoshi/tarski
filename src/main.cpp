#include <iostream>
#include "examples.h"
#include "latticeUtil.h"
#include "recursiveBinarySearch.h"
#include "fixDecompAlgorithm.h"


int main() {
//    int N = 3;

//    int queryCounter = 0;
//    auto fg = [&queryCounter](auto v) {
//        queryCounter++;
//        cout << "query! count is: " << queryCounter << endl;
//        return example1[v[0]][v[1]][v[2]];
//    };
//    auto f = getDirectionFunction(fg);
//
//    vector<int> bot {0, 0, 0};
//    vector<int> top {N, N, N};
//
//    vector<int> fixpoint = findFixpoint3(bot, top, f);
//    vector<int> fgFixpoint = fg(fixpoint);
//
//    cout << "fixpoint is: ";
//    printVec(fixpoint);
//    cout << endl;
//
//    cout << "fgFixpoint is: ";
//    printVec(fgFixpoint);
//    cout << endl;

    vector<int> x {2, 1, 4, 5, 2, 2, 8, 3, 4, 2, 8, 5, 2, 8, 6};
    auto example2 = [&x](const vector<int>& v) -> const auto& {
        // example 2 is a 6 dimensional problem on [9]^d.
//        cout << "queried with vec: ";
//        printVec(v);
//        cout << endl;
        assert(v.size() == 15);

        return x;
    };

    auto example3 = [](const vector<int>& v) {
        assert(v.size() == 2);
        return vector<int> {21312334, 71241243};
    };

    int queryCount = 0;
    auto f = [&example2, &queryCount] (const auto& v) -> const auto& {
        queryCount++;
        return example2(v);
    };

    auto g = getDirectionFunction(f);

    vector<int> bot {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<int> top {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

//    vector<int> bot {0, 0, 0, 0, 0, 0};
//    vector<int> top {9, 9, 9, 9, 9, 9};
//    vector<int> bot {0, 0};
//    vector<int> top {INT_MAX, INT_MAX};
//    auto fixpoint = findFixpointRecBin(bot, top, g);

    auto fixpoint = findFixpointByFixDecomposition(bot, top, g);

    cout << "fixpoint is: ";
    printVec(fixpoint);
    cout << endl << "query count is: " << queryCount << endl;

    return 0;
}

//    int sliceDimension = getLargeEnoughSliceIndex(bot, top);
//    int sliceMiddleValue = getSliceMiddle(bot, top, sliceDimension);
//    auto monotonePoint = findMonotonePoint3(bot, top, f, sliceDimension, sliceMiddleValue);
//
//    while(!isFixpoint(monotonePoint, f)) {
//        if(isUp(monotonePoint, f)) {
//            bot = monotonePoint;
//        } else {
//            top = monotonePoint;
//        }
//
//        sliceDimension = getLargeEnoughSliceIndex(bot, top);
//
//        if(sliceDimension == -1) {
//            bot.insert(bot.begin() + sliceDimension, sliceMiddleValue);
//            top.insert(top.begin() + sliceDimension, sliceMiddleValue);
//            monotonePoint = searchSmallInstance(bot, top, f);
//            break;
//        }
//
//        sliceMiddleValue = getSliceMiddle(bot, top, sliceDimension);
//        monotonePoint = findMonotonePoint3(bot, top, f, sliceDimension, sliceMiddleValue);
//    }
//
//    assert(isFixpoint(monotonePoint, f));
//
//    cout << "result is: ";
//    printVec(monotonePoint);
//
//    auto fMonotonePoint = f(monotonePoint);
//    cout << "f m is : ";
//    printVec(fMonotonePoint);
//    cout << endl;
//
//
//    cout << endl;
//    cout << "query count is: ";
//    cout << queryCounter << endl;


