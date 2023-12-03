//
// Created by angus on 22/11/2023.
//

#include "simpleWalk.h"
#include <iostream>

long long simpleWalk(const vector<pair<int, int>>& instance) {
    vector<bool> switches(instance.size(), false);
    int current = 0;
    long long counter = 0;
    while(current != instance.size() - 1) {
        if(current == -1) return counter;

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

    return counter;
}
