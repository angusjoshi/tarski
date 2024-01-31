//
// Created by angus on 02/12/2023.
//

#include "runAnalysis.h"
#include "../arrival/arrivalInstance.h"
#include "../arrival/arrivalUtil.h"
#include "../arrival/generateRandomInstance.h"
#include "../arrival/preprocessInstance.h"
#include "../arrival/simpleWalk.h"
#include "../fixpoint/fixDecompAlgorithm.h"
#include "../fixpoint/kleeneTarski.h"
#include "../fixpoint/latticeUtil.h"
#include "../fixpoint/recursiveBinarySearch.h"
#include "../fixpoint/findFixpointByMonotoneDecomp.h"
#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>

using std::chrono::duration;
using std::chrono::high_resolution_clock;
using namespace std;

vector<int> sizes{3, 5, 8, 12, 15, 20};
vector<int> danqiyeSizes{3, 4, 5, 6, 7, 8};

enum algorithm {
    recbin,
    decomp,
    monotoneDecomp,
};


pair<int, double> solveRandomArrivalWithIterate(int instanceSize) {
    vector<pair<int, int>> instance = generateRandomInstance(instanceSize);
    vector<pair<int, int>> preprocessedInstance = preprocessInstance(instance);
    cout << "instance is: ";
    printInstance(preprocessedInstance);
    ArrivalInstance arrivalInstance{std::move(preprocessedInstance)};
    auto g = arrivalInstance.getIntFunction();
    auto bot = arrivalInstance.getBot();
    auto top = arrivalInstance.getTop();

    long long queryCounter = 0;
    auto f = [&queryCounter, &g](const auto &v) {
        queryCounter++;
        return g(v);
    };

    auto t1 = high_resolution_clock::now();
    auto fixpoint = kleeneTarski(top, f);
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms = t2 - t1;

    return {queryCounter, ms.count()};
}
int manhattanDistance(const vector<int> &a, const vector<int> &b) {
    assert(a.size() == b.size());
    int distance = 0;

    for (int i = 0; i < a.size(); i++) {
        distance += abs(a[i] - b[i]);
    }

    return distance;
}

pair<int, double> solveRandomArrival(int instanceSize, algorithm algorithmToRun) {
    vector<pair<int, int>> instance = generateRandomInstance(instanceSize);
    vector<pair<int, int>> preprocessedInstance = preprocessInstance(instance);
    ArrivalInstance arrivalInstance{std::move(preprocessedInstance)};

    auto g = arrivalInstance.getDirectionFunction();
    auto bot = arrivalInstance.getBot();
    auto top = arrivalInstance.getTop();

    long long queryCounter = 0;
    auto f = [&g, &queryCounter](const auto &v) {
        queryCounter++;
        return g(v);
    };

    auto t1 = high_resolution_clock::now();
    auto fixpoint = algorithmToRun == decomp
                            ? findFixpointByFixDecomposition(bot, top, f)
                            : algorithmToRun == monotoneDecomp
                            ? findFixpointByMonotoneDecomp(bot, top, f)
                            : findFixpointRecBin(bot, top, f);
    auto t2 = high_resolution_clock::now();

    if(!isAllFixed(g(fixpoint))) throw runtime_error("algorithm returned a point which is not fixed!");

    duration<double, std::milli> ms = t2 - t1;

    return {queryCounter, ms.count()};
}

bool hasDiagonalEntries(const vector<pair<int, int>> &pairs) {
    return any_of(pairs.begin(), pairs.end(), [](const auto &p) { return p.first == p.second; });
}

pair<int, double> solveRandomArrivalWithWalk(int instanceSize) {
    auto instance = generateRandomInstance(instanceSize);
    auto processedInstance = preprocessInstance(instance);

    auto t1 = high_resolution_clock::now();
    auto [flows, counter] = simpleWalk(processedInstance);
    if (flows[flows.size() - 1] == 0) {
        if (!hasDiagonalEntries(vector<pair<int, int>>{processedInstance.begin(), processedInstance.end() - 1})) {
            printVec(flows);
            printInstance(processedInstance);
        }
    }
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms = t2 - t1;

    return {counter, ms.count()};
}

