//
// Created by angus on 22/11/2023.
//

#ifndef SRC_PREPROCESSINSTANCE_H
#define SRC_PREPROCESSINSTANCE_H
#include <vector>

using namespace std;

vector<vector<int>> getReverseAdjList(const vector<pair<int, int>>& instance);
vector<pair<vector<int>, vector<int>>> getReverseEvenOddAdjList(const vector<pair<int, int>>& preprocessedInstance);
pair<vector<int>, vector<int>> getDeadEndReverseAdj(const vector<pair<int, int>>& preprocessedInstance);
vector<pair<int, int>> preprocessInstance(const vector<pair<int, int>>& instance);

#endif //SRC_PREPROCESSINSTANCE_H
