//
// Created by angus on 05/11/2023.
//

#ifndef SRC_INNERALGORITHM_H
#define SRC_INNERALGORITHM_H

#include <vector>
#include <functional>

using namespace std;

class InnerAlgorithm {

private:
    vector<int> bot;
    vector<int> top;
    vector<int> a;
    vector<int> u;
    vector<int> d;
    vector<int> b;

    int sliceDimension;
    int sliceDimensionVal;
    function<vector<int> (const vector<int>&)> f;

    vector<int> getMidInSlice(const vector<int>& x, const vector<int>& y) const;
    vector<int> helper();
    vector<int> getFreeCoords() const;
    bool sliceLe(vector<int>& x, vector<int>& y) const;

public:
    InnerAlgorithm(const vector<int>& bot, const vector<int>& top, const function<vector<int> (const vector<int>&)>& f);

    vector<int> findMonotonePoint(
            vector<int> _bot,
            vector<int> _top,
            int _sliceDimension,
            int _sliceDimensionVal);
};

#endif //SRC_INNERALGORITHM_H
