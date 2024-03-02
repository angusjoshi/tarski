//
// Created by angus on 02/12/2023.
//

#include "runAnalysis.h"
#include "../arrival/arrivalInstance.h"
#include "../arrival/arrivalUtil.h"
#include "../arrival/generateInstance.h"
#include "../arrival/preprocessInstance.h"
#include "../arrival/simpleWalk.h"
#include "../fixpoint/fixDecompAlgorithm.h"
#include "../fixpoint/kleeneTarski.h"
#include "../fixpoint/recursiveBinarySearch.h"
#include "../fixpoint/findFixpointByMonotoneDecomp.h"
#include "../simple-stochatic-game/simpleStochasticGameGenerator.h"
#include "../simple-stochatic-game/simpleStochasticGame.h"
#include <chrono>
#include <iostream>
#include <numeric>
#include <thread>

using std::chrono::duration;
using std::chrono::high_resolution_clock;
using namespace std;

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

void solveSimpleStochasticGame() {
    simpleStochasticGame g = getExampleOne();
    auto f = getDirectionFunction(g.getMonotoneFunction());

    long long queryCounter = 0;
    auto fWithCounter = [&f, &queryCounter](const vector<int_t>& v) {
        queryCounter++;
        return f(v);
    };
    auto bot = g.getBot();
    auto top = g.getTop();

    auto t1 = high_resolution_clock::now();
    auto fixpoint = findFixpointByFixDecomposition(bot, top, fWithCounter);
    auto t2 = high_resolution_clock::now();

    if(!isAllFixed(f(fixpoint))) throw runtime_error("algorithm returned a point which is not fixed!");


}

pair<int, double> solveArrival(int instanceSize,
                               algorithm algorithmToRun,
                               const function<vector<pair<int, int>>(int)>& instanceGenerator) {
    vector<pair<int, int>> instance = instanceGenerator(instanceSize);
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

pair<int, double> solveRandomArrivalWithWalk(
        int instanceSize,
        const function<vector<pair<int, int>>(int)>& instanceGenerator) {
    auto instance = instanceGenerator(instanceSize);
    auto processedInstance = preprocessInstance(instance);

    auto t1 = high_resolution_clock::now();
    auto [flows, counter] = simpleWalk(processedInstance);
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms = t2 - t1;

    return {counter, ms.count()};
}

void runAndPrintAnalysis() {
    //    auto [queryCount, time] = solveRandomArrivalWithIterate(5);
    //    auto fixpoint = findFixpointRecBin(bot, top, f);

//    vector<int> decompTestSizes{3, 6, 9, 12, 15};
    solveSimpleStochasticGame();

    vector<int> recBinTestSizes{3, 5, 7, 9};
    vector<int> decompTestSizes{7, 10, 13, 15, 18};
    vector<int> monDecompTestSizes{3, 5, 7, 9, 11, 13};
//    vector<int> decompTestSizes{7};
    //    vector<int> walkTestSizes {10, 100, 1000};//, 10000}; //, 100000, 10000000};
    int n = 1;

    string line = "==================================================\n";


    cout << line;
    cout << "STARTING DECOMP TEST" << endl;
    for (auto testSize: decompTestSizes) {
        vector<int> queryCounts{};
        vector<double> times{};

        for (int j = 0; j < n; j++) {
            auto [queryCount, time] = solveArrival(testSize, decomp, generateLongInstance);
            queryCounts.push_back(queryCount);
            times.push_back(time);
        }
        //
        double avgTime = accumulate(times.begin(), times.end(), 0.0) / n;
        double avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / n;
        cout << line;
        cout << "test size: " << testSize << endl;
        cout << "avg queries was: " << avgQueries << endl;
        cout << "avg time was: " << avgTime << "ms" << endl;
    }

    cout << line;
    cout << "STARTING RECBIN TEST" << endl;
    for(auto testSize : recBinTestSizes) {
        vector<long long> queryCounts {};
        vector<double> times {};
        for(int i = 0; i < n; i++) {
            auto [queryCount, time] = solveArrival(testSize, recbin, generateLongInstance);
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

    cout << line;
    cout << "STARTING MONDECOMP TEST" << endl;
    for(auto testSize : monDecompTestSizes) {
        vector<int> queryCounts {};
        vector<double> times {};
        for(int i = 0; i < n; i++) {
            auto [queryCount, time] = solveArrival(testSize, monotoneDecomp, generateLongInstance);
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

    cout << line;
    cout << "STARTING WALK TEST" << endl;
    for(int testSize = 3; testSize <= 15; testSize++) {
        vector<int> queryCounts {};
        vector<double> times {};
        for(int i = 0; i < n; i++) {
            auto [stepCount, time] = solveRandomArrivalWithWalk(testSize, generateLongInstance);
            queryCounts.push_back(stepCount);
            times.push_back(time);
        }

        double avgTime = accumulate(times.begin(), times.end(), 0.0) / n;
        long long avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / n;
        cout << "===========================================================" << endl;
        cout << "test size: " << testSize << endl;
        cout << "avg steps was: " << avgQueries << endl;
        cout << "avg time was: " << avgTime << "ms" << endl;
    }
}