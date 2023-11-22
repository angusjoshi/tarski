//
// Created by angus on 22/11/2023.
//

#include "preprocessInstance.h"
#include <queue>
#include "arrivalUtil.h"

vector<vector<int>> getReverseAdjList(const vector<pair<int, int>>& instance) {
    vector<vector<int>> reverseAdjList (instance.size(), vector<int>{});

    for(int i = 0; i < instance.size(); i++) {
        auto succs = instance[i];
        auto s0 = succs.first;
        auto s1 = succs.second;

        reverseAdjList[s0].push_back(i);
        reverseAdjList[s1].push_back(i);
    }

    return std::move(reverseAdjList);
}

vector<pair<int, int>> preprocessInstance(const vector<pair<int, int>>& instance) {
    assert(instance.size() >= 2);
    auto reverseAdjList = getReverseAdjList(instance);

    cout << "\n\n\n ===============REVERSE=============\n";
    printReverseInstance(reverseAdjList);

    queue<size_t> bfsStack {};
    bfsStack.push(instance.size() - 1);
    vector<bool> seenBefore (instance.size(), false);
    seenBefore[instance.size() - 1] = true;

    while(!bfsStack.empty()) {
        auto i = bfsStack.front();
        bfsStack.pop();

        for(auto reverseAdj : reverseAdjList[i]) {
            if(seenBefore[reverseAdj]) continue;

            bfsStack.push(reverseAdj);
            seenBefore[reverseAdj] = true;
        }
    }

    vector<pair<int, int>> newInstance { instance.begin(), instance.end() };
    for(int i = 0; i < seenBefore.size(); i++) {
        if(seenBefore[i]) continue;

        for(int j = 0; j < newInstance.size(); j++) {
            newInstance[j].first = newInstance[j].first != i ? newInstance[j].first : -1;
            newInstance[j].second = newInstance[j].second != i ? newInstance[j].second : -1;
        }

    }

    return std::move(newInstance);
}
