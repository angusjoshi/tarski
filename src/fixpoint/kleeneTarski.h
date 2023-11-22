//
// Created by angus on 05/11/2023.
//

#ifndef SRC_KLEENETARSKI_H
#define SRC_KLEENETARSKI_H

#include <vector>
#include <functional>

using namespace std;

vector<int> kleeneTarski(const vector<int>& bot,
                         const function<vector<int> (const vector<int>&)>& f);

#endif //SRC_KLEENETARSKI_H
