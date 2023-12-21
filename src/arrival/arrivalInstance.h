//
// Created by angus on 30/11/2023.
//

#ifndef SRC_ARRIVALINSTANCE_H
#define SRC_ARRIVALINSTANCE_H

#include <functional>
#include "../fixpoint/monotoneFunction.h"

class ArrivalInstance {
private:
    vector<pair<int, int>> adjList;
    vector<pair<vector<int>, vector<int>>> reverseAdjList;
    pair<vector<int>, vector<int>> deadEndReverseAdj;
    int flowUpperBound;


public:
    bool hasDiagonalEntries();
    bool hasSelfLoops();
    void print();
    ArrivalInstance(vector<pair<int, int>>&& adjList);
    function<vector<direction>(const vector<int> &)> getDirectionFunction();
    function<vector<int>(const vector<int> &)> getIntFunction();
    vector<int> getBot();
    vector<int> getTop();
    int computeSinkInflow(const vector<int>& outflows);

};
#endif //SRC_ARRIVALINSTANCE_H
