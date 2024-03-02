//
// Created by angus on 02/03/2024.
//

#include "simpleStochasticGameGenerator.h"

simpleStochasticGame getExampleOne() {
    vertex v0 = {
            .type = maxi,
            .succs =  { { 2 },
                        { 4 }}
    };

    vertex v1 = {
            .type = mini,
            .succs =  { { 2, 0,},
                        { 4, 0,}}
    };

    vertex v2 = {
            .type = chance,
            .succs =  { {6, 1.f/3 },
                        { 7, 1.f/3 },
                        { 0, 1.f/3,},
                        }
    };

    vertex v3 = {
            .type = maxi,
            .succs =  { { 1 },
                        { 2 }}
    };

    vertex v4 = {
            .type = chance,
            .succs =  { { 1, 4.f/5 },
                        { 4, 0,}}
    };

    vertex v5 = {
            .type = mini,
            .succs =  { { 0 },
                        { 3 }}
    };

    vertex maxTarget = {
            .type = maxSink,
    };

    vertex minTarget = {
            .type = minSink,
    };

    return  {{v0, v1, v2, v3, v4, v5, maxTarget, minTarget}};
}

simpleStochasticGame generateSimpleStochasticGame(int size) {

    return {{}};
}
