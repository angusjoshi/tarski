//
// Created by angus on 27/01/2024.
//

#include "monotoneDecompAlgorithm.h"
#include "latticeUtil.h"
#include "innerAlgorithm.h"
#include "recursiveBinarySearch.h"

typedef struct {
    vector<int_t> bot;
    vector<int_t> top;
} bounds;

typedef struct {
    vector<int_t> queriedPoint;
    bounds b;
    vector<direction> result;
} previousRound;

bool isMonotone(const vector<int_t>& v,
    const function<vector<direction>(const vector<int_t> &)> &f) {
    auto result = f(v);
    return isAllWeakDown(result) || isAllWeakUp(result);
}

bounds findBounds(const vector<int_t>& bot,
                     const vector<int_t>& top,
                     const function<vector<direction>(const vector<int_t> &)> &f) {
    // this is refinedTarski in the Chen, Li paper.
    bounds b = {bot, top};
    size_t n = bot.size();
    auto fPlus = [&f, n](const vector<int_t>& v) {
        vector<direction> result = f(v);
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

    vector<direction> resultDirs = f(plusMonotonePoint.first);
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

pair<vector<int_t>, vector<direction>> findMonotonePointByDecomposition(const vector<int_t> &bot,
                                             const vector<int_t> &top,
                                             const function<vector<direction>(const vector<int_t> &)> &f) {
    assert(!bot.empty());

    if(bot.size() == 1) {
        int_t botVal = bot[0];
        int_t topVal = top[0];

        vector<direction> dirs{};
        auto oneDimensionF = [&f, &dirs] (const int_t& x) {
            vector<int_t> v {x};
            dirs = f(v);
            return dirs[0];
        };

        int_t resultVal = binarySearch(botVal, topVal, oneDimensionF);
        vector<int_t> result {resultVal};
        vector<direction> resultDirs {f(result)};
        return {result, resultDirs};
    }

    if(bot.size() == 2) {
        InnerAlgorithm innerAlgorithm{bot, top, f};
        return innerAlgorithm.findMonotonePoint();
    }

    assert(bot.size() > 2);

    vector<previousRound> previousRounds{};
    bounds lBounds{};
    vector<direction> lDirs{};

    auto rFunction = [&bot, &top, &f, &previousRounds, &lBounds, &lDirs](const auto& v) {
        // return memoized results
        for(const auto& round : previousRounds) {
            if(latEq(round.queriedPoint, v)) {
                vector<direction> prev = round.result;
                lBounds = round.b;
                return prev;
            }
        }

        lBounds = {
                vector<int_t>{bot.begin(), bot.end() - 2},
                vector<int_t>{top.begin(), top.end() - 2},
        };

        for(const auto& previousRound : previousRounds) {
            if(latticeLe(previousRound.queriedPoint, v)) {
                lBounds.bot = join(std::move(lBounds.bot), previousRound.b.bot);
            }
            if(latticeLe(v, previousRound.queriedPoint)) {
                lBounds.top = meet(std::move(lBounds.top), previousRound.b.top);
            }
        }

        for(int i = 0; i < v.size() + 1; i++) {
            auto lFunction = [&v, &f, i, &lBounds](const auto& w) {
                assert(w.size() == lBounds.bot.size());
                vector<int_t> x{};
                x.insert(x.end(), w.begin(), w.end());
                x.insert(x.end(), v.begin(), v.end());
                vector<direction> fx = f(x);

                // sub 3 since the result has 1 more component.
                vector<direction> result {fx.begin(), fx.end() - 3};
                result.push_back(fx[i + lBounds.bot.size()]);
                return result;
            };

            lBounds = findBounds(lBounds.bot, lBounds.top, lFunction);
        }

        vector<int_t> leftRight{};
        leftRight.insert(leftRight.end(), lBounds.bot.begin(), lBounds.bot.end());
        leftRight.insert(leftRight.end(), v.begin(), v.end());
        auto flr = f(leftRight);

        vector<direction> result {flr.end() - 3, flr.end()};

        previousRounds.push_back({v, lBounds, result});
        lDirs = vector<direction> {flr.begin(), flr.end() - 3};
        return result;
    };

    vector<int_t> rBot {bot.end() - 2, bot.end()};
    vector<int_t> rTop {top.end() - 2, top.end()};
    auto rMonotonePoint = findMonotonePointByDecomposition(rBot, rTop, rFunction);

    if(isAllWeakUp(rMonotonePoint.second)) {
        vector<int_t> resultVec {lBounds.bot.begin(), lBounds.bot.end()};
        resultVec.insert(resultVec.end(), rMonotonePoint.first.begin(), rMonotonePoint.first.end());
        vector<direction> resultDirs = f(resultVec);
        return {resultVec, resultDirs};
    }

    assert(isAllWeakDown(rMonotonePoint.second));
    vector<int_t> resultVec{lBounds.top.begin(), lBounds.top.end()};
    resultVec.insert(resultVec.end(), rMonotonePoint.first.begin(), rMonotonePoint.first.end());

    vector<direction> resultDirs = f(resultVec);
    return {resultVec, resultDirs};
}
