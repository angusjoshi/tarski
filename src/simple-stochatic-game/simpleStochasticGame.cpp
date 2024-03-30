//
// Created by angus on 10/02/2024.
//

#include "simpleStochasticGame.h"
#include "../fixpoint/latticeUtil.h"

simpleStochasticGame::simpleStochasticGame(vector<simpleVertex> vs, f_t eps) : vertices{vs}, EPSILON{eps} {
//    N = LLONG_MAX;
//    N = 1 << (vs.size() - 3)*(vs.size() - 2);

//    contractionFactor = 1.f - (1.f / (1ll << vs.size()));
    contractionFactor = 0.99;
    N = floor((float)1 / EPSILON * contractionFactor);

    bool seenMaxBefore = false;
    for(int i = 0; i < vs.size(); i++) {
        if(vs[i].type == maxSink) {
            if(seenMaxBefore) {
                throw runtime_error("more than one max sink detected.");
            }
            seenMaxBefore = true;
            maxSinkI = i;
        }
    }

    if(!seenMaxBefore) throw runtime_error("no maxSink detected.");

}

const vector<int_t> simpleStochasticGame::getTop() {
    return vector<int_t>(vertices.size() - 1, N);
}

const vector<f_t> simpleStochasticGame::getCtsStart() {
    return vector<f_t>(vertices.size() - 1, 0);
}
const vector<int_t> simpleStochasticGame::getBot() {
    return vector<int_t>(vertices.size() - 1, 0);
}


const vector<int_t> simpleStochasticGame::discretize(const vector<f_t>& d) {
    vector<int_t> result;
    result.reserve(d.size());
    for(const auto& val : d) {
        result.push_back(N * val);
    }
    return result;
}

const vector<f_t> simpleStochasticGame::unDiscretize(const vector<int_t>& v) {
    vector<f_t> result;
    result.reserve(v.size());

    for(auto val : v) {
        double unDiscretized = (f_t) val / N;
        result.push_back(unDiscretized);
    }

    return result;
}


const void simpleStochasticGame::contract(vector<f_t>& v) {
    for(auto& val : v) {
        val *= contractionFactor;
    }
}
const vector<f_t> simpleStochasticGame::computeFunction(const vector<f_t>& vf) {
    vector<f_t> result;

    for(const auto& vertex : vertices) {
        switch(vertex.type) {
            case mini:
            {
                f_t minVal = 1;
                for(const auto& s : vertex.succs) {
                    if(s.i == maxSinkI) {
                        continue;
                    }

                    minVal = min(minVal, vf[s.i]);
                }
                result.push_back(minVal);
                break;
            }

            case maxi:
            {
                f_t maxVal = 0;
                for(const auto& s : vertex.succs) {
                    if(s.i == maxSinkI) {
                        maxVal = 1;
                        continue;
                    }

                    maxVal = max(maxVal, vf[s.i]);
                }
                result.push_back(maxVal);
                break;
            }

            case chance:
            {
                f_t sumVal = 0;
                for(const auto& s : vertex.succs) {
                    if(s.i == maxSinkI) {
                        sumVal += s.p;
                        continue;
                    }

                    sumVal += vf[s.i] * s.p;
                }
                result.push_back(sumVal);
                break;
            }

            case maxSink:
                break;
        }
    }

    contract(result);
    return result;
}

const function<vector<int_t>(const vector<int_t>& v)> simpleStochasticGame::getMonotoneFunction() {
    return [this](const vector<int_t>& v) {
        vector<f_t> vf = unDiscretize(v);
        vector<f_t> result = computeFunction(vf);
        return discretize(result);
    };
}

const function<vector<f_t>(const vector<f_t>& v)> simpleStochasticGame::getCtsMonotoneFunction() {
    return [this](const vector<f_t>& v) {
        return computeFunction(v);
    };
    return {};
}

const void simpleStochasticGame::print() {
    for(int i = 0 ; i < vertices.size(); i++) {
        const auto& v = vertices[i];
        printf("vertex: %d, type is: %d\n", i, v.type);
        printf("succs are: \n");
        for(const auto& succ : v.succs) {
            printf("\t index: %d, p: %f\n", succ.i, succ.p);
        }
    }
}
