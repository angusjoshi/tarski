//
// Created by angus on 05/07/2024.
//

#include "simpleContractionSolver.h"
#include "../contraction/OddEven.h"
#include "../fixpoint/latticeUtil.h"

int_t dist(const vector<int_t>& a, const vector<int_t>& b) {
    assert(a.size() > 0);
    assert(a.size() == b.size());

    int_t dist = abs(a[0] - b[0]);
    for(int i = 0; i < a.size(); i++) {
        dist = max(abs(a[i] - b[i]), dist);
    }
    return dist;
}

vector<int_t> simpleContractionSolve(simpleStochasticGame& g) {
    auto f = g.getMonotoneFunction();

    OddEven o;
    o.reset(g.k, g.N);

    while(o.points.size() > 1) {
        auto balancedPoint = o.someBalancedPoint();
        printf("balanced point is: ");
        printVec(balancedPoint);

        auto result = f(balancedPoint);

        if(dist(result, balancedPoint) <= 1) return result;

        o.removePyramids(balancedPoint, result);
    }

    assert(o.points.size() == 1);
    return o.points[0];
}
