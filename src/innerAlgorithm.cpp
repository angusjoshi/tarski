#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

class InnerAlgorithm {
private:

  void printVec(const vector<int>& v) {
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
    cout << "x is: ";
    printVec(x);
    cout << "y is: ";
    printVec(y);
    assert(x.size() == y.size());

    for(int i = 0; i < x.size(); i++) {
      if(x[i] > y[i]) {
        return false;
      }
    }

    return true;
  }

  bool sliceLe(vector<int>& a, vector<int>& b) {
    assert(a.size() == b.size());

    for(int i = 0; i < a.size(); i++) {
      if(i == sliceDimension) continue;

      if(a[i] > b[i]) {
        return false;
      }
    }

    return true;
  }

  vector<int> getMidInSlice(const vector<int>& bot, const vector<int>& top) {
    assert(latticeLe(bot, top));
    assert(bot.size() == top.size());

    vector<int> result;
    for(int i = 0; i < bot.size(); i++) {
      if(i == sliceDimension) {
        result.push_back(sliceDimensionVal);
        continue;
      }

      result.push_back((top[i] - bot[i]) / 2);
    }

    return result;
  }

  vector<int> findMonotonePoint(
    vector<int> bot,
    vector<int> top,
    int sliceDimension,
    int sliceDimensionVal) {
    assert(sliceDimension <= 2 && sliceDimension >= 0);
    assert(sliceDimensionVal <= top[sliceDimension] && sliceDimension >= bot[sliceDimension]);

    a = bot;
    b = top;
    u = a;
    d = b;

    this->sliceDimension = sliceDimension;
    this->sliceDimensionVal = sliceDimensionVal;

    return helper();
  }

  vector<int> helper() {
    cout << "helper! a is: ";
    printVec(a);
    cout << "b is: ";
    printVec(b);

    vector<int> mid = getMidInSlice(a, b);
    vector<int> fMid = f(mid);

    cout << "fMid is: ";
    printVec(fMid);

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
        lteDimension = dimension;
      } else {
        gteDimension = dimension;
      }
    }

    auto candidateWitness = vector<int>(3, -1); 

    if(mid[sliceDimension] <= fMid[sliceDimension]) {
      candidateWitness[sliceDimension] = sliceDimensionVal;
      candidateWitness[lteDimension] = mid[lteDimension];
      candidateWitness[gteDimension] = b[gteDimension];

      auto fCandidateWitness = f(candidateWitness);
      assert(candidateWitness[sliceDimension] <= fCandidateWitness[sliceDimension]);

      if(candidateWitness[gteDimension] <= fCandidateWitness[gteDimension]) {
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

  vector<int> getFreeCoords() {
    vector<int> result;
    for(int i = 0; i < 3; i++) {
      if(i != sliceDimension) {
        result.push_back(i);
      }
    }
    return result;
  }

};

void printVec(vector<int>& v) {
  for(const auto i : v) {
    cout << i << '\t';
  }
  cout << endl;
}


bool isFixpoint(vector<int> point, function<vector<int> (const vector<int>&)> f) {
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

