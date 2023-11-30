//
// Created by angus on 22/11/2023.
//

#include "generateRandomInstance.h"
#include <random>

vector<pair<int, int>> generateRandomInstance(int instanceSize) {
    std::random_device rd;
    std::mt19937 gen(rd());
    // note the distribution uses the closed range for some reason...
    std::uniform_int_distribution<> nodeDistribution(0, instanceSize - 1);

    vector<pair<int, int>> randInstance (instanceSize, pair<int, int> {INT_MIN, INT_MIN});

    for(int i = 0; i < instanceSize - 1; i++) {
        int s0 = nodeDistribution(gen);
        int s1 = nodeDistribution(gen);

        randInstance[i].first = s0;
        randInstance[i].second = s1;
    }

    randInstance[instanceSize - 1].first = instanceSize - 1;
    randInstance[instanceSize - 1].second = instanceSize - 1;

    return std::move(randInstance);
}
