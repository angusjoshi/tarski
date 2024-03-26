//
// Created by angus on 07/11/2023.
//

#include "recursiveBinarySearch.h"

bool allButLastFixed(const vector<direction>& v) {
    for(int i = 0; i < v.size() - 1; i++) {
        if(v[i] != fix) return false;
    }
    return true;
}

int_t binarySearch(int_t bot, int_t top, const function<direction(const int_t&)>& f) {
    int_t currentMid = bot + ((top - bot) / 2);
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


vector<int_t> findFixpointRecBin(const vector<int_t>& bot,
                               const vector<int_t>& top,
                               const function<vector<direction>(const vector<int_t>&)>& f) {
    assert(bot.size() == top.size());
    assert(!bot.empty());

    if(bot.size() == 1) {
        int_t botVal = bot[0];
        int_t topVal = top[0];

        auto oneDimensionF = [&f] (const int_t& x) {
            vector<int_t> v {x};
            return f(v)[0];
        };

        int_t resultVal = binarySearch(botVal, topVal, oneDimensionF);
        vector<int_t> result {resultVal};
        return result;
    }

    assert(bot.size() > 1);

    auto currentBot = bot;
    auto currentTop = top;

    bool useCeilDivision = false;

    while(true) {
        int_t botPlusTop = currentTop.back() + currentBot.back();
        int_t currentMid = botPlusTop / 2;
        if(useCeilDivision) {
            currentMid += botPlusTop % 2;
        }

        auto sliceFunction  = [&f, currentMid] (vector<int_t> v) {
            v.push_back(currentMid);
            auto result = f(v);
            result.pop_back();
            return result;
        };

        vector<int_t> sliceBot {currentBot.begin(), currentBot.end() - 1};
        vector<int_t> sliceTop {currentTop.begin(), currentTop.end() - 1};

        vector<int_t> sliceFixpoint = findFixpointRecBin(sliceBot, sliceTop, sliceFunction);

        vector<int_t> other {sliceFixpoint.begin(), sliceFixpoint.end()};
        other.push_back(currentMid);
        vector<direction> result = f(other);

        assert(allButLastFixed(result));

        if(result.back() == fix) {
            return other;
        }

        if(abs(currentTop.back() - currentBot.back()) <= 1) {
            useCeilDivision = !useCeilDivision;
        }

        assert(result.back() != fix);
        if(result.back() == down) currentTop = other;
        if(result.back() == up) currentBot = other;
    }
}