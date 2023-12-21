//
// Created by angus on 30/11/2023.
//

#include "arrivalInstance.h"
#include "preprocessInstance.h"
#include <iostream>
#include "arrivalUtil.h"
#include "../fixpoint/latticeUtil.h"

inline int ceilDivideByTwo(int x) {
    return x / 2 + (x % 2 != 0);
}
inline int floorDivideByTwo(int x) {
    return x / 2;
}

ArrivalInstance::ArrivalInstance(vector<pair<int, int>>&& adjList) : adjList(adjList) {
    reverseAdjList = getReverseEvenOddAdjList(adjList);
    deadEndReverseAdj = getDeadEndReverseAdj(adjList);
    flowUpperBound = 1 << adjList.size();
}

function<vector<int>(const vector<int> &)> ArrivalInstance::getIntFunction() {
    return [this] (const auto& v) {
        assert(v.size() == adjList.size() - 1);
        vector<int> result (adjList.size() - 1, 0);

        // the inflow from source.
        result[0] = 1;

        for(int i = 0; i < reverseAdjList.size() - 1; i++) {
            for(const auto j : reverseAdjList[i].first) {
                result[i] = min(flowUpperBound, result[i] + ceilDivideByTwo(v[j]));
            }

            for(const auto j : reverseAdjList[i].second) {
                result[i] = min(flowUpperBound, result[i] + floorDivideByTwo(v[j]));
            }
        }
        return result;
    };
}

function<vector<direction>(const vector<int> &)> ArrivalInstance::getDirectionFunction() {
    return ::getDirectionFunction(getIntFunction());
}

vector<int> ArrivalInstance::getBot() {
    return vector<int> (adjList.size() - 1, 0);
}
vector<int> ArrivalInstance::getTop() {
    return vector<int> (adjList.size() - 1, flowUpperBound);
}

bool ArrivalInstance::hasDiagonalEntries() {
    for(int i = 0; i < adjList.size() - 1; i++) {
        if(adjList[i].first == adjList[i].second) return true;
    }

    return false;
}
bool ArrivalInstance::hasSelfLoops() {
    for(int i = 0; i < adjList.size() - 1; i++) {
        if(adjList[i].first == i || adjList[i].second == i) return true;
    }

    return false;
}

void ArrivalInstance::print() {
    printInstance(adjList);
}


int ArrivalInstance::computeSinkInflow(const vector<int>& outflows) {
    assert(outflows.size() == adjList.size() - 1);

    int result = 0;
    for(const auto j : reverseAdjList[reverseAdjList.size() - 1].first) {
        result = min(flowUpperBound, result + ceilDivideByTwo(outflows[j]));
    }

    for(const auto j : reverseAdjList[reverseAdjList.size() - 1].second) {
        result = min(flowUpperBound, result + floorDivideByTwo(outflows[j]));
    }

    return result;
}
