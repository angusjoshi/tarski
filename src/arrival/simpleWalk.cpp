//
// Created by angus on 22/11/2023.
//

#include "simpleWalk.h"
#include <iostream>

pair<vector<long long>, long long> simpleWalk(const vector<pair<int, int>>& instance) {
    vector<bool> switches(instance.size(), false);
    vector<long long> flows(instance.size(), 0);
    int current = 0;
    long long counter = 0;
    while(current != instance.size() - 1) {
        if(current == -1) return { flows, counter };

        flows[current]++;

        bool currentSwitch = switches[current];
        switches[current] = !switches[current];
        if(!currentSwitch) {
            // 0 succ
            current = instance[current].first;
        } else {
            // 1 succ
            current = instance[current].second;
        }

        counter++;
    }

    flows[current]++;

    return {flows, counter};
}
