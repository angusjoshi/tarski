#include "innerAlgorithm.h"
#include "latticeUtil.h"
#include "recursiveBinarySearch.h"
#include <iostream>

using namespace std;
namespace rng = std::ranges;

bool latticeEq(vector<int_t> a, vector<int_t> b) {
    assert(a.size() == b.size());
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }

    return true;
}

bool isMonotone(const vector<direction> &directions) {
    return isAllWeakUp(directions) || isAllWeakDown(directions);
}

bool InnerAlgorithm::instanceIsWellFormed() {
    bool botLeTop = latticeLe(a, b);
    bool botWitnessInRange = latticeLe(a, u) && latticeLe(u, b);
    bool topWitnessInRange = latticeLe(d, b) && latticeLe(a, d);

    return botLeTop && botWitnessInRange && topWitnessInRange;
}

InnerAlgorithm::InnerAlgorithm(const vector<int_t> &bot, const vector<int_t> &top,
                               const function<vector<direction>(const vector<int_t> &)> &f) :
        bot(bot),
        top(top),
        a(bot),
        u(bot),
        d(top),
        b(top),
        f(f) {
    assert(bot.size() == 2);
    assert(top.size() == 2);
    useCeilDivision = false;
    ceilDivisionDimension = -1;
}

InnerAlgorithm::~InnerAlgorithm() = default;

bool InnerAlgorithm::sliceWeakUp(const vector<direction> &directions) {
    assert(!directions.empty());
    return rng::all_of(directions.begin(), directions.end() - 1, [](auto direction) { return direction != down; });
}

bool InnerAlgorithm::sliceWeakDown(const vector<direction> &directions) {
    assert(!directions.empty());
    return rng::all_of(directions.begin(), directions.end() - 1, [](auto direction) { return direction != up; });
}

vector<int_t> InnerAlgorithm::getMidInSlice(const vector<int_t> &x, const vector<int_t> &y) const {
    assert(x.size() == y.size());
    assert(latticeLe(x, y));

    vector<int_t> result{};
    result.reserve(x.size());

    if (useCeilDivision) {
        for (int i = 0; i < x.size(); i++) {
            result.push_back(x[i] + ((y[i] - x[i]) / 2));

            if (i == ceilDivisionDimension) {
                result.back() += ((y[i] - x[i]) % 2 == 0) ? 0 : 1;
            }
        }
    } else {
        for (int i = 0; i < x.size(); i++) {
            result.push_back(x[i] + ((y[i] - x[i]) / 2));
        }
    }


    return result;
}

bool InnerAlgorithm::isNarrowInstance() {
    return abs(b[0] - a[0]) <= 1 || abs(b[1] - a[1]) <= 1;
}

bool InnerAlgorithm::isWidthZeroInstance() {
    return abs(b[0] - a[0]) == 0 || abs(b[1] - a[1]) == 0;
}

bool InnerAlgorithm::isDoublyNarrowInstance() {
    return abs(b[0] - a[0]) <= 1 && abs(b[1] - a[1]) <= 1;
}

int InnerAlgorithm::getNarrowDimension() {
    if (abs(b[0] - a[0]) <= 1) {
        return 0;
    } else if (abs(b[1] - a[1]) <= 1) {
        return 1;
    }
    return -1;
}


optional<pair<vector<int_t>, vector<direction>>> InnerAlgorithm::trySolveWidthZeroInstance() {
    if (latticeEq(a, u)) {
        auto fa = f(a);
        if (isAllWeakUp(fa) || isAllWeakDown(fa)) return {{a, fa}};
    }

    if (latticeEq(b, d)) {
        auto fb = f(b);
        if (isAllWeakUp(fb) || isAllWeakDown(fb)) return {{b, fb}};
    }

    return {};
}

pair<vector<int_t>, vector<direction>> InnerAlgorithm::solveZeroWidthInstance(int narrowDimension,
                                                                            const vector<int_t> &bot,
                                                                            const vector<int_t> &top) {
    assert(bot.size() == top.size());
    assert(bot.size() == 2);
    assert(bot[narrowDimension] == top[narrowDimension]);

    int otherDimension = narrowDimension == 0 ? 1 : 0;

    auto narrowF = [this, narrowDimension, &bot, otherDimension](const int_t& x) {
        vector<int_t> input(2, -1);
        input[narrowDimension] = bot[narrowDimension];
        input[otherDimension] = x;
        return f(input)[otherDimension];
    };

    auto sliceFixpoint = binarySearch(bot[otherDimension], top[otherDimension], narrowF);

    vector<int_t> result(2, -1);
    result[otherDimension] = sliceFixpoint;
    result[narrowDimension] = bot[narrowDimension];

    auto resultDirections = f(result);

    assert(resultDirections[otherDimension] == fix);

    return {result, f(result)};
}

