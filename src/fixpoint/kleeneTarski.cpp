//
// Created by angus on 05/11/2023.
//

#include "kleeneTarski.h"
#include "latticeUtil.h"
#include <iostream>

vector<int> kleeneTarski(const vector<int>& start,
                         const function<vector<int> (const vector<int>&)>& f) {
    vector<int> current = start;
    vector<int> fCurrent = f(current);

    while(!latEq(current, fCurrent)) {
        cout << "current is: ";
        printVec(current);
        current = fCurrent;
        fCurrent = f(current);
    }

    cout << "current is: ";
    printVec(current);
    if(!latEq(current, fCurrent)) throw;
    return current;
}
