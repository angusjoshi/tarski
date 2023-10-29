//
// Created by angus on 29/10/2023.
//

#ifndef SRC_EXAMPLES_H
#define SRC_EXAMPLES_H

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

#endif //SRC_EXAMPLES_H
