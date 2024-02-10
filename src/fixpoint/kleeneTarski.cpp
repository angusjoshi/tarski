//
// Created by angus on 05/11/2023.
//

#include "kleeneTarski.h"
#include "latticeUtil.h"

vector<int_t> kleeneTarski(const vector<int_t>& start,
                         const function<vector<int_t> (const vector<int_t>&)>& f) {
    vector<int_t> current = start;
    vector<int_t> fCurrent = f(current);

    while(!latEq(current, fCurrent)) {
        current = fCurrent;
        fCurrent = f(current);
    }

    if(!latEq(current, fCurrent)) throw;
    return current;
}
