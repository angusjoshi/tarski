//
// Created by angus on 07/11/2023.
//

#include "recursiveBinarySearch.h"
#include <iostream>

bool allButLastFixed(const vector<direction>& v) {
    for(int i = 0; i < v.size() - 1; i++) {
        if(v[i] != fix) return false;
    }
    return true;
}
int binarySearch(int bot, int top, const function<direction(int)>& f) {
    int currentMid = bot + ((top - bot) / 2);
    direction fCurrentMid = f(currentMid);

    while(fCurrentMid != fix) {
        if(top - bot <= 1) {
            if(bot == currentMid) {
                return top;
            }
            return bot;
        }
        if(fCurrentMid == down) {
            top = currentMid;
        } else {
            bot = currentMid;
        }

        currentMid = (top + bot) / 2;
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
        vector<int> result {resultVal};
        return std::move(result);
    }

    assert(bot.size() > 1);

    auto currentBot = bot;
    auto currentTop = top;

    bool useCeilDivision = false;

    while(true) {
        int botPlusTop = currentTop.back() + currentBot.back();
        int currentMid = botPlusTop / 2;
        if(useCeilDivision) {
            currentMid += botPlusTop % 2 == 1 ? 1 : 0;
        }

        auto sliceFunction  = [&f, currentMid] (vector<int> v) {
            v.push_back(currentMid);
            auto result = f(v);
            result.pop_back();
            return result;
        };

        vector<int> sliceBot {bot.begin(), bot.end() - 1};
        vector<int> sliceTop {top.begin(), top.end() - 1};

        vector<int> sliceFixpoint = findFixpointRecBin(sliceBot, sliceTop, sliceFunction);

        vector<int> other {sliceFixpoint.begin(), sliceFixpoint.end()};
        other.push_back(currentMid);
        vector<direction> result = f(other);

        assert(allButLastFixed(result));

        if(result.back() == fix) {
            return other;
        }

        if(currentTop.back() - currentBot.back() <= 1) {
            useCeilDivision = !useCeilDivision;
        }

        assert(result.back() != fix);
        if(result.back() == down) currentTop = other;
        if(result.back() == up) currentBot = other;
    }
}