//
// Created by angus on 05/11/2023.
//

#include "kleeneTarski.h"
#include "latticeUtil.h"

vector<int> kleeneTarski(const vector<int>& bot,
                         const function<vector<int> (const vector<int>&)>& f) {
    vector<int> current = bot;
    vector<int> fCurrent = f(current);

    while(!latEq(current, bot)) {
        current = fCurrent;
        fCurrent = f(current);
    }

    return current;
}
