//
// Created by angus on 06/03/2024.
//

#include "shapleyStochasticGameGenerator.h"

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
