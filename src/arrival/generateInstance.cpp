//
// Created by angus on 22/11/2023.
//

#include "generateInstance.h"
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

vector<pair<int, int>> generateLongInstance(int n) {
    vector<pair<int, int>> longInstance(n, pair<int, int>{});

    for(int i = 0; i < n - 1; i++) {
        longInstance[i].first = 0;
        longInstance[i].second = i + 1;
    }

    longInstance[n - 1].first = n - 1;
    longInstance[n - 1].second = n - 1;

    return longInstance;
}
