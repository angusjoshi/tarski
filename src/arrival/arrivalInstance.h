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
    int_t flowUpperBound;
    vector<int_t> flowUpperBounds;


public:
    bool hasDiagonalEntries();
    bool hasSelfLoops();
    void print();
    ArrivalInstance(vector<pair<int, int>>&& adjList);
    function<vector<direction>(const vector<int_t> &)> getDirectionFunction();
    function<vector<int_t>(const vector<int_t> &)> getIntFunction();
    vector<int_t> getBot();
    vector<int_t> getTop();
    int_t computeSinkInflow(const vector<int_t>& outflows);

};
#endif //SRC_ARRIVALINSTANCE_H
