//
// Created by angus on 10/02/2024.
//

#include "simpleStochasticGame.h"

function<vector<int>(const vector<int>& v)> simpleStochasticGame::getMonotoneFunction() {
    return [this](const vector<int>& v) {
        for(const auto& vertex : this->vertices) {
            switch(vertex.type) {
                case mini:
                    break;
                case maxi:
                    break;
                case chance:
                    break;
                case maxSink:
                case minSink:
                    break;
            }
        }
        vector<int> result;
        return result;
    };
}
