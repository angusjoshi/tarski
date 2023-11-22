//
// Created by angus on 29/10/2023.
//

#ifndef SRC_EXAMPLES_H
#define SRC_EXAMPLES_H

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

auto example1 = vector<vector<vector<vector<int>>>> {
        vector<vector<vector<int>>> {
                vector<vector<int>> { vector<int> {0, 1, 0}, vector<int> {0, 1, 0}, vector<int> {0, 1, 2}, vector<int> {0, 1, 2} },
                vector<vector<int>> { vector<int> {0, 2, 0}, vector<int> {0, 2, 1}, vector<int> {0, 2, 2}, vector<int> {0, 2, 2} },
                vector<vector<int>> { vector<int> {0, 2, 1}, vector<int> {1, 2, 1}, vector<int> {1, 2, 2}, vector<int> {1, 2, 2} },
                vector<vector<int>> { vector<int> {0, 2, 1}, vector<int> {1, 2, 1}, vector<int> {1, 2, 2}, vector<int> {1, 2, 2} }
        },
        vector<vector<vector<int>>> {
                vector<vector<int>> { vector<int> {0, 1, 1}, vector<int> {0, 1, 1}, vector<int> {0, 1, 2}, vector<int> {0, 1, 2} },
                vector<vector<int>> { vector<int> {0, 2, 1}, vector<int> {0, 2, 1}, vector<int> {0, 2, 2}, vector<int> {0, 2, 2} },
                vector<vector<int>> { vector<int> {0, 2, 1}, vector<int> {1, 2, 1}, vector<int> {1, 2, 2}, vector<int> {1, 2, 2} },
                vector<vector<int>> { vector<int> {0, 2, 2}, vector<int> {1, 2, 3}, vector<int> {1, 2, 3}, vector<int> {1, 2, 3} }
        },
        vector<vector<vector<int>>> {
                vector<vector<int>> { vector<int> {0, 1, 1}, vector<int> {0, 1, 1}, vector<int> {0, 1, 2}, vector<int> {0, 2, 2} },
                vector<vector<int>> { vector<int> {0, 2, 2}, vector<int> {0, 2, 2}, vector<int> {0, 2, 2}, vector<int> {0, 2, 3} },
                vector<vector<int>> { vector<int> {0, 2, 2}, vector<int> {1, 2, 2}, vector<int> {1, 2, 2}, vector<int> {1, 2, 3} },
                vector<vector<int>> { vector<int> {1, 2, 2}, vector<int> {1, 2, 3}, vector<int> {2, 2, 3}, vector<int> {2, 2, 3} }
        },
        vector<vector<vector<int>>> {
                vector<vector<int>> { vector<int> {0, 2, 1}, vector<int> {0, 2, 1}, vector<int> {1, 2, 2}, vector<int> {1, 2, 2} },
                vector<vector<int>> { vector<int> {1, 2, 2}, vector<int> {1, 2, 3}, vector<int> {2, 2, 3}, vector<int> {2, 2, 3} },
                vector<vector<int>> { vector<int> {3, 2, 2}, vector<int> {3, 2, 3}, vector<int> {3, 2, 3}, vector<int> {3, 2, 3} },
                vector<vector<int>> { vector<int> {3, 2, 2}, vector<int> {3, 2, 3}, vector<int> {3, 2, 3}, vector<int> {3, 2, 3} }
        }
};

//auto example2 = [](const vector<int>& v) {
//    // example 2 is a 6 dimensional problem on [9]^d.
//    assert(v.size() == 6);
//
//    return vector<int> {2, 1, 4, 5, 2, 2};
//};
#endif //SRC_EXAMPLES_H
