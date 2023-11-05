#include "innerAlgorithm.h"
#include "latticeUtil.h"

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


bool InnerAlgorithm::sliceWeakUp(const vector<direction>& directions) {
    assert(!directions.empty());
    return rng::all_of(directions.begin(), directions.end() -1, [](auto direction) {return direction != down;});
}

bool InnerAlgorithm::sliceWeakDown(const vector<direction> &directions) {
    assert(!directions.empty());
    return rng::all_of(directions.begin(), directions.end() -1, [](auto direction) {return direction != up;});
}

vector<int> InnerAlgorithm::getMidInSlice(const vector<int>& x, const vector<int>& y) {
    assert(x.size() == y.size());
    assert(latticeLe(x, y));

    vector<int> result;
    result.reserve(x.size());

    for(int i = 0; i < x.size(); i++) {
      result.push_back(x[i] + ((y[i] - x[i]) / 2));
    }

    return result;
}

  vector<int> InnerAlgorithm::findMonotonePoint() {
    return helper();
  }

  vector<int> InnerAlgorithm::helper() {
    vector<int> mid = getMidInSlice(a, b);
    vector<direction> midDirections = f(mid);

    if(isAllWeakUp(midDirections)) {
      return mid;
    }

    if(isAllWeakDown(midDirections)) {
      return mid;
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

      return candidateWitness;
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
    return candidateWitness;
  }

vector<int> findMonotonePoint3(const vector<int>& bot,
                              const vector<int>& top,
                              const function<vector<int> (const vector<int>&)>& f,
                              int sliceDimension,
                              int sliceValue) {
    auto directionFunction = getDirectionFunction(f);
    auto slicedFunction = getSlicedFunction(directionFunction, sliceDimension, sliceValue);

    auto slicedBot = vector<int>(bot.begin(), bot.end());
    slicedBot.erase(slicedBot.begin() + sliceDimension);

    auto slicedTop = vector<int>(top.begin(), top.end());
    slicedTop.erase(slicedTop.begin() + sliceDimension);

    InnerAlgorithm innerAlgorithm {slicedBot, slicedTop, slicedFunction};
    auto monotonePoint = innerAlgorithm.findMonotonePoint();

    monotonePoint.insert(monotonePoint.begin() + sliceDimension, sliceValue);
    return monotonePoint;
}


