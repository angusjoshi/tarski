#include <iostream>
#include "innerAlgorithm.cpp"
#include "examples.h"

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


    int sliceDimension = 2;
    int sliceMiddle = N / 2;
    vector<int> bot {0, 0, 0};
    vector<int> top {N, N, N};

    auto monotonePoint = innerAlgorithm.findMonotonePoint(
            bot,
            top,
            sliceDimension,
            sliceMiddle);

    while(!isFixpoint(monotonePoint, f)) {
        if(isUp(monotonePoint, f)) {
            bot = monotonePoint;
        } else {
            // assert(isDown(monotonePoint, f));
            top = monotonePoint;
        }

        sliceMiddle = (top[sliceDimension] - bot[sliceDimension]) / 2;
        monotonePoint = innerAlgorithm.findMonotonePoint(
                bot,
                top,
                sliceDimension,
                sliceMiddle);
    }

    cout << "result is: ";
    printVec(monotonePoint);

    cout << endl;
    cout << "query count is: ";
    cout << queryCounter << endl;
}

