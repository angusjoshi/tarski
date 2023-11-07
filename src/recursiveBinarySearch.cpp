//
// Created by angus on 07/11/2023.
//

#include "recursiveBinarySearch.h"

int binarySearch(int bot, int top, const function<direction(int)>& f) {
    int currentMid = (top - bot) / 2;
    int fCurrentMid = f(currentMid);

    while(fCurrentMid != currentMid) {
        if(fCurrentMid < currentMid) {
            top = currentMid;
        } else {
            bot = currentMid;
        }

        currentMid = (top - bot) / 2;
        fCurrentMid = f(currentMid);
    }

    return currentMid;
}

vector<int> findFixpointRecBin(const vector<int>& bot,
                               const vector<int>& top,
                               const function<vector<direction>(const vector<int>&)>& f) {
    assert(bot.size() == top.size());
    assert(!bot.empty());

    if(bot.size() == 1) {
        int botVal = bot[0];
        int topVal = top[0];

        auto oneDimensionF = [&f] (int x) {
            vector<int> v {x};

            return f(v)[0];
        };

        int resultVal = binarySearch(botVal, topVal, oneDimensionF);
        return vector<int> {resultVal};
    }

    assert(bot.size() > 1);

    auto function = [&f, &bot, &top] (int x) {
        auto sliceFunction  = [&f, x] (vector<int> v) {
            v.push_back(x);
            auto result = f(v);
            result.pop_back();
            return result;
        };

        vector<int> sliceBot {bot.begin(), bot.end() - 1};
        vector<int> sliceTop {top.begin(), top.end() - 1};

        vector<int> sliceFixpoint = findFixpointRecBin(sliceBot, sliceTop, sliceFunction);
        sliceFixpoint.push_back(x);
        vector<direction> result = f(sliceBot);
        return result.back();
    };

    return vector<int> {};
}
