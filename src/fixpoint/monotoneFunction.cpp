//
// Created by angus on 05/11/2023.
//

#include "monotoneFunction.h"
#include <iostream>
#include "../config.h"

namespace vw = std::views;
namespace rng = std::ranges;

function<vector<direction> (const vector<int_t>&)> getDirectionFunction(
        const function<vector<int_t>(const vector<int_t>&)>& f) {
    return [f](const auto& v) {
        auto results = f(v);

        assert(v.size() == results.size());

        vector<direction> directions {};

        directions.reserve(v.size());
        for(int i = 0; i < v.size(); i++) {
            directions.push_back( v[i] < results[i]
                   ? up
                   : v[i] > results[i]
                     ? down
                     : fix);
        }
        return directions;
    };
}

void printDirections(const vector<direction>& directions) {
    for(const auto& direction : directions) {
        cout << (direction == up
                 ? "up"
                 : direction == down
                   ? "down"
                   : "fix") << " ";
    }
    cout << endl;
}
function<vector<direction> (const vector<int_t>&)> getSlicedFunction(
        const function<vector<direction> (const vector<int_t>&)>& f,
        int sliceDimension,
        int_t sliceVal) {
    return [&f, sliceDimension, sliceVal] (const auto& v) {
        auto input = vector<int_t> { v.begin(), v.end() };
        input.insert(input.begin() + sliceDimension, sliceVal);

        auto result = f(input);

        direction sliceDirection = result[sliceDimension];
        result.erase(result.begin() + sliceDimension);
        result.push_back(sliceDirection);
        return result;
    };
}

bool isAllWeakUp(const vector<direction>& directions) {
    return rng::all_of(directions.begin(), directions.end(), [](auto direction) {return direction != down;});
}

bool isAllWeakDown(const vector<direction>& directions) {
    return rng::all_of(directions.begin(), directions.end(), [](auto direction) {return direction != up;});
}

bool isAllFixed(const vector<direction>& directions) {
    return rng::all_of(directions.begin(), directions.end(), [](auto direction) {return direction == fix;});
}

slicedLattice getSlicedLattice(const vector<int_t>& bot,
                               const vector<int_t>& top,
                               const function<vector<direction>(const vector<int_t> &)> &f,
                               int sliceDimension,
                               int_t sliceValue) {
    auto slicedFunction = getSlicedFunction(f, sliceDimension, sliceValue);

    auto slicedBot = vector<int_t>{bot.begin(), bot.end()};
    slicedBot.erase(slicedBot.begin() + sliceDimension);

    auto slicedTop = vector<int_t>{top.begin(), top.end()};
    slicedTop.erase(slicedTop.begin() + sliceDimension);

    return {slicedBot, slicedTop, slicedFunction};
}
