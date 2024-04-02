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
#include "../shapley-stochastic-game/shapleyStochasticGame.h"
#include "../shapley-stochastic-game/shapleyStochasticGameGenerator.h"
#include "../fixpoint/valueIteration.h"

using std::chrono::duration;
using std::chrono::high_resolution_clock;
using namespace std;

enum algorithm {
    recbin,
    decomp,
    monotoneDecomp,
    iterate,
    lastEntry,
};
string algToString(algorithm a) {
    switch(a) {
        case recbin: return "recbin";
        case decomp: return "decomp";
        case monotoneDecomp: return "monotoneDecmop";
        case iterate: return "iterate";
        default: return "";
    }
}

void printAlgorithmType(algorithm a) {
    cout << "algorithm type: " << algToString(a) << endl;
}


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

pair<int, double> solveShapleyStochasticGame(int size, algorithm algorithmToRun, f_t eps) {
    shapleyStochasticGame g = generateShapleyStochasticGame(size, eps);

    auto normalF = g.getMonotoneFunction();
    auto f = getDirectionFunction(normalF);

    long long queryCounter = 0;
    auto normalFWithCounter = [&normalF, f, &queryCounter](const vector<int_t>& v) -> vector<int_t> {
        queryCounter++;
        return normalF(v);
    };

    auto fWithCounter = [&f, &queryCounter](const vector<int_t>& v) -> vector<direction> {
        queryCounter++;
        return f(v);
    };
    auto bot = g.getBot();
    auto top = g.getTop();

    auto t1 = high_resolution_clock::now();
    auto fixpoint = algorithmToRun == decomp
                    ? findFixpointByFixDecomposition(bot, top, fWithCounter)
                    : algorithmToRun == monotoneDecomp
                    ? findFixpointByMonotoneDecomp(bot, top, fWithCounter)
                    : algorithmToRun == recbin
                    ? findFixpointRecBin(bot, top, fWithCounter)
                    : kleeneTarski(bot, normalFWithCounter);
    auto t2 = high_resolution_clock::now();

    if(!isAllFixed(f(fixpoint))) throw runtime_error("algorithm returned a point which is not fixed!");
    duration<double, std::milli> ms = t2 - t1;
    return {queryCounter, ms.count()};
}

pair<int, double> valIterateShapleyStochasticGame(int instanceSize,
                                                 f_t eps = 0.01) {
    shapleyStochasticGame g = generateShapleyStochasticGame(instanceSize, eps);
    auto f = g.getCtsMonotoneFunction();

    long long queryCounter = 0;

    auto fWithCounter = [&f, &queryCounter](const vector<f_t>& v) {
        queryCounter++;
        return f(v);
    };

    auto start = g.getCtsStart();

    auto t1 = high_resolution_clock::now();
    auto fixpoint = valueIteration(fWithCounter, start, eps * g.q);
    auto t2 = high_resolution_clock::now();

    auto fFix = f(fixpoint);
    if(dist(fixpoint, fFix) > eps) throw runtime_error("algorithm returned a point which is not almost fixed!");
    duration<double, std::milli> ms = t2 - t1;
    return {queryCounter, ms.count()};
}

pair<int, double> valIterateSimpleStochasticGame(int instanceSize,
                                             f_t eps = 0.01) {
    simpleStochasticGame g = generateSimpleStochasticGame(instanceSize, eps);
    auto f = g.getCtsMonotoneFunction();

    long long queryCounter = 0;

    auto fWithCounter = [&f, &queryCounter](const vector<f_t>& v) {
        queryCounter++;
        return f(v);
    };

    auto start = g.getCtsStart();

    auto t1 = high_resolution_clock::now();
    auto fixpoint = valueIteration(fWithCounter, start, eps * (1 - g.contractionFactor));
    auto t2 = high_resolution_clock::now();

    auto fFix = f(fixpoint);
    if(dist(fixpoint, fFix) > eps) throw runtime_error("algorithm returned a point which is not almost fixed!");
    duration<double, std::milli> ms = t2 - t1;
    return {queryCounter, ms.count()};
}

