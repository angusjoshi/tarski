//
// Created by angus on 05/11/2023.
//

#include "monotoneFunction.h"
#include <iostream>

namespace vw = std::views;
namespace rng = std::ranges;

function<vector<direction> (const vector<int>&)> getDirectionFunction(
        const function<vector<int>(const vector<int>&)>& f) {
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
function<vector<direction> (const vector<int>&)> getSlicedFunction(
        const function<vector<direction> (const vector<int>&)>& f,
        int sliceDimension,
        int sliceVal) {
    return [&f, sliceDimension, sliceVal] (const auto& v) {
        auto input = vector<int> { v.begin(), v.end() };
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