void InnerAlgorithm::fixNarrowInstance() {
    int narrowDimension = getNarrowDimension();
    assert(narrowDimension != -1);

    ceilDivisionDimension = narrowDimension;
    useCeilDivision = !useCeilDivision;

    if (!sliceEq(a, u) && a[narrowDimension] != u[narrowDimension]) {
        // witness on the narrow edge.
        vector<direction> aDirections = f(a);
        if (sliceWeakUp(aDirections)) {
            u = a;
        } else {
            assert(d[narrowDimension] == u[narrowDimension]);
            a = u;
        }
    }

    if (!sliceEq(b, d) && b[narrowDimension] != d[narrowDimension]) {
        // witness on the narrow edge.
        vector<direction> bDirections = f(b);
        if (sliceWeakDown(bDirections)) {
            d = b;
        } else {
            assert(u[narrowDimension] == d[narrowDimension]);
            b = d;
        }
    }
    assert(instanceIsWellFormed());
}

pair<vector<int_t>, vector<direction>> InnerAlgorithm::findMonotonePoint() {
    return helper();
}

bool InnerAlgorithm::sliceEq(const vector<int_t> &x, const vector<int_t> &y) {
    assert(x.size() == 2);
    assert(x.size() == y.size());

    return x[0] == y[0] && x[1] == y[1];
}

int InnerAlgorithm::getNeDimension(const vector<int_t> &x, const vector<int_t> &y) {
    int neDimension = x[0] != y[0] ? 0 : 1;
    return neDimension;
}

bool InnerAlgorithm::fixWitnesses() {
    if (!sliceEq(a, u)) {
        // down set witness
        int neDimension = getNeDimension(a, u);

        int eqDimension = neDimension == 0 ? 1 : 0;
        assert(a[eqDimension] == u[eqDimension]);

        int_t topRightBoundary = b[neDimension];
        int_t botLeftBoundary = a[neDimension];

        int_t neDimensionMiddle = botLeftBoundary + ((topRightBoundary - botLeftBoundary) / 2);

        if (u[neDimension] > neDimensionMiddle) {
            vector<int_t> edgeMid{-1, -1};
            edgeMid[eqDimension] = a[eqDimension];
            edgeMid[neDimension] = neDimensionMiddle;
            vector<direction> fEdgeMid = f(edgeMid);

            if (fEdgeMid[neDimension] != down) {
                // e.g. case 3.b.
                a = edgeMid;
            } else {
                // e.g. case 3.c.
                u = edgeMid;
            }
            return true;
        }
    }

    if (!sliceEq(b, d)) {
        // up set witness
        int neDimension = getNeDimension(b, d);

        int eqDimension = neDimension == 0 ? 1 : 0;
        assert(b[eqDimension] == d[eqDimension]);

        int_t topRightBoundary = b[neDimension];
        int_t botLeftBoundary = a[neDimension];

        int_t neDimensionMiddle = botLeftBoundary + ((topRightBoundary - botLeftBoundary) / 2);

        if (d[neDimension] < neDimensionMiddle) {
            vector<int_t> edgeMid(2, -1);
            edgeMid[eqDimension] = b[eqDimension];
            edgeMid[neDimension] = neDimensionMiddle;
            vector<direction> fEdgeMid = f(edgeMid);

            if (fEdgeMid[neDimension] != up) {
                // e.g. case 2.b.
                b = edgeMid;
            } else {
                // e.g. case 2.c.
                d = edgeMid;
            }
            return true;
        }
    }
    return false;
}


pair<vector<int_t>, vector<direction>> InnerAlgorithm::exhaustiveSearchInstance() {
    assert(isDoublyNarrowInstance());

    for (int_t i = a[0]; i <= b[0]; i++) {
        for (int_t j = a[1]; j <= b[1]; j++) {
            vector<int_t> point{i, j};
            vector<direction> fPoint = f(point);
            if (isAllWeakUp(fPoint) || isAllWeakDown(fPoint)) {
                return {point, fPoint};
            }
        }
    }

    assert(false);
}

