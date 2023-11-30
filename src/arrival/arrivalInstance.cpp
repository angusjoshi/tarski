//
// Created by angus on 30/11/2023.
//

#include "arrivalInstance.h"
#include "preprocessInstance.h"
#include <iostream>
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

function<vector<direction>(const vector<int> &)> ArrivalInstance::getDirectionFunction() {
    auto f = [this] (const auto& v) {
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

    return ::getDirectionFunction(f);
}

vector<int> ArrivalInstance::getBot() {
    return vector<int> (adjList.size() - 1, 0);
}
vector<int> ArrivalInstance::getTop() {
    return vector<int> (adjList.size() - 1, flowUpperBound);
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
