#include <iostream>
#include "innerAlgorithm.cpp"
#include "examples.h"

int getNextNeIndex(int start, const vector<int>& a, const vector<int>& b) {
    assert(a.size() == b.size());

    for(int i = start; i < a.size(); i++) {
        if(a[i] != b[i]) return i;
    }

    return -1;
}

vector<int> searchSmallInstance(const vector<int>& bot,
                                const vector<int>& top,
                                const function<vector<int> (const vector<int>&)>& f) {
    assert(isUp(bot, f));
    assert(isDown(top, f));

    vector<int> current = bot;
    vector<int> fCurrent = f(bot);
    int currentDimension = getNextNeIndex(0, current, fCurrent);

    while(currentDimension != -1) {
        current[currentDimension]++;
        fCurrent = f(current);

        currentDimension = getNextNeIndex(currentDimension, current, fCurrent);
    }

    return current;
}

int main() {
    int N = 3;

    int queryCounter = 0;
    auto f = [&queryCounter](auto v) {
        queryCounter++;
        cout << "query! count is: " << queryCounter << endl;
        return example1[v[0]][v[1]][v[2]];
    };

    InnerAlgorithm innerAlgorithm {
            vector<int> {0, 0, 0},
            vector<int> {N, N, N},
            f};


    vector<int> bot {0, 0, 0};
    vector<int> top {N, N, N};

    int sliceDimension = getLargeEnoughSliceIndex(bot, top);
    int sliceMiddleValue = getSliceMiddle(bot, top, sliceDimension);

    auto monotonePoint = innerAlgorithm.findMonotonePoint(
            bot,
            top,
            sliceDimension,
            sliceMiddleValue);

    assert(isUp(monotonePoint, f) || isDown(monotonePoint, f));

    while(!isFixpoint(monotonePoint, f)) {
        if(isUp(monotonePoint, f)) {
            bot = monotonePoint;
        } else {
            top = monotonePoint;
        }

        cout << "top is: ";
        printVec(top);
        cout << "\n bot is: ";
        printVec(bot);
        cout << endl;

        cout << "monotone is: ";

        sliceDimension = getLargeEnoughSliceIndex(bot, top);

        if(sliceDimension == -1) {
            monotonePoint = searchSmallInstance(bot, top, f);
            break;
        }

        sliceMiddleValue = getSliceMiddle(bot, top, sliceDimension);

        monotonePoint = innerAlgorithm.findMonotonePoint(
                bot,
                top,
                sliceDimension,
                sliceMiddleValue);
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


