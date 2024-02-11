//
// Created by angus on 05/11/2023.
//

#include "latticeUtil.h"
#include "monotoneFunction.h"

#include <iostream>

bool isFixpoint(const vector<int_t>& point, const function<vector<direction> (const vector<int_t>&)>& f) {
    auto fPoint = f(point);

    assert(fPoint.size() == point.size());
    return all_of(fPoint.begin(), fPoint.end(), [](auto x) { return x == fix;});
}

bool isUp(const vector<int_t>& point, const function<vector<direction> (const vector<int_t>&)>& f) {
    auto fPoint = f(point);
    assert(fPoint.size() == point.size());

    return all_of(fPoint.begin(), fPoint.end(), [](auto x) { return x != down; });
}

bool isDown(const vector<int_t>& point, const function<vector<direction> (const vector<int_t>&)>& f) {
    auto fPoint = f(point);
    assert(fPoint.size() == point.size());

    return all_of(fPoint.begin(), fPoint.end(), [](auto x) { return x != up; });
}

int_t getSliceMiddle(const vector<int_t>& bot, const vector<int_t>& top, int i) {
    return bot[i] + ((top[i] - bot[i]) / 2);
}

int getLargeEnoughSliceIndex(const vector<int_t>& bot, const vector<int_t>& top) {
    assert(bot.size() == top.size());

    for(int i = bot.size() - 1; i >= 0; i--) {
        if(top[i] - bot[i] >= 2) {
            return i;
        }
    }
    return -1;
}

void printVec(const vector<long long>& v) {
    for(const auto i : v) {
        cout << i << '\t';
    }
    cout << endl;
}
//void printVec(const vector<int_t>& v) {
//    for(const auto& i : v) {
//        cout << i << '\t';
//    }
//    cout << endl;
//}

int getNextUpIndex(const vector<direction>& a) {
    for(int i = 0; i < a.size(); i++) {
        if(a[i] == up) return i;
    }

    return -1;
}

vector<int_t> searchSmallInstance(const vector<int_t>& bot,
                                const vector<int_t>& top,
                                const function<vector<direction> (const vector<int_t>&)>& f) {
    vector<int_t> current = bot;
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

bool latEq(const vector<int_t>& a, const vector<int_t>& b) {
    assert(a.size() == b.size());

    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

bool latticeLe(const vector<int_t>& x, const vector<int_t>& y) {
    assert(x.size() == y.size());

    for(int i = 0; i < x.size(); i++) {
        if(x[i] > y[i]) {
            return false;
        }
    }

    return true;
}

vector<int_t> join(vector<int_t> &&a, const vector<int_t> &b) {
    assert(a.size() == b.size());
    for (int i = 0; i < a.size(); i++) {
        a[i] = max(a[i], b[i]);
    }
    return std::move(a);
}

vector<int_t> meet(vector<int_t> &&a, const vector<int_t> &b) {
    assert(a.size() == b.size());

    for (int i = 0; i < a.size(); i++) {
        a[i] = min(a[i], b[i]);
    }
    return std::move(a);
}
