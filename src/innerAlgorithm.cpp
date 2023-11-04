#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

class InnerAlgorithm {
private:

  static void printVec(const vector<int>& v) {
    for(const auto i : v) {
      cout << i << '\t';
    }
    cout << endl;
  }

  vector<int> bot;
  vector<int> top;
  vector<int> a;
  vector<int> u;
  vector<int> d;
  vector<int> b;

  int sliceDimension;
  int sliceDimensionVal;
  function<vector<int> (const vector<int>&)> f;


public:
  InnerAlgorithm(vector<int>&& bot, vector<int>&& top, function<vector<int> (const vector<int>&)>&& f) noexcept : 
    bot(bot),
    top(top),
    a(bot),
    u(bot),
    d(top),
    b(top),
    f(f) {
    assert(bot.size() == 3);
    assert(top.size() == 3);
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

  bool sliceLe(vector<int>& x, vector<int>& y) const {
    assert(x.size() == y.size());

    for(int i = 0; i < x.size(); i++) {
      if(i == sliceDimension) continue;

      if(x[i] > y[i]) {
        return false;
      }
    }

    return true;
  }

  vector<int> getMidInSlice(const vector<int>& x, const vector<int>& y) {
    assert(x.size() == y.size());
    assert(latticeLe(x, y));

    vector<int> result;
    for(int i = 0; i < x.size(); i++) {
      if(i == sliceDimension) {
        result.push_back(sliceDimensionVal);
        continue;
      }

      result.push_back(x[i] + ((y[i] - x[i]) / 2));
    }

    return result;
  }

  vector<int> findMonotonePoint(
    vector<int> _bot,
    vector<int> _top,
    int _sliceDimension,
    int _sliceDimensionVal) {
    assert(_sliceDimension <= 2 && _sliceDimension >= 0);
    assert(_sliceDimensionVal <= _top[_sliceDimension] && _sliceDimension >= _bot[_sliceDimension]);

    a = _bot;
    b = _top;
    u = a;
    d = b;

    this->sliceDimension = _sliceDimension;
    this->sliceDimensionVal = _sliceDimensionVal;

    return helper();
  }

  vector<int> helper() {
    vector<int> mid = getMidInSlice(a, b);
    vector<int> fMid = f(mid);

    if(latticeLe(mid, fMid)) {
      return mid;
    }

    if(latticeLe(fMid, mid)) {
      return mid;
    }

    if(sliceLe(mid, fMid)) {
      a = mid;
      u = mid;
      return helper();
    }

    if(sliceLe(fMid, mid)) {
      d = mid;
      b = mid;
      return helper();
    }

    auto freeDimensions = getFreeCoords();

    int lteDimension;
    int gteDimension;

    for(const auto dimension : freeDimensions) {
      if(mid[dimension] <= fMid[dimension]) {
        gteDimension = dimension;
      } else {
        lteDimension = dimension;
      }
    }

    auto candidateWitness = vector<int>(3, -1); 

    if(mid[sliceDimension] <= fMid[sliceDimension]) {
      candidateWitness[sliceDimension] = sliceDimensionVal;
      candidateWitness[lteDimension] = mid[lteDimension];
      candidateWitness[gteDimension] = b[gteDimension];

      auto fCandidateWitness = f(candidateWitness);
      assert(candidateWitness[sliceDimension] <= fCandidateWitness[sliceDimension]);

      if(candidateWitness[gteDimension] >= fCandidateWitness[gteDimension]) {
        b = candidateWitness;
        d = mid;
        return helper();
      }

      // this is the lemma 12 case.
      cout << "hereerehrehrehreh" << endl;
      return candidateWitness;
    }

    candidateWitness[sliceDimension] = sliceDimensionVal;
    candidateWitness[lteDimension] = a[lteDimension];
    candidateWitness[gteDimension] = mid[gteDimension];

    auto fCandidateWitness = f(candidateWitness);
    assert(candidateWitness[sliceDimension] >= fCandidateWitness[sliceDimension]);

    if(candidateWitness[gteDimension] <= fCandidateWitness[gteDimension]) {
      a = candidateWitness;
      u = mid;
      return helper();
    }

    // this is the lemma 12 case.
    return candidateWitness;
  }

  [[nodiscard]] vector<int> getFreeCoords() const {
    vector<int> result;
    for(int i = 0; i < 3; i++) {
      if(i != sliceDimension) {
        result.push_back(i);
      }
    }
    return result;
  }

};

int getSliceMiddle(vector<int>& bot, vector<int>& top, int i) {
    return bot[i] + ((top[i] - bot[i]) / 2);
}
int getLargeEnoughSliceIndex(vector<int>& bot, vector<int>& top) {
    assert(bot.size() == 3);
    assert(bot.size() == top.size());

    for(int i = 2; i >= 0; i--) {
        if(top[i] - bot[i] >= 2) {
            return i;
        }
    }
    return -1;
}
void printVec(vector<int>& v) {
  for(const auto i : v) {
    cout << i << '\t';
  }
  cout << endl;
}


bool isFixpoint(vector<int> point, const function<vector<int> (const vector<int>&)>& f) {
  auto fPoint = f(point);

  assert(fPoint.size() == point.size());

  for(int i = 0; i < point.size(); i++) {
    if(point[i] != fPoint[i]) {
      return false;
    }
  }

  return true;
}

bool isUp(vector<int> point, function<vector<int> (const vector<int>&)> f) {
  auto fPoint = f(point);

  assert(fPoint.size() == point.size());

  for(int i = 0; i < point.size(); i++) {
    if(point[i] > fPoint[i]) {
      return false;
    }
  }

  return true;
}

bool isDown(vector<int> point, function<vector<int> (const vector<int>&)> f) {
  auto fPoint = f(point);

  assert(fPoint.size() == point.size());

  for(int i = 0; i < point.size(); i++) {
    if(point[i] < fPoint[i]) {
      return false;
    }
  }

  return true;
}

