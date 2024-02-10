//
// Created by angus on 05/11/2023.
//

#ifndef SRC_KLEENETARSKI_H
#define SRC_KLEENETARSKI_H

#include <vector>
#include <functional>
#include "../config.h"

using namespace std;

vector<int_t> kleeneTarski(const vector<int_t>& bot,
                         const function<vector<int_t> (const vector<int_t>&)>& f);

#endif //SRC_KLEENETARSKI_H
