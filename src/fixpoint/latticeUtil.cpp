//
// Created by angus on 05/11/2023.
//

#include "latticeUtil.h"
#include "monotoneFunction.h"

#include <iostream>

bool isFixpoint(const vector<int>& point, const function<vector<direction> (const vector<int>&)>& f) {
    auto fPoint = f(point);

    assert(fPoint.size() == point.size());
    return all_of(fPoint.begin(), fPoint.end(), [](auto x) { return x == fix;});
}

bool isUp(const vector<int>& point, const function<vector<direction> (const vector<int>&)>& f) {
    auto fPoint = f(point);
    assert(fPoint.size() == point.size());

    return all_of(fPoint.begin(), fPoint.end(), [](auto x) { return x != down; });
}

bool isDown(const vector<int>& point, const function<vector<direction> (const vector<int>&)>& f) {
    auto fPoint = f(point);
    assert(fPoint.size() == point.size());

    return all_of(fPoint.begin(), fPoint.end(), [](auto x) { return x != up; });
}

int getSliceMiddle(const vector<int>& bot, const vector<int>& top, int i) {
    return bot[i] + ((top[i] - bot[i]) / 2);
}

int getLargeEnoughSliceIndex(const vector<int>& bot, const vector<int>& top) {
    assert(bot.size() == top.size());

    for(int i = 2; i >= 0; i--) {
        if(top[i] - bot[i] >= 2) {
            return i;
        }
    }
    return -1;
}

void printVec(const vector<int>& v) {
    for(const auto i : v) {
        cout << i << '\t';
    }
    cout << endl;
}

int getNextUpIndex(const vector<direction>& a) {
    for(int i = 0; i < a.size(); i++) {
        if(a[i] == up) return i;
    }

    return -1;
}

vector<int> searchSmallInstance(const vector<int>& bot,
                                const vector<int>& top,
                                const function<vector<direction> (const vector<int>&)>& f) {
    vector<int> current = bot;
    vector<direction> fCurrent = f(bot);

    assert(isAllWeakUp(fCurrent));

    int currentDimension = getNextUpIndex(fCurrent);

    while(currentDimension != -1) {
        current[currentDimension]++;
        fCurrent = f(current);

        currentDimension = getNextUpIndex(fCurrent);
    }

    return current;
}

bool latEq(const vector<int>& a, const vector<int>& b) {
    assert(a.size() == b.size());

    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

bool latticeLe(const vector<int>& x, const vector<int>& y) {
    assert(x.size() == y.size());

    for(int i = 0; i < x.size(); i++) {
        if(x[i] > y[i]) {
            return false;
        }
    }

    return true;
}
