//
// Created by angus on 10/02/2024.
//

#include "simpleStochasticGame.h"


int_t simpleStochasticGame::discretize(f_t d) {
    size_t n = this->vertices.size();
    int_t N = 1 << (n*n);
    f_t result = N * d;
    return result.get_num();
}

vector<f_t> simpleStochasticGame::unDiscretize(const vector<int_t>& v) {
    size_t n = this->vertices.size();
    int_t N = 1 << (n*n);

    vector<f_t> result;
    for(auto val : v) {
//        double unDicretized = val / (double)N;
//        result.push_back(unDicretized);
    }

    return result;
}


function<vector<int_t>(const vector<int_t>& v)> simpleStochasticGame::getMonotoneFunction() {
    return [this](const vector<int_t>& v) {
        vector<int_t> result;

        for(const auto& vertex : this->vertices) {
            if(vertex.succs.empty()) {
                result.emplace_back(0);
            }
            switch(vertex.type) {
                case mini:
                    {
                        int_t minVal = INT_MAX;
                        for(const auto& s : vertex.succs) {
                            minVal = min(minVal, v[s.i]);
                        }
                        result.push_back(minVal);
                        break;
                    }

                case maxi:
                    {
                        int_t maxVal = 0;
                        for(const auto& s : vertex.succs) {
                            maxVal = max(maxVal, v[s.i]);
                        }
                        result.push_back(maxVal);
                        break;
                    }

                case chance:
                    int_t sumVal = 0;
                    for(const auto& s : vertex.succs) {
                        sumVal += v[s.i] * s.p;
                    }
                    result.push_back(sumVal);
                    break;
            }
        }
        return result;
    };
}