pair<vector<int_t>, vector<direction>> InnerAlgorithm::helper() {
    assert(instanceIsWellFormed());

    if (isDoublyNarrowInstance()) {
        return exhaustiveSearchInstance();
    }

    if (isNarrowInstance()) {
        fixNarrowInstance();
    }

    if (isWidthZeroInstance()) {
        auto result = trySolveWidthZeroInstance();
        if (result.has_value()) return result.value();
    }

    if (fixWitnesses()) {
        //recurse if fixWitnesses changes something.
        return helper();
    }

    vector<int_t> mid = getMidInSlice(a, b);
    vector<direction> midDirections = f(mid);

    if (isAllWeakUp(midDirections)) {
        return {mid, midDirections};
    }

    if (isAllWeakDown(midDirections)) {
        return {mid, midDirections};
    }

    if (sliceWeakUp(midDirections)) {
        a = mid;
        u = mid;
        assert(sliceWeakUp(f(a)));
        assert(instanceIsWellFormed());
        return helper();
    }

    if (sliceWeakDown(midDirections)) {
        d = mid;
        b = mid;
        assert(sliceWeakDown(f(d)));
        assert(instanceIsWellFormed());
        return helper();
    }

    int lteDimension = midDirections[0] == down ? 0 : 1;
    int gteDimension = midDirections[0] == up ? 0 : 1;

    assert(lteDimension != gteDimension);

    auto candidateWitness = vector<int_t>(2, -1);

    if (midDirections[2] != down) {
        candidateWitness[lteDimension] = mid[lteDimension];
        candidateWitness[gteDimension] = b[gteDimension];

        auto candidateWitnessDirections = f(candidateWitness);

        assert(candidateWitnessDirections[2] != down);

        if (candidateWitnessDirections[gteDimension] != up) {
            b = candidateWitness;
            d = mid;

            if (isWidthZeroInstance()) {
                //binary search in the slice between mid and candidateWitness
                auto [fixedInLte, directions] = solveZeroWidthInstance(lteDimension, a, mid);
                if (isMonotone(directions)) return {fixedInLte, directions};

                b = fixedInLte;
                d = fixedInLte;
            }

            return helper();
        }

        // lemma 12
        assert(latticeEq(d, candidateWitness));
        return {candidateWitness, candidateWitnessDirections};
    }

    candidateWitness[lteDimension] = a[lteDimension];
    candidateWitness[gteDimension] = mid[gteDimension];

    auto candidateWitnessDirections = f(candidateWitness);

    assert(candidateWitnessDirections[2] != up);

    if (candidateWitnessDirections[lteDimension] != down) {
        a = candidateWitness;
        u = mid;

        if (isWidthZeroInstance()) {
            //binary search in the slice between mid and candidateWitness
            auto fixedInLte = solveZeroWidthInstance(gteDimension, mid, b);
            if (isMonotone(fixedInLte.second)) return fixedInLte;

            a = fixedInLte.first;
            u = fixedInLte.first;
        }

        return helper();
    }

    // lemma 12
    assert(midDirections[2] == down || latticeEq(u, candidateWitness));
    return {candidateWitness, candidateWitnessDirections};
}

pair<vector<int_t>, vector<direction>> findMonotonePoint3(const vector<int_t> &bot,
                                                        const vector<int_t> &top,
                                                        const function<vector<direction>(
                                                                const vector<int_t> &)> &directionFunction,
                                                        int sliceDimension,
                                                        int_t sliceValue) {

    auto l = getSlicedLattice(bot, top, directionFunction, sliceDimension, sliceValue);
    auto slicedFunction = l.slicedFunction;
    auto slicedBot = l.slicedBot;
    auto slicedTop = l.slicedTop;

    InnerAlgorithm innerAlgorithm{slicedBot, slicedTop, slicedFunction};
    pair<vector<int_t>, vector<direction>> monotonePoint = innerAlgorithm.findMonotonePoint();

    assert(isAllWeakUp(monotonePoint.second) || isAllWeakDown(monotonePoint.second));
    monotonePoint.first.insert(monotonePoint.first.begin() + sliceDimension, sliceValue);
    return monotonePoint;
}


