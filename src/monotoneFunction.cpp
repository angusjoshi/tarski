//
// Created by angus on 05/11/2023.
//

#include "monotoneFunction.h"

namespace vw = std::views;
namespace rng = std::ranges;

function<vector<direction> (const vector<int>&)> getDirectionFunction(
        const function<vector<int> (const vector<int>&)>& f) {
    return [&f](auto v) {
        auto result = f(v);

        auto view = vw::zip(v, result)
            | vw::transform([](auto x) {
                return x.first < x.second
                    ? up
                    : x.first > x.second
                    ? down
                    : fix;
            });

        return vector<direction> (view.begin(), view.end());
    };
}

function<vector<direction> (const vector<int>&)> getSlicedFunction(
        const function<vector<direction> (const vector<int>&)>& f,
        int sliceDimension,
        int sliceVal) {
    return [&f, sliceDimension, sliceVal](auto v) {
        auto input = vector<int> (v.begin(), v.end());
        input.insert(input.begin() + sliceDimension, sliceVal);

        auto result = f(input);

        direction sliceDirection = result[sliceDimension];
        result.erase(result.begin() + sliceDimension);
        result.push_back(sliceDirection);
        return result;
    };
}

bool isAllWeakUp(const vector<direction>& directions) {
    return rng::all_of(directions.begin(), directions.end(), [](auto direction) {return direction != up;});
}

bool isAllWeakDown(const vector<direction>& directions) {
    return rng::all_of(directions.begin(), directions.end(), [](auto direction) {return direction != down;});
}
