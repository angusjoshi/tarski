//
// Created by angus on 10/02/2024.
//

#include "simpleStochasticGame.h"

simpleStochasticGame::simpleStochasticGame(vector<simpleVertex> vs) {
    vertices = vs;
//    N = LLONG_MAX;
    N = 1 << (vs.size() - 3)*(vs.size() - 2);

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

    contractionFactor = 1.f - (1.f / (1ll << vs.size()));
}

vector<int_t> simpleStochasticGame::getTop() {
    return vector<int_t>(vertices.size() - 2, N);
}

vector<int_t> simpleStochasticGame::getBot() {
    return vector<int_t>(vertices.size() - 2, 0);
}


vector<int_t> simpleStochasticGame::discretize(const vector<f_t>& d) {
    vector<int_t> result;
    result.reserve(d.size());
    for(const auto& val : d) {
        result.push_back(N * val);
    }
    return result;
}

vector<f_t> simpleStochasticGame::unDiscretize(const vector<int_t>& v) {
    vector<f_t> result;
    result.reserve(v.size());

    for(auto val : v) {
        double unDiscretized = (f_t) val / N;
        result.push_back(unDiscretized);
    }

    return result;
}


void simpleStochasticGame::contract(vector<f_t>& v) {
    for(auto& val : v) {
        val *= contractionFactor;
    }
}

function<vector<int_t>(const vector<int_t>& v)> simpleStochasticGame::getMonotoneFunction() {
    return [this](const vector<int_t>& v) {
        vector<f_t> vf = unDiscretize(v);
        vector<f_t> resultf;

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
                        resultf.push_back(minVal);
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
                        resultf.push_back(maxVal);
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
                        resultf.push_back(sumVal);
                        break;
                    }

                case maxSink:
                    break;
            }
        }

        contract(resultf);

        return discretize(resultf);
    };
}

void simpleStochasticGame::print() {
    for(int i = 0 ; i < vertices.size(); i++) {
        const auto& v = vertices[i];
        printf("vertex: %d, type is: %d\n", i, v.type);
        printf("succs are: \n");
        for(const auto& succ : v.succs) {
            printf("\t index: %d, p: %f\n", succ.i, succ.p);
        }
    }
}
