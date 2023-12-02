#include <iostream>
#include "fixpoint/examples.h"
#include "fixpoint/latticeUtil.h"
#include "fixpoint/recursiveBinarySearch.h"
#include "fixpoint/fixDecompAlgorithm.h"
#include <chrono>
#include "arrival/generateRandomInstance.h"
#include "arrival/arrivalUtil.h"
#include "arrival/preprocessInstance.h"
#include "arrival/simpleWalk.h"
#include "arrival/arrivalInstance.h"
#include "analysis/runAnalysis.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration;

vector<pair<int, int>> longExample { {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {10, 10} };

void fixpointExample() {
    vector<int> x {2, 1, 4, 5, 2, 2, 8, 3, 4, 2, 8, 5, 2, 8, 6};
    auto example2 = [&x](const vector<int>& v) -> const auto& {
        assert(v.size() == 15);

        return x;
    };


    long long queryCount = 0;
    auto f = [&example2, &queryCount] (const auto& v) -> const auto& {
        queryCount++;
        return example2(v);
    };

    auto g = getDirectionFunction(f);

    vector<int> bot {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<int> top {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    auto t1 = high_resolution_clock::now();

//    auto fixpoint = findFixpointRecBin(bot, top, g);
    auto fixpoint = findFixpointByFixDecomposition(bot, top, g);

    auto t2 = high_resolution_clock::now();


    cout << "fixpoint is: ";
    printVec(fixpoint);
    cout << endl << "query count is: " << queryCount << endl;

    duration<double, std::milli> ms = t2 - t1;
    std::cout << "time was: " << ms.count() << "ms" << endl;
}
void randExample() {
    vector<pair<int, int>> instance = generateRandomInstance(100000);
    cout << "\n\n\n ===============RAND=============\n";
    printInstance(instance);

    vector<pair<int, int>> preprocessedInstance = preprocessInstance(instance);

    cout << "\n\n\n ===============PROCESSED=============\n";
    printInstance(preprocessedInstance);

    int result = simpleWalk(preprocessedInstance);
    if(result) {
        cout << "found the end" << endl;
    } else {
        cout << "didn't find the end" << endl;
    }
}
void arrivalFixpointExample() {

    for(int i = 0; i < 100; i++) {

    vector<pair<int, int>> instance = generateRandomInstance(15);

            cout << "\n\n\n ===============RAND=============\n";
    printInstance(instance);

    vector<pair<int, int>> preprocessedInstance = preprocessInstance(instance);

    cout << "\n\n\n ===============PROCESSED=============\n";
    printInstance(preprocessedInstance);

    ArrivalInstance arrivalInstance {std::move(preprocessedInstance)};
    auto g = arrivalInstance.getDirectionFunction();
    auto bot = arrivalInstance.getBot();
    auto top = arrivalInstance.getTop();

    int queryCounter = 0;
    auto f =  [&g, &queryCounter] (const auto& v) {
        queryCounter++;
        return g(v);
    };

//    auto fixpoint = findFixpointRecBin(bot, top, f);
    auto fixpoint = findFixpointByFixDecomposition(bot, top, f);

    cout << "done!!!!!!! fixpoint is: ";
    printVec(fixpoint);
    vector<direction> dirs = f(fixpoint);
    cout << "query count is: " << queryCounter << endl;

    int sinkInflow = arrivalInstance.computeSinkInflow(fixpoint);
    cout << "sinkInflow is: " << sinkInflow << endl;

    assert(isAllFixed(dirs));
    if(!isAllFixed(dirs)) throw;
    }
}

int main() {
//    fixpointExample();
//    randExample();
//    arrivalFixpointExample();

    runAndPrintAnalysis();
    return 0;
}


