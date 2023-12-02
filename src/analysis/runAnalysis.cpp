//
// Created by angus on 02/12/2023.
//

#include "runAnalysis.h"
#include "../arrival/generateRandomInstance.h"
#include <iostream>
#include "../fixpoint/latticeUtil.h"
#include "../arrival/arrivalUtil.h"
#include "../arrival/arrivalInstance.h"
#include "../arrival/preprocessInstance.h"
#include "../fixpoint/fixDecompAlgorithm.h"
#include "../fixpoint/recursiveBinarySearch.h"
#include <thread>
#include <chrono>
#include <future>

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using namespace std;

vector<int> sizes {3, 5, 8, 12, 15, 20};
vector<int> danqiyeSizes {3, 4, 5, 6, 7, 8};

enum algorithm {
    recbin,
    decomp,
};


pair<int, double> solveRandomArrival(int instanceSize, algorithm algorithmToRun) {
    vector<pair<int, int>> instance = generateRandomInstance(instanceSize);
    vector<pair<int, int>> preprocessedInstance = preprocessInstance(instance);
    ArrivalInstance arrivalInstance {std::move(preprocessedInstance)};
    auto g = arrivalInstance.getDirectionFunction();
    auto bot = arrivalInstance.getBot();
    auto top = arrivalInstance.getTop();

    long long queryCounter = 0;
    auto f =  [&g, &queryCounter] (const auto& v) {
        queryCounter++;
        return g(v);
    };

    auto t1 = high_resolution_clock::now();

    auto fixpoint = algorithmToRun == decomp
            ? findFixpointByFixDecomposition(bot, top, f)
            : findFixpointRecBin(bot, top, f);

    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms = t2 - t1;

    return { queryCounter, ms.count() };
}

void runAndPrintAnalysis() {
//    auto fixpoint = findFixpointRecBin(bot, top, f);

    auto [queryCount, time] = solveRandomArrival(15, decomp);
    cout << "query count was: " << queryCount << endl;
    cout << "time was: " << time << "ms" << endl;
}