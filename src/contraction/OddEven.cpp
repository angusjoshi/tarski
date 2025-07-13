//
// Created by angus on 05/07/2024.
//

#include "OddEven.h"
#include <utility>

void OddEven::reset(int newK, int_t newN) {
    k = newK;
    n = newN;

    vector<int_t> current(k, 0);

    for(int i = 0; i <= n; i++) {
        current[0] = i;

        if(i % 2 == 0) {
            resetHelper(1, true, current);
            continue;
        }

        resetHelper(1, false, current);
    }

}

void OddEven::resetHelper(int i, bool even, vector<int_t>& current) {
    if(i == k) {
        points.push_back(current);
        return;
    }

    for(int j = 0; j <= n; j++) {
        if(!even && j % 2 == 0) continue;
        if(even && j % 2 == 1) continue;

        current[i] = j;
        resetHelper(i + 1, even, current);
    }
}

int infDist(const vector<int_t>& a, const vector<int_t>& b) {
    assert(a.size() > 0);
    assert(a.size() == b.size());

    int_t dist = abs(a[0] - b[0]);

    for(int i = 1; i < a.size(); i++) {
        dist = max(abs(a[i] - b[i]), dist);
    }

    return dist;
}

void OddEven::removePyramids(const vector<int_t>& queried, const vector<int_t>& result) {
    assert(queried.size() == k);
    assert(queried.size() == result.size());

    vector<pair<bool, bool>> pyramidsToRemove(k, {false, false});

    for(int i = 0; i < k; i++) {
        if(result[i] <= queried[i]) {
            pyramidsToRemove[i].first = true;
        }

        if(result[i] >= queried[i]) {
            pyramidsToRemove[i].second = true;
        }
    }


    for(auto it = points.begin(); it != points.end();) {
        int_t dist = infDist(*it, queried);

        bool erase = false;
        for(int i = 0; i < k; i++) {
            if((*it)[i] - queried[i] == dist && pyramidsToRemove[i].first) {
                erase = true;
                break;
            }
            if (queried[i] - (*it)[i] == dist && pyramidsToRemove[i].second) {
                erase = true;
                break;
            }
        }

        if(erase) {
            it = points.erase(it);
        } else {
            it++;
        }
    }
}

vector<int_t> OddEven::someBalancedPoint() {
    for(const auto& point : points) {
        if(isBalanced(point)) return point;
    }

    assert(false);
}

bool OddEven::isBalanced(const vector<int_t>& point) {
    vector<pair<int_t, int_t>> nInPyramids(k, pair<int_t, int_t>{});

    for(const auto& other : points) {
        int_t dist = infDist(point, other);

        for(int i = 0; i < k; i++) {
            if(point[i] - other[i] == dist) {
                nInPyramids[i].first++;
            }

            if(other[i] - point[i] == dist) {
                nInPyramids[i].second++;
            }
        }
    }


    for(const auto& nInPyramid : nInPyramids) {
        // todo fix this rounding
        // threshold is floored but it should be ceiled
        int_t balancedThreshold = points.size() / (2*k)+ (points.size() % (2*k) != 0);
        if(nInPyramid.first >= balancedThreshold && nInPyramid.second >= balancedThreshold) {
            return true;
        }
    }

    return false;
}

void OddEven::printAll() {
    for(const auto& point : points) {
        for(int v : point) {
            printf("%d ", v);
        }

        printf("\n");
    }
}
