//
// Created by angus on 22/11/2023.
//

#include "preprocessInstance.h"
#include "arrivalUtil.h"
#include <queue>

pair<vector<int>, vector<int>>
getDeadEndReverseAdj(const vector<pair<int, int>> &instance) {
  pair<vector<int>, vector<int>> result{{}, {}};
  for (int i = 0; i < instance.size() - 1; i++) {
    // don't add the self loops at sink here.

    auto succs = instance[i];
    auto s0 = succs.first;
    auto s1 = succs.second;

    if (s0 == -1) {
      result.first.push_back(i);
    }
    if (s1 == -1) {
      result.second.push_back(i);
    }
  }

  return std::move(result);
}
vector<pair<vector<int>, vector<int>>>
getReverseEvenOddAdjList(const vector<pair<int, int>> &instance) {
  vector<pair<vector<int>, vector<int>>> reverseAdjList(instance.size(),
                                                        {{}, {}});

  for (int i = 0; i < instance.size() - 1; i++) {
    auto succs = instance[i];
    auto s0 = succs.first;
    auto s1 = succs.second;

    if (s0 != -1) {
      reverseAdjList[s0].first.push_back(i);
    }
    if (s1 != -1) {
      reverseAdjList[s1].second.push_back(i);
    }
  }

  return std::move(reverseAdjList);
}

vector<vector<int>> getReverseAdjList(const vector<pair<int, int>> &instance) {
  vector<vector<int>> reverseAdjList(instance.size(), vector<int>{});

  for (int i = 0; i < instance.size(); i++) {
    auto succs = instance[i];
    auto s0 = succs.first;
    auto s1 = succs.second;

    reverseAdjList[s0].push_back(i);
    reverseAdjList[s1].push_back(i);
  }

  return std::move(reverseAdjList);
}

vector<pair<int, int>>
preprocessInstance(const vector<pair<int, int>> &instance) {
  assert(instance.size() >= 2);
  auto reverseAdjList = getReverseAdjList(instance);

  queue<int> bfsQueue{};
  bfsQueue.push(instance.size() - 1);
  vector<bool> seenBefore(instance.size(), false);
  seenBefore[instance.size() - 1] = true;
  // vector<int> nextNodes{};
  // int dist = 1;
  // for (auto node : reverseAdjList[instance.size() - 1]) {
  //   nextNodes.push_back(node);
  //   seenBefore[node] = true;
  // }

  while (!bfsQueue.empty()) {
    auto i = bfsQueue.front();
    bfsQueue.pop();

    for (auto reverseAdj : reverseAdjList[i]) {
      if (seenBefore[reverseAdj])
        continue;

      bfsQueue.push(reverseAdj);
      seenBefore[reverseAdj] = true;
    }
  }

  vector<pair<int, int>> newInstance{instance.begin(), instance.end()};
  for (auto &succs : newInstance) {
    if (!seenBefore[succs.first])
      succs.first = -1;
    if (!seenBefore[succs.second])
      succs.second = -1;
  }

  return std::move(newInstance);
}
