//
// Created by angus on 07/11/2023.
//

#include "fixDecompAlgorithm.h"
#include "threeDimensionAlgorithm.h"

vector<int> findFixpointByFixDecomposition(const vector<int>& bot,
                                           const vector<int>& top,
                                           const function<vector<direction> (const vector<int>&)>& f) {
    assert(bot.size() == top.size());
    assert(!bot.empty());

    if(bot.size() == 1) {
        // binary search
    }

    if(bot.size() == 2) {
        // dan qi ye
    }

    if(bot.size() == 3) {
        return findFixpoint3(bot, top, f);
    }

    assert(bot.size() > 3);
    vector<pair<vector<int>, vector<int>>> previouslyQueriedPairs;
    auto leftBot = vector<int> {bot.begin(), bot.begin() + 3};
    auto leftTop = vector<int> {top.begin(), top.begin() + 3};


    auto leftFunction = [&bot, &top, &f, &previouslyQueriedPairs](const auto& v) {
        auto rightFunction = [&f, &v] (const auto& w) {
            vector<int> x;
            x.insert(x.end(), v.begin(), v.end());
            x.insert(x.end(), w.begin(), w.end());

            return f(x);
        };

        auto rightBot = vector<int> {bot.begin() + 3, bot.end()};
        auto rightTop = vector<int> {top.begin() + 3, top.end()};

        for(const auto& queriedPair : previouslyQueriedPairs) {
            if(latticeLe(queriedPair.first, v)) {
                rightBot = join(std::move(rightBot), queriedPair.second);
            }

            if(latticeLe(v, queriedPair.first)) {
                rightTop = meet(std::move(rightTop), queriedPair.second);
            }
        }

        auto rightFixpoint = findFixpointByFixDecomposition(rightBot, rightTop, rightFunction);

        vector<int> leftRight;
        leftRight.insert(leftRight.end(), v.begin(), v.end());
        leftRight.insert(leftRight.end(), rightFixpoint.begin(), rightFixpoint.end());

        vector<direction> fxy = f(leftRight);

        auto queriedPair = pair<vector<int>, vector<int>> {v, rightFixpoint};
        previouslyQueriedPairs.push_back(queriedPair);

        return vector<direction> {fxy.begin(), fxy.begin() + 3};
    };

    return findFixpoint3(leftBot, leftTop, leftFunction);
}

vector<int> join(vector<int>&& a, const vector<int>& b) {
    assert(a.size() == b.size());
    for(int i = 0; i < a.size(); i++) {
        a[i] = max(a[i], b[i]);
    }

    return std::move(a);
}

vector<int> meet(vector<int>&& a, const vector<int>& b) {
    assert(a.size() == b.size());

    for(int i = 0; i < a.size(); i++) {
        a[i] = min(a[i], b[i]);
    }
    return std::move(a);
}
