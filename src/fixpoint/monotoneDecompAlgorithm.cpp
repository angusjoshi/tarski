//
// Created by angus on 27/01/2024.
//

#include "monotoneDecompAlgorithm.h"
#include "latticeUtil.h"
#include "innerAlgorithm.h"
#include "recursiveBinarySearch.h"

typedef struct bounds {
    vector<int> bot;
    vector<int> top;
} bounds;

typedef struct previousRound {
    vector<int> queriedPoint;
    bounds b;
} previousRound;

bounds findBounds(const vector<int>& bot,
                     const vector<int>& top,
                     const function<vector<direction>(const vector<int> &)> &f) {
    // this is refinedTarski in the Chen, Li paper.
    bounds b = {bot, top};
    size_t n = bot.size();
    vector<direction> resultDirs{};
    auto fPlus = [&f, n, &resultDirs](const auto& v) {
        resultDirs = f(v);

        vector<direction> result{resultDirs.begin(), resultDirs.end()};
        if(result[n] == fix) {
            result[n] = up;
        }
        return result;
    };

    auto plusMonotonePoint = findMonotonePointByDecomposition(b.bot, b.top, fPlus);
    if(plusMonotonePoint.second[n] == up) {
        b.bot = plusMonotonePoint.first;
    } else {
        assert(plusMonotonePoint.second[n] == down);
        b.top = plusMonotonePoint.first;
    }

    // hacky using the last queried result in the function
    if(resultDirs[n] != fix) {
        return b;
    }

    auto fMinus = [&f, n](const auto& v) {
        vector<direction> result = f(v);

        if(result[n] == fix) {
            result[n] = down;
        }
        return result;
    };

    auto minusMonotonePoint = findMonotonePointByDecomposition(b.bot, b.top, fMinus);

    if(minusMonotonePoint.second[n] == up) {
        b.bot = minusMonotonePoint.first;
    } else {
        assert(minusMonotonePoint.second[n] == down);
        b.top = minusMonotonePoint.first;
    }

    return b;
}

pair<vector<int>, vector<direction>> findMonotonePointByDecomposition(const vector<int> &bot,
                                             const vector<int> &top,
                                             const function<vector<direction>(const vector<int> &)> &f) {
    if(bot.size() == 1) {
        // use normal bin search
        int botVal = bot[0];
        int topVal = top[0];

        vector<direction> dirs{};
        auto oneDimensionF = [&f, &dirs] (int x) {
            vector<int> v {x};
            dirs = f(v);
            return dirs[0];
        };

        int resultVal = binarySearch(botVal, topVal, oneDimensionF);
        vector<int> result {resultVal};
        return {result, dirs};
    }

    if(bot.size() == 2) {
        // use inner algorithm
        InnerAlgorithm innerAlgorithm{bot, top, f};
        return innerAlgorithm.findMonotonePoint();
    }

    assert(bot.size() > 2);

    vector<previousRound> previousRounds{};
    bounds lBounds{};
    vector<direction> lDirs{};

    auto rFunction = [&bot, &top, &f, &previousRounds, &lBounds, &lDirs](const auto& v) {
        lBounds = {
                vector<int>{bot.begin(), bot.end() - 2},
                vector<int>{top.begin(), top.end() - 2},
        };

        for(const auto& previousRound : previousRounds) {
            if(latticeLe(previousRound.queriedPoint, v)) {
                lBounds.bot = join(std::move(lBounds.bot), previousRound.b.bot);
            }
            if(latticeLe(v, previousRound.queriedPoint)) {
                lBounds.top = meet(std::move(lBounds.top), previousRound.b.top);
            }
        }

        for(int i = v.size() - 3; i < v.size() + 1; i++) {
            auto lFunction = [&v, &f, i](const auto& w) {
                vector<int> x{};
                x.insert(x.end(), w.begin(), w.end());
                x.insert(x.end(), v.begin(), v.end());
                vector<direction> fx = f(x);

                // sub 3 since the result has 1 more component.
                vector<direction> result {fx.begin(), fx.end() - 3};
                result.push_back(fx[i]);
                return result;
            };

            lBounds = findBounds(lBounds.bot, lBounds.top, lFunction);
        }

        vector<int> leftRight{};
        leftRight.insert(leftRight.end(), lBounds.bot.begin(), lBounds.bot.end());
        leftRight.insert(leftRight.end(), v.begin(), v.end());
        auto flr = f(leftRight);

        previousRounds.push_back({v, lBounds});
        lDirs = vector<direction> {flr.begin(), flr.begin() + v.size()};
        return lDirs;
    };

    vector<int> rBot {bot.end() - 2, bot.end()};
    vector<int> rTop {top.end() - 2, top.end()};
    auto rMonotonePoint = findMonotonePointByDecomposition(rBot, rTop, rFunction);

    if(isAllWeakUp(rMonotonePoint.second)) {
        vector<int> resultVec{lBounds.bot.begin(), lBounds.bot.end()};
        resultVec.insert(resultVec.end(), rMonotonePoint.first.begin(), rMonotonePoint.first.end());

        // big hack here - the last call to lFunction must be the one that found the
        // monotone point for this to be correct. kind of reasonable but should probably be changed.
        vector<direction> resultDirs{lDirs.begin(), lDirs.end()};
        resultDirs.insert(resultDirs.end(), rMonotonePoint.second.begin(), rMonotonePoint.second.end());

        return {resultVec, resultDirs};
    }

    assert(isAllWeakDown(rMonotonePoint.second));
    vector<int> resultVec{lBounds.top.begin(), lBounds.top.end()};
    resultVec.insert(resultVec.end(), rMonotonePoint.first.begin(), rMonotonePoint.first.end());

    // big hack as above
    vector<direction> resultDirs{lDirs.begin(), lDirs.end()};
    resultDirs.insert(resultDirs.end(), rMonotonePoint.second.begin(), rMonotonePoint.second.end());
    return {resultVec, resultDirs};
}
