#include "innerAlgorithm.h"
#include "latticeUtil.h"
#include <iostream>

using namespace std;
namespace rng = std::ranges;

InnerAlgorithm::InnerAlgorithm(const vector<int>& bot, const vector<int>& top, const function<vector<direction> (const vector<int>&)>& f) :
    bot(bot),
    top(top),
    a(bot),
    u(bot),
    d(top),
    b(top),
    f(f) {
        assert(bot.size() == 2);
        assert(top.size() == 2);
    }

    InnerAlgorithm::~InnerAlgorithm() {}




bool InnerAlgorithm::sliceWeakUp(const vector<direction>& directions) {
    assert(!directions.empty());
    return rng::all_of(directions.begin(), directions.end() -1, [](auto direction) {return direction != down;});
}

bool InnerAlgorithm::sliceWeakDown(const vector<direction> &directions) {
    assert(!directions.empty());
    return rng::all_of(directions.begin(), directions.end() -1, [](auto direction) {return direction != up;});
}

vector<int> InnerAlgorithm::getMidInSlice(const vector<int>& x, const vector<int>& y) const {
    assert(x.size() == y.size());
    assert(latticeLe(x, y));

    vector<int> result;
    result.reserve(x.size());

    if(useCeilDivision) {
        for(int i = 0; i < x.size(); i++) {
            result.push_back(x[i] + ((y[i] - x[i]) / 2));

            if(i == ceilDivisionDimension) {
                result.back() += ((y[i] - x[i]) % 2 == 0) ? 0 : 1;
            }
        }
    } else {
        for(int i = 0; i < x.size(); i++) {
            result.push_back(x[i] + ((y[i] - x[i]) / 2));
        }
    }


    return result;
}

bool InnerAlgorithm::isNarrowInstance() {
    return abs(b[0] - a[0]) <= 1 || abs(b[1] - a[1]) <= 1;
}

int InnerAlgorithm::getNarrowDimension() {
    if(abs(b[0] - a[0]) <= 1) {
        return 0;
    } else if(abs(b[1] - a[1]) <= 1) {
        return 1;
    }
    return -1;
}


pair<vector<int>, vector<direction>> InnerAlgorithm::solveZeroWidthInstance() {
    return { {}, {} };
}

void InnerAlgorithm::fixNarrowInstance() {
    int narrowDimension = getNarrowDimension();
    assert(narrowDimension != -1);

    ceilDivisionDimension = narrowDimension;
    useCeilDivision = !useCeilDivision;

    if(!sliceEq(a, u) && a[narrowDimension] != u[narrowDimension]) {
        // witness on the narrow edge.
        vector<direction> aDirections = f(a);
        if(sliceWeakUp(aDirections)) {
            u = a;
        } else {
            assert(d[narrowDimension] == u[narrowDimension]);
            a = u;
        }
    }

    if(!sliceEq(b, d) && b[narrowDimension] != d[narrowDimension]) {
        // witness on the narrow edge.
        vector<direction> bDirections = f(b);
        if(sliceWeakUp(bDirections)) {
            d = b;
        } else {
            assert(u[narrowDimension] == d[narrowDimension]);
            b = d;
        }
    }
}

  pair<vector<int>, vector<direction>> InnerAlgorithm::findMonotonePoint() {
    return helper();
  }

bool InnerAlgorithm::sliceEq(const vector<int>& x, const vector<int>& y) {
    assert(x.size() == 2);
    assert(x.size() == y.size());

    return x[0] == y[0] && x[1] == y[1];
}
int InnerAlgorithm::getNeDimension(const vector<int> &x, const vector<int> &y) {
    int neDimension = x[0] != y[0] ? 0 : 1;
    return neDimension;
}

