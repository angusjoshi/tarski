//
// Created by angus on 06/03/2024.
//

#include "shapleyStochasticGameGenerator.h"
#include <random>

const double PROB_OF_NOT_HALTING = 0.8;
const int MAX_PAYOFF_VAL = 10;

shapleyStochasticGame getShapleyExampleOne() {
    shapleyVertex v0 = {
        {
            {{ {2, 0.4}, {4, 0.5} }, { {1, 0.8}, {0, 0.15} }, { {2, 0.2}, {0, 0.2} } },
            {{ {0, 0.4}, {3, 0.5} }, { {3, 0.4}, {5, 0.5} }, { {4, 0.5}, {1, 0.3} } },
            { { {1, 0.15}, {5, 0.23} }, { {4, 0.6}, {1, 0.2} }, { {1, 0.12}, {3, 0.8} } },
        },
        {
            {1, -2, 3},
            {-1, 2, 1},
            {4, -5, 2},
        }
    };
    shapleyVertex v1 = {
        {
            {
                { { {1, 0.3}, {3, 0.6} }, { {2, 0.85}, {5, 0.1} }, { {5, 0.2}, {2, 0.6} } },
                { { {1, 0.6}, {4, 0.2} }, { {2, 0.3}, {4, 0.6} }, { {3, 0.3}, {2, 0.3} } },
                { { {1, 0.15}, {2, 0.53} }, { {5, 0.6}, {1, 0.3} }, { {4, 0.12}, {0, 0.8} } },
            }
        },
        {
            {2, 4, -3},
            {-10, 4, -1},
            {5, -2, -3},
        }
    };
    shapleyVertex v2 = {
        {
            {
                { { {3, 0.6}, {0, 0.3} }, { {2, 0.4}, {4, 0.5} }, { {3, 0.4}, {0, 0.5} } },
                { { {3, 0.4}, {3, 0.5} }, { {2, 0.5}, {3, 0.45} }, { {3, 0.3}, {2, 0.4} } },
                { { {2, 0.35}, {3, 0.43} }, { {3, 0.4}, {5, 0.5} }, { {4, 0.12}, {5, 0.8} } },
            }
        },
        {
            {5, 3, 2},
            {-1, -2, -4},
            {0, -5, 4},
        }
    };
    shapleyVertex v3 = {
        {
            {
                { { {4, 0.4}, {5, 0.3} }, { {5, 0.4}, {2, 0.05} }, { {3, 0.4}, {2, 0.4} } },
                { { {3, 0.2}, {4, 0.3} }, { {5, 0.6}, {3, 0.3} }, { {3, 0.3}, {0, 0.4} } },
                { { {0, 0.45}, {5, 0.43} }, { {5, 0.3}, {4, 0.68} }, { {4, 0.12}, {0, 0.8} } },
            }
        },
        {
            {-1, 3, 4},
            {-3, -2, 10},
            {14, -12, 0},
        }
    };
    shapleyVertex v4 = {
        {
            {
                { { {4, 0.3}, {0, 0.6} }, { {4, 0.6}, {1, 0.25} }, { {4, 0.4}, {3, 0.4} } },
                { { {2, 0.6}, {0, 0.2} }, { {2, 0.6}, {4, 0.2} }, { {5, 0.4}, {4, 0.4} } },
                { { {3, 0.35}, {2, 0.53} }, { {2, 0.3}, {3, 0.4} }, { {2, 0.62}, {4, 0.3} } },
            }
        },
        {
            {4, 12, -3},
            {-6, 4, 3},
            {-4, -5, 4},
        }
    };
    shapleyVertex v5 = {
        {
            {
                { { {2, 0.4}, {4, 0.5} }, { {1, 0.8}, {0, 0.15} }, { {2, 0.2}, {0, 0.2} } },
                { { {0, 0.4}, {3, 0.5} }, { {3, 0.4}, {5, 0.5} }, { {2, 0.5}, {1, 0.3} } },
                { { {1, 0.15}, {5, 0.23} }, { {4, 0.6}, {1, 0.2} }, { {1, 0.12}, {3, 0.8} } },
            }
    },
    {
        {1, -2, 3},
        {-1, 2, 1},
        {4, -5, 2},
    }
    };

    shapleyVertex v6 = {
            {
                    {
                            { { {2, 0.4}, {4, 0.5} }, { {1, 0.8}, {0, 0.15} }, { {2, 0.2}, {0, 0.2} } },
                            { { {0, 0.4}, {3, 0.5} }, { {3, 0.4}, {5, 0.5} }, { {2, 0.5}, {1, 0.3} } },
                            { { {1, 0.15}, {5, 0.23} }, { {4, 0.6}, {1, 0.2} }, { {1, 0.12}, {3, 0.8} } },
                    }
            },
            {
                    {1, -2, 3},
                    {-1, 2, 1},
                    {4, -5, 2},
            }
    };

    return {{v0, v1, v2, v3, v4, v5, v6}};
}

shapleyStochasticGame generateShapleyStochasticGame(int size) {
    assert(size >= 1);
    // for shapley, there is no specific target so don't need as many vertices
    // as the simple stochastic games.

    // it will be assumed that the action space is 3x3 at every vertex,
    // every action joint action will yield a probability distribution on two successors.

    std::random_device rd;
    std::mt19937 gen(rd());
    // note the distribution uses the closed range for some reason...
    std::uniform_int_distribution<> nodeDistribution(0, size - 1);

    std::uniform_int_distribution<> payoffDistribution(-MAX_PAYOFF_VAL, MAX_PAYOFF_VAL);


    // predefined probability of not halting at every transition. split this
    // into two.
    std::uniform_real_distribution<> partitionDistribution(0, PROB_OF_NOT_HALTING);

    vector<shapleyVertex> vertices;
    vertices.reserve(size);

    for(int i = 0; i < size; i++) {
        vector<vector<int>> payoffMatrix(3, vector<int>(3, 0));

        for(auto& row : payoffMatrix) {
            for(auto& cell : row) {
                cell = payoffDistribution(gen);
            }
        }

        vector<vector<vector<shapleySuccessor>>> successorMatrix(
                3,
                vector<vector<shapleySuccessor>>(3, vector<shapleySuccessor>{}));

        for(auto& row : successorMatrix) {
            for(auto& cell : row) {
                auto p = partitionDistribution(gen);
                cell.push_back({nodeDistribution(gen), p});
                cell.push_back({nodeDistribution(gen), PROB_OF_NOT_HALTING - p});
            }
        }

        vertices.push_back({successorMatrix, payoffMatrix});
    }

    return { vertices };
}
