//
// Created by angus on 02/03/2024.
//

#include "simpleStochasticGameGenerator.h"
#include <random>

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


    return  {{v0, v1, v2, v3, v4, v5, maxTarget}};
}

simpleStochasticGame generateSimpleStochasticGame(int size) {
    //first vertex is assumed to be the start,
    // second last is min sink,
    // last is max sink.
    // so need at least 3 vertices.
    assert(size >= 3);

    // the last vertex is assumed to be player 1s target,
    // first is assumed to be the initial vertex.

    std::random_device rd;
    std::mt19937 gen(rd());
    // note the distribution uses the closed range for some reason...
    std::uniform_int_distribution<> nodeDistribution(0, size - 1);

    // bit hacky but using the last guy in the enum spec seems
    // like the best way to gen a distribution.
    // also drop the last 2 (don't want extra max/mins)

    std::uniform_int_distribution<> typeDist(0, last - 3);

    std::uniform_real_distribution<> partitionDistribution(0);

    vector<simpleVertex> vertices;
    vertices.reserve(size);

    for(int i = 0; i < size - 2; i++) {
        double p = partitionDistribution(gen);
        simpleVertex v = {
                .type = static_cast<simpleVertexType>(typeDist(gen)),
                .succs = {
                    { .i = nodeDistribution(gen), .p = p },
                    { .i = nodeDistribution(gen), .p = 1 - p },
                }
        };

        vertices.push_back(v);
    }

    simpleVertex maxiSink = {
            .type = maxSink,
    };
    vertices.push_back(maxiSink);

    return { vertices };
}