void InnerAlgorithm::fixWitnesses() {
    if(!sliceEq(a, u)) {
        // down set witness
        int neDimension = getNeDimension(a, u);

        int eqDimension = neDimension == 0 ? 1 : 0;
        assert(a[eqDimension] == u[eqDimension]);

        int topRightBoundary = b[neDimension];
        int botLeftBoundary = a[neDimension];

        int neDimensionMiddle = botLeftBoundary + ((topRightBoundary  - botLeftBoundary) / 2);

        if(u[neDimension] > neDimensionMiddle) {
            vector<int> edgeMid(2, -1);
            edgeMid[eqDimension] = a[eqDimension];
            edgeMid[neDimension] = neDimensionMiddle;
            vector<direction> fEdgeMid = f(edgeMid);

            if(fEdgeMid[neDimension] != down) {
                // e.g. case 3.b.
                a = edgeMid;
            } else {
                // e.g. case 3.c.
                u = edgeMid;
            }
        }
    }

    if(!sliceEq(b, d)) {
        // up set witness
        int neDimension = getNeDimension(b, d);

        int eqDimension = neDimension == 0 ? 1 : 0;
        assert(b[eqDimension] == d[eqDimension]);

        int topRightBoundary = b[neDimension];
        int botLeftBoundary = a[neDimension];

        int neDimensionMiddle = botLeftBoundary + ((topRightBoundary  - botLeftBoundary) / 2);

        if(d[neDimension] < neDimensionMiddle) {
            vector<int> edgeMid(2, -1);
            edgeMid[eqDimension] = b[eqDimension];
            edgeMid[neDimension] = neDimensionMiddle;
            vector<direction> fEdgeMid = f(edgeMid);

            if(fEdgeMid[neDimension] != up) {
                // e.g. case 2.b.
                b = edgeMid;
            } else {
                // e.g. case 2.c.
                d = edgeMid;
            }
        }
    }
}

  pair<vector<int>, vector<direction>> InnerAlgorithm::helper() {
    if(isNarrowInstance()) {
        fixNarrowInstance();
    }

//    if(b[narrowDimension] - a[narrowDimension] == 0) {
//      return solveZeroWidthInstance();
//    }

    fixWitnesses();

    vector<int> mid = getMidInSlice(a, b);
    vector<direction> midDirections = f(mid);

    if(isAllWeakUp(midDirections)) {
      return { mid, midDirections };
    }

    if(isAllWeakDown(midDirections)) {
      return { mid, midDirections };
    }

    if(sliceWeakUp(midDirections)) {
      a = mid;
      u = mid;
      return helper();
    }

    if(sliceWeakDown(midDirections)) {
      d = mid;
      b = mid;
      return helper();
    }

    int lteDimension = midDirections[0] == down ? 0 : 1;
    int gteDimension = midDirections[0] == up ? 0 : 1;

    assert(lteDimension != gteDimension);

    auto candidateWitness = vector<int>(2, -1);

    if(midDirections[2] != down) {
      candidateWitness[lteDimension] = mid[lteDimension];
      candidateWitness[gteDimension] = b[gteDimension];

      auto candidateWitnessDirections = f(candidateWitness);

      assert(candidateWitnessDirections[2] != down);

      if(candidateWitnessDirections[gteDimension] != up) {
        b = candidateWitness;
        d = mid;
        return helper();
      }

      return { candidateWitness, candidateWitnessDirections };
    }

    candidateWitness[lteDimension] = a[lteDimension];
    candidateWitness[gteDimension] = mid[gteDimension];

    auto candidateWitnessDirections = f(candidateWitness);

    assert(candidateWitnessDirections[2] != up);

    if(candidateWitnessDirections[gteDimension] != down) {
      a = candidateWitness;
      u = mid;
      return helper();
    }

    // this is the lemma 12 case.
    return { candidateWitness, candidateWitnessDirections };
  }

pair<vector<int>, vector<direction>> findMonotonePoint3(const vector<int>& bot,
                              const vector<int>& top,
                              const function<vector<direction> (const vector<int>&)>& directionFunction,
                              int sliceDimension,
                              int sliceValue) {
    auto slicedFunction = getSlicedFunction(directionFunction, sliceDimension, sliceValue);

    auto slicedBot = vector<int>(bot.begin(), bot.end());
    slicedBot.erase(slicedBot.begin() + sliceDimension);

    auto slicedTop = vector<int>(top.begin(), top.end());
    slicedTop.erase(slicedTop.begin() + sliceDimension);

    InnerAlgorithm innerAlgorithm {slicedBot, slicedTop, slicedFunction};
    pair<vector<int>, vector<direction>> monotonePoint = innerAlgorithm.findMonotonePoint();

    assert(isAllWeakUp(monotonePoint.second) || isAllWeakDown(monotonePoint.second));
    monotonePoint.first.insert(monotonePoint.first.begin() + sliceDimension, sliceValue);
    return monotonePoint;
}


