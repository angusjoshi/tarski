//
// Created by angus on 02/03/2024.
//

#include "simpleStochasticGameGenerator.h"

simpleStochasticGame getExampleOne() {
    simpleVertex v0 = {
            .type = maxi,
            .succs =  { { 2 },
                        { 4 }}
    };

    simpleVertex v1 = {
            .type = mini,
            .succs =  { { 2 },
                        { 4 }}
    };

    f_t weirdP = 0.125112351235663241234;
    f_t weirdP2 = 0.4421234513462345;
    simpleVertex v2 = {
            .type = chance,
            .succs =  { {6, weirdP },
                        { 7, weirdP2 },
                        { 0, 1 - (weirdP + weirdP2)},
                        }
    };

    simpleVertex v3 = {
            .type = maxi,
            .succs =  { { 1 },
                        { 2 }}
    };

    simpleVertex v4 = {
            .type = chance,
            .succs =  { { 1, weirdP },
                        { 5, 1 - weirdP }}
    };

    simpleVertex v5 = {
            .type = mini,
            .succs =  { { 0 },
                        { 3 }}
    };

    simpleVertex maxTarget = {
            .type = maxSink,
    };

    simpleVertex minTarget = {
            .type = minSink,
    };

    return  {{v0, v1, v2, v3, v4, v5, maxTarget, minTarget}};
}

simpleStochasticGame generateSimpleStochasticGame(int size) {

    return {{}};
}
