//
// Created by angus on 05/11/2023.
//

#include "kleeneTarski.h"
#include "latticeUtil.h"
#include <iostream>

vector<int> kleeneTarski(const vector<int>& bot,
                         const function<vector<int> (const vector<int>&)>& f) {
    vector<int> current = bot;
    vector<int> fCurrent = f(current);

    while(!latEq(current, fCurrent)) {
        current = fCurrent;
        fCurrent = f(current);
    }

    if(!latEq(current, fCurrent)) throw;
    return current;
}