void runAndPrintAnalysis() {
    //    auto [queryCount, time] = solveRandomArrivalWithIterate(5);
    //    auto fixpoint = findFixpointRecBin(bot, top, f);

//    vector<int> decompTestSizes{3, 6, 9, 12, 15};
    vector<int> recBinTestSizes{3, 5, 7, 9};
    vector<int> decompTestSizes{7, 10, 13, 15, 18};
    vector<int> monDecompTestSizes{3, 5, 7, 9, 11, 13};
//    vector<int> decompTestSizes{7};
    //    vector<int> walkTestSizes {10, 100, 1000};//, 10000}; //, 100000, 10000000};
    int n = 20;

    string line = "==================================================\n";

//
//    cout << line;
//    cout << "STARTING DECOMP TEST" << endl;
//    for (auto testSize: decompTestSizes) {
//        vector<int> queryCounts{};
//        vector<double> times{};
//
//        for (int j = 0; j < n; j++) {
//            auto [queryCount, time] = solveRandomArrival(testSize, decomp);
//            queryCounts.push_back(queryCount);
//            times.push_back(time);
//        }
//        //
//        double avgTime = accumulate(times.begin(), times.end(), 0.0) / n;
//        double avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / n;
//        cout << line;
//        cout << "test size: " << testSize << endl;
//        cout << "avg queries was: " << avgQueries << endl;
//        cout << "avg time was: " << avgTime << "ms" << endl;
//    }
//
//        cout << line;
//        cout << "STARTING RECBIN TEST" << endl;
//        for(auto testSize : recBinTestSizes) {
//            vector<int> queryCounts {};
//            vector<double> times {};
//            for(int i = 0; i < n; i++) {
//                auto [queryCount, time] = solveRandomArrival(testSize, recbin);
//                queryCounts.push_back(queryCount);
//                times.push_back(time);
//            }
//
//            double avgTime = accumulate(times.begin(), times.end(), 0.0) / n;
//            int avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / n;
//            cout << "===========================================================" << endl;
//            cout << "test size: " << testSize << endl;
//            cout << "avg queries was: " << avgQueries << endl;
//            cout << "avg time was: " << avgTime << "ms" << endl;
//        }

    cout << line;
    cout << "STARTING MONDECOMP TEST" << endl;
    for(auto testSize : monDecompTestSizes) {
        vector<int> queryCounts {};
        vector<double> times {};
        for(int i = 0; i < n; i++) {
            auto [queryCount, time] = solveRandomArrival(testSize, monotoneDecomp);
            queryCounts.push_back(queryCount);
            times.push_back(time);
        }

        double avgTime = accumulate(times.begin(), times.end(), 0.0) / n;
        int avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / n;
        cout << "===========================================================" << endl;
        cout << "test size: " << testSize << endl;
        cout << "avg queries was: " << avgQueries << endl;
        cout << "avg time was: " << avgTime << "ms" << endl;
    }

    //    cout << line;
    //    cout << "STARTING KLEENETARSKI TEST" << endl;
    //    for(auto testSize : walkTestSizes) {
    //        vector<int> queryCounts {};
    //        vector<double> times {};
    //        for(int i = 0; i < n; i++) {
    //            auto [queryCount, time] = solveRandomArrivalWithIterate(testSize);
    //            queryCounts.push_back(queryCount);
    //            times.push_back(time);
    //        }
    //
    //        double avgTime = accumulate(times.begin(), times.end(), 0.0) / n;
    //        int avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / n;
    //        cout << "===========================================================" << endl;
    //        cout << "test size: " << testSize << endl;
    //        cout << "avg queries was: " << avgQueries << endl;
    //        cout << "avg time was: " << avgTime << "ms" << endl;
    //    }

    //    cout << line;
    //    cout << "STARTING WALK TEST" << endl;
    //    for(int testSize = 3; testSize <= 15; testSize++) {
    //        cout << testSize << endl;
    //        vector<int> queryCounts {};
    //        vector<double> times {};
    //        for(int i = 0; i < n; i++) {
    //            auto [stepCount, time] = solveRandomArrivalWithWalk(testSize);
    //            queryCounts.push_back(stepCount);
    //            times.push_back(time);
    //        }

    //        double avgTime = accumulate(times.begin(), times.end(), 0.0) / 100;
    //        long long avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / 100;
    //        cout << "===========================================================" << endl;
    ////        cout << "test size: " << testSize << endl;
    //        cout << "avg steps was: " << avgQueries << endl;
    //        cout << "avg time was: " << avgTime << "ms" << endl;
    //    }
}