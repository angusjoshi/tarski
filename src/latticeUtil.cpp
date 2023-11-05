//
// Created by angus on 05/11/2023.
//

#include "latticeUtil.h"
#include "monotoneFunction.h"

#include <iostream>

bool isFixpoint(const vector<int>& point, const function<vector<int> (const vector<int>&)>& f) {
    auto fPoint = f(point);

    assert(fPoint.size() == point.size());

    for(int i = 0; i < point.size(); i++) {
        if(point[i] != fPoint[i]) {
            return false;
        }
    }

    return true;
}

bool isUp(const vector<int>& point, const function<vector<int> (const vector<int>&)>& f) {
    auto fPoint = f(point);

    assert(fPoint.size() == point.size());

    for(int i = 0; i < point.size(); i++) {
        if(point[i] > fPoint[i]) {
            return false;
        }
    }

    return true;
}

bool isDown(const vector<int>& point, const function<vector<int> (const vector<int>&)>& f) {
    auto fPoint = f(point);

    assert(fPoint.size() == point.size());

    for(int i = 0; i < point.size(); i++) {
        if(point[i] < fPoint[i]) {
            return false;
        }
    }

    return true;
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
int getNextNeIndex(int start, const vector<int>& a, const vector<int>& b) {
    assert(a.size() == b.size());

    for(int i = start; i < a.size(); i++) {
        if(a[i] != b[i]) return i;
    }

    return -1;
}

vector<int> searchSmallInstance(const vector<int>& bot,
                                const vector<int>& top,
                                const function<vector<int> (const vector<int>&)>& f) {
    assert(isUp(bot, f));
    assert(isDown(top, f));

    vector<int> current = bot;
    vector<int> fCurrent = f(bot);
    int currentDimension = getNextNeIndex(0, current, fCurrent);

    while(currentDimension != -1) {
        current[currentDimension]++;
        fCurrent = f(current);

        currentDimension = getNextNeIndex(currentDimension, current, fCurrent);
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
