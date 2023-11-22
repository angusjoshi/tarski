//
// Created by angus on 22/11/2023.
//

#include "arrivalUtil.h"

void printInstance(const vector<pair<int, int>>& instance) {
    for(auto succs : instance) {
        cout << "{" << succs.first << ", " << succs.second << "} ";
    }

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