pair<int, double> solveSimpleStochasticGame(int instanceSize,
                               algorithm algorithmToRun, f_t eps = 0.01) {
    simpleStochasticGame g = generateSimpleStochasticGame(instanceSize, eps);
    auto normalF = g.getMonotoneFunction();
    auto f = getDirectionFunction(normalF);

    long long queryCounter = 0;
    auto normalFWithCounter = [&normalF, &f, &queryCounter](const vector<int_t>& v) {
        queryCounter++;
        return normalF(v);
    };

    auto fWithCounter = [&f, &queryCounter](const vector<int_t>& v) {
        queryCounter++;
        return f(v);
    };
    auto bot = g.getBot();
    auto top = g.getTop();

    auto t1 = high_resolution_clock::now();
    auto fixpoint = algorithmToRun == decomp
                    ? findFixpointByFixDecomposition(bot, top, fWithCounter)
                    : algorithmToRun == monotoneDecomp
                    ? findFixpointByMonotoneDecomp(bot, top, fWithCounter)
                    : algorithmToRun == recbin
                    ? findFixpointRecBin(bot, top, fWithCounter)
                    : kleeneTarski(bot, normalFWithCounter);

//    auto fixpoint =
    auto t2 = high_resolution_clock::now();
    auto soln = g.unDiscretize(fixpoint);

    if(!isAllFixed(f(fixpoint))) throw runtime_error("algorithm returned a point which is not fixed!");

    duration<double, std::milli> ms = t2 - t1;
    return {queryCounter, ms.count()};
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

    auto normalG = arrivalInstance.getIntFunction();

    long long queryCounter = 0;
    auto f = [&g, &queryCounter](const auto &v) {
        queryCounter++;
        return g(v);
    };
    auto normalFWithCounter = [&normalG, &queryCounter](const auto& v) {
        queryCounter++;
        return normalG(v);
    };

    auto t1 = high_resolution_clock::now();
    auto fixpoint = algorithmToRun == decomp
                    ? findFixpointByFixDecomposition(bot, top, f)
                    : algorithmToRun == monotoneDecomp
                    ? findFixpointByMonotoneDecomp(bot, top, f)
                    : algorithmToRun == recbin
                    ? findFixpointRecBin(bot, top, f)
                    : kleeneTarski(bot, normalFWithCounter);


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
//    solveSimpleStochasticGame();
//    solveShapleyStochasticGame();
//    return;

    vector<int> recBinTestSizes{3, 5, 7, 9};
    vector<int> longRecBin{3, 6, 9, 12, 15};
    vector<int> decompTestSizes{3, 7, 10, 13, 15, 18, 24};
    vector<int> monDecompTestSizes{3, 5, 7, 9, 11, 13};

    vector<int> simpleStochasticTestSizes{3, 5, 7, 9, 11, 13};
    vector<int> shapleyTestSizes{2, 3, 4, 5, 6};
    vector<int> shapleyWalkSizes {10, 15, 20, 30, 40};
    vector<int> walkTestSizes {10, 100, 1000, 10000, 100000, 100000};
    vector<int> longWalkTestSizes {3, 6, 11, 17, 22, 27};
    vector<f_t> epsilons {0.5, 0.1, 0.01, 0.001, 0.0001};//, 0.00001, 0.000001};

    unordered_map<algorithm, vector<int>> testSizes {
            { recbin, longRecBin },
            { decomp, decompTestSizes },
            { monotoneDecomp, monDecompTestSizes },
            { iterate, longWalkTestSizes },
    };

    int n = 20;
    string line = "==================================================\n";

    cout << "STARTING SIMPLE STOCHASTIC VALUE ITERATION TEST" << endl;
    cout << line;
    for(int testSize : walkTestSizes) {
        vector<int> queryCounts {};
        vector<double> times {};
        for(int i = 0; i < n; i++) {
            auto [stepCount, time] = valIterateSimpleStochasticGame(testSize + 1, 0.01);
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

    cout << "STARTING SHAPLEY STOCHASTIC VALUE ITERATION TEST" << endl;
    cout << line;
    for(int testSize : shapleyWalkSizes) {
        vector<int> queryCounts {};
        vector<double> times {};
        for(int i = 0; i < n; i++) {
            auto [stepCount, time] = valIterateShapleyStochasticGame(testSize + 1, 0.01);
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

    cout << "STARTING LONG ARRIVAL EPSILON TEST" << endl;
    for(int algI = recbin; algI != lastEntry; algI++) {
        auto alg = static_cast<algorithm>(algI);
        cout << line;
        printAlgorithmType(alg);
        for(int testSize : testSizes[alg]) {
            vector<int> queryCounts {};
            vector<double> times {};
            for(int i = 0; i < n; i++) {
                auto [stepCount, time] = solveArrival(testSize, alg, generateLongInstance);
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

    cout << "STARTING SIMPLE STOCHASTIC GAME EPSILON TEST" << endl;
    for(int algI = recbin; algI != lastEntry; algI++) {
        auto alg = static_cast<algorithm>(algI);
        cout << line;
        printAlgorithmType(alg);
        for(f_t epsilon : epsilons) {
            int testSize = 11;
            vector<int> queryCounts {};
            vector<double> times {};
            for(int i = 0; i < n; i++) {
                auto [stepCount, time] = solveSimpleStochasticGame(testSize, alg, epsilon);
                queryCounts.push_back(stepCount);
                times.push_back(time);
            }

            double avgTime = accumulate(times.begin(), times.end(), 0.0) / n;
            long long avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / n;
            cout << "===========================================================" << endl;
            cout << "test size: " << testSize << endl;
            cout << "epsilon: " << epsilon << endl;
            cout << "avg steps was: " << avgQueries << endl;
            cout << "avg time was: " << avgTime << "ms" << endl;
        }
    }

    cout << "STARTING SHAPLEY STOCHASTIC GAME EPSILON TEST" << endl;
    for(int algI = recbin; algI != lastEntry; algI++) {
        auto alg = static_cast<algorithm>(algI);
        if(alg == recbin) continue;

        cout << line;
        printAlgorithmType(alg);
        for(f_t epsilon : epsilons) {
            int testSize = 6;
            vector<int> queryCounts {};
            vector<double> times {};
            for(int i = 0; i < n; i++) {
                auto [stepCount, time] = solveShapleyStochasticGame(testSize, alg, epsilon);
                queryCounts.push_back(stepCount);
                times.push_back(time);
            }

            double avgTime = accumulate(times.begin(), times.end(), 0.0) / n;
            long long avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / n;
            cout << "===========================================================" << endl;
            cout << "test size: " << testSize << endl;
            cout << "epsilon: " << epsilon << endl;
            cout << "avg steps was: " << avgQueries << endl;
            cout << "avg time was: " << avgTime << "ms" << endl;
        }
    }

    cout << "STARTING SIMPLE STOCHASTIC GAME TEST" << endl;

    for(int algI = recbin; algI != lastEntry; algI++) {
        auto alg = static_cast<algorithm>(algI);
        cout << line;
        printAlgorithmType(alg);
        for(int testSize : simpleStochasticTestSizes) {
            vector<int> queryCounts {};
            vector<double> times {};
            for(int i = 0; i < n; i++) {
                auto [stepCount, time] = solveSimpleStochasticGame(testSize + 1, alg);
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
    cout << line;
    cout << "STARTING SHAPLEY STOCHASTIC GAME TEST" << endl;
    for(int algI = recbin; algI != lastEntry; algI++) {
        auto alg = static_cast<algorithm>(algI);
        cout << line;
        printAlgorithmType(alg);
        cout << line;
        for(int testSize : shapleyTestSizes) {
            vector<int> queryCounts {};
            vector<double> times {};
            for(int i = 0; i < n; i++) {
                auto [stepCount, time] = solveShapleyStochasticGame(testSize, alg, 0.01);
                queryCounts.push_back(stepCount);
                times.push_back(time);
            }

            double avgTime = accumulate(times.begin(), times.end(), 0.0) / n;
            long long avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / n;
            cout << "===========================================================" << endl;
            cout << "test size: " << testSize << endl;
            cout << "avg queries was: " << avgQueries << endl;
            cout << "avg time was: " << avgTime << "ms" << endl;
        }
    }

    cout << line;
    cout << "STARTING SHAPLEY STOCHASTIC GAME WALK TEST" << endl;
    cout << line;
    for(int testSize : shapleyWalkSizes) {
        vector<int> queryCounts {};
        vector<double> times {};
        for(int i = 0; i < n; i++) {
            auto [stepCount, time] = solveShapleyStochasticGame(testSize, iterate, 0.01);
            queryCounts.push_back(stepCount);
            times.push_back(time);
        }

        double avgTime = accumulate(times.begin(), times.end(), 0.0) / n;
        long long avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / n;
        cout << "===========================================================" << endl;
        cout << "test size: " << testSize << endl;
        cout << "avg queries was: " << avgQueries << endl;
        cout << "avg time was: " << avgTime << "ms" << endl;
    }


    cout << line;
    cout << "STARTING SIMPLE STOCHASTIC GAME WALK TEST" << endl;
    cout << line;
    for(int testSize : walkTestSizes) {
        vector<int> queryCounts {};
        vector<double> times {};
        for(int i = 0; i < n; i++) {
            auto [stepCount, time] = solveSimpleStochasticGame(testSize, iterate);
            queryCounts.push_back(stepCount);
            times.push_back(time);
        }

        double avgTime = accumulate(times.begin(), times.end(), 0.0) / n;
        long long avgQueries = accumulate(queryCounts.begin(), queryCounts.end(), 0) / n;
        cout << "===========================================================" << endl;
        cout << "test size: " << testSize << endl;
        cout << "avg queries was: " << avgQueries << endl;
        cout << "avg time was: " << avgTime << "ms" << endl;
    }

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

        cout << line;
        cout << "STARTING KLEENETARSKI TEST" << endl;
        for(auto testSize : walkTestSizes) {
            vector<int> queryCounts {};
            vector<double> times {};
            for(int i = 0; i < n; i++) {
                auto [queryCount, time] = solveRandomArrivalWithIterate(testSize);
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