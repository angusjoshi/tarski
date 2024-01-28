//
// Created by angus on 07/11/2023.
//

#include "fixDecompAlgorithm.h"
#include "threeDimensionAlgorithm.h"
#include "recursiveBinarySearch.h"
#include <iostream>



vector<int> findFixpointByFixDecomposition(const vector<int> &bot,
                                           const vector<int> &top,
                                           const function<vector<direction>(const vector<int> &)> &f) {
    assert(bot.size() == top.size());
    assert(!bot.empty());

    if (bot.size() <= 2) {
        // dan qi ye, (recursive binary search)
        return findFixpointRecBin(bot, top, f);
    }

    if (bot.size() == 3) {
        // inner algorithm based 3 dimensions
        return findFixpoint3(bot, top, f);
    }

    // else decompose per savani, fearnley, pavlogyi paper.

    assert(bot.size() > 3);

    vector<pair<vector<int>, vector<int>>> previouslyQueriedPairs{};
    vector<int> rightFixpoint{};

    auto leftFunction = [&bot, &top, &f, &previouslyQueriedPairs, &rightFixpoint](const auto &v) {
        auto rightBot = vector<int>{bot.begin() + 3, bot.end()};
        auto rightTop = vector<int>{top.begin() + 3, top.end()};

        for (const auto &queriedPair: previouslyQueriedPairs) {
            if (latticeLe(queriedPair.first, v)) {
                rightBot = join(std::move(rightBot), queriedPair.second);
            }

            if (latticeLe(v, queriedPair.first)) {
                rightTop = meet(std::move(rightTop), queriedPair.second);
            }
        }

        assert(latticeLe(rightBot, rightTop));

        auto rightFunction = [&f, &v](const auto &w) {
            vector<int> x{};
            x.insert(x.end(), v.begin(), v.end());
            x.insert(x.end(), w.begin(), w.end());

            vector<direction> result = f(x);
            return std::move(vector<direction>{result.begin() + v.size(), result.end()});
        };
        rightFixpoint = findFixpointByFixDecomposition(rightBot, rightTop, rightFunction);
        assert(isAllFixed(rightFunction(rightFixpoint)));

        vector<int> leftRight{};
        leftRight.insert(leftRight.end(), v.begin(), v.end());
        leftRight.insert(leftRight.end(), rightFixpoint.begin(), rightFixpoint.end());

        vector<direction> fxy = f(leftRight);

        auto queriedPair = pair<vector<int>, vector<int>>{v, rightFixpoint};
        previouslyQueriedPairs.push_back(queriedPair);

        return vector<direction>{fxy.begin(), fxy.begin() + v.size()};
    };

    vector<int> leftBot {bot.begin(), bot.begin() + 3};
    vector<int> leftTop {top.begin(), top.begin() + 3};
    auto leftFixpoint = findFixpoint3(leftBot, leftTop, leftFunction);

    vector<int> resultFixpoint{};
    resultFixpoint.insert(resultFixpoint.end(), leftFixpoint.begin(), leftFixpoint.end());
    resultFixpoint.insert(resultFixpoint.end(), rightFixpoint.begin(), rightFixpoint.end());

    return resultFixpoint;
}
