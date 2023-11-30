//
// Created by angus on 22/11/2023.
//

#include "arrivalUtil.h"

void printInstance(const vector<pair<int, int>>& instance) {
    cout << "{ ";
    for(int i = 0; i < instance.size() - 1; i++) {
        auto succs = instance[i];
        cout << "{" << succs.first << ", " << succs.second << "}, ";
    }

    cout << "{" << instance[instance.size() - 1].first << ", " << instance[instance.size() - 1].second << "} }";


    cout << endl;
}
void printReverseInstance(const vector<vector<int>>& instance) {
    for(auto succs : instance) {
        cout << "{ ";
        for(auto coord : succs) {
            cout << coord << ", ";
        }
        cout << "}" << ", ";
    }

    cout << endl;
}
