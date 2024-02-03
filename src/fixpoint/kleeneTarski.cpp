//
// Created by angus on 05/11/2023.
//

#include "kleeneTarski.h"
#include "latticeUtil.h"

vector<int> kleeneTarski(const vector<int>& start,
                         const function<vector<int> (const vector<int>&)>& f) {
    vector<int> current = start;
    vector<int> fCurrent = f(current);

    while(!latEq(current, fCurrent)) {
        current = fCurrent;
        fCurrent = f(current);
    }

    if(!latEq(current, fCurrent)) throw;
    return current;
}
