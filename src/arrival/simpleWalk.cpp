//
// Created by angus on 22/11/2023.
//

#include "simpleWalk.h"
#include <iostream>

bool simpleWalk(const vector<pair<int, int>>& instance) {
    vector<bool> switches(instance.size(), false);

    int current = 0;
    while(current != instance.size() - 1) {
        if(current == -1) return false;
        if(!switches[current]) {
            // 0 succ
            current = instance[current].first;
        } else {
            // 1 succ
            current = instance[current].second;
        }

        switches[current] = !switches[current];
    }

    return true;
}
