//
// Created by angus on 03/03/2024.
//

#include "shapleyStochasticGame.h"
#include <soplex.h>
#include <algorithm>
#include <thread>
#include "../fixpoint/latticeUtil.h"

using namespace soplex;

shapleyStochasticGame::shapleyStochasticGame(vector<shapleyVertex> vertices, f_t eps = 0.01) : vertices{vertices}, EPSILON{eps} {
    // find max payoff
    assert(vertices.size() != 0);
    assert(vertices[0].payoffs.size() == vertices[0].succs.size());

    int_t M = 0;
    for(const auto& vertex : vertices) {
        for(const auto& row : vertex.payoffs) {
            for(const auto& cell : row) {
                M = M < cell ? cell : M;
            }
        }
    }

    q = 1.f;

    for(const auto& vertex : vertices) {
        for(const auto& row : vertex.succs) {
            for(const auto& cell : row) {
                f_t current = 1;
                for(const auto& succ : cell) {
                    assert(succ.i < vertices.size() && succ.i >= 0);
                    current -= succ.p;
                }

                if(current <= 0) {
                    throw runtime_error("vertex found with probability of dying immediately <= 0.");
                }

                q = q > current ? current : q;
            }
        }
    }

    N = (4*M)/(EPSILON*q);
    scale = 4/EPSILON;
}

f_t getZeroSumVal(const vector<vector<f_t>>& payoffMatrix) {
    assert(!payoffMatrix.empty());
    SoPlex mysoplex;
    mysoplex.setIntParam(SoPlex::OBJSENSE, SoPlex::OBJSENSE_MAXIMIZE);
    mysoplex.setIntParam(SoPlex::VERBOSITY, SoPlex::VERBOSITY_ERROR);
    DSVector dummycol(0);
    mysoplex.addColReal(LPCol(1.0, dummycol, infinity, -infinity));
    for(const auto& _ : payoffMatrix) {
        mysoplex.addColReal(LPCol(0, dummycol, infinity, 0));
    }

    for(int j = 0; j < payoffMatrix[0].size(); j++) {
        DSVector currRow(payoffMatrix[0].size() + 1ul);
        currRow.add(0, 1);
        for(int i = 0; i < payoffMatrix.size(); i++) {
            currRow.add(i + 1, -payoffMatrix[i][j]);
        }

        mysoplex.addRowReal(LPRow(currRow, LPRow::LESS_EQUAL, 0));
    }

    DSVector equalityRow(payoffMatrix[0].size() + 1ul);
    equalityRow.add(0, 0);
    for(int i = 1; i <= payoffMatrix.size(); i++) {
        equalityRow.add(i, 1);
    }
    mysoplex.addRowReal(LPRow(equalityRow, LPRow::EQUAL, 1));

    auto status = mysoplex.optimize();
    assert(status == soplex::SPxSolver::OPTIMAL);
    return mysoplex.objValueReal();
}

void add(vector<vector<f_t>>& a, const vector<vector<int>>& b) {
    assert(a.size() == b.size());
    assert(a[0].size() == b[0].size());

    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < a[i].size(); j++) {
            a[i][j] += b[i][j];
        }
    }
}



vector<f_t> shapleyStochasticGame::scaleDown(const vector<int_t>& v) {
    vector<f_t> result;
    result.reserve(v.size());
    for(const auto& x : v) {
        result.emplace_back(x / scale);
    }
    return result;
}

vector<int_t> shapleyStochasticGame::scaleUp(const vector<f_t>& v) {
    vector<int_t> result;
    result.reserve(v.size());
    for(const auto& x : v) {
        // flooring will happen during coercion to int.
        result.emplace_back(x * scale);
    }
    return result;
}

function<vector<int_t>(const vector<int_t>& v)> shapleyStochasticGame::getMonotoneFunction() {
    return [this](const vector<int_t>& v) -> vector<int_t> {
        auto scaled = scaleDown(v);
        auto ctsResult = computeFunction(scaled);
        auto result = scaleUp(ctsResult);
        assert(latticeLe(result, getTop()));
        assert(latticeLe(getBot(), result));
        return result;
    };
}

vector<int_t> shapleyStochasticGame::getBot() {
    vector<int_t> bot(vertices.size(), -N);
    return bot;
}
vector<int_t> shapleyStochasticGame::getTop() {
    vector<int_t> top(vertices.size(), N);
    return top;
}

function<vector<f_t>(const vector<f_t>& v)> shapleyStochasticGame::getCtsMonotoneFunction() {
    return [this](const vector<f_t>& v) -> vector<f_t> {
        return computeFunction(v);
    };
}
const vector<f_t> shapleyStochasticGame::getCtsStart() {
    vector<f_t> start(vertices.size(), 0);
    return start;
}

const vector<f_t> shapleyStochasticGame::computeFunction(const vector<f_t>& scaled) {
    vector<f_t> results(vertices.size(), -1);
    vector<std::thread> threads;
    threads.reserve(vertices.size());

    for(int k = 0; k < vertices.size(); k++) {
        auto computeForVertex = [this, &results, k, &scaled]() {
            auto vertex = vertices[k];
            vector<vector<f_t>> m(
                    vertex.payoffs.size(),
                    vector<f_t>(vertex.payoffs[0].size(), 0));

            for(int i = 0; i < vertex.succs.size(); i++) {
                for(int j = 0; j < vertex.succs[i].size(); j++) {
                    for(const auto& succ : vertex.succs[i][j]) {
                        m[i][j] += succ.p * scaled[succ.i];
                    }
                }
            }

            add(m, vertex.payoffs);
            f_t val = getZeroSumVal(m);
            results[k] = val;
        };
        threads.emplace_back(computeForVertex);
    }

    for(std::thread& thread : threads) thread.join();
    return results;
}
void shapleyStochasticGame::print() {
    for(int i = 0; i < vertices.size(); i++) {
        auto& v = vertices[i];
        printf("vertex %d. payoff matrix is:\n", i);
        for(const auto& row : v.payoffs) {
            printf("\t");
            for(const auto& cell : row) {
                printf("%d\t", cell);
            }
            printf("\n");
        }

        printf("succ matrix is:\n");
        for(const auto& row : v.succs) {
            printf("\t");
            for(const auto& cell : row) {
                for(int i = 0; i < cell.size(); i++) {
                    const auto& succ = cell[i];
                    printf("(succ %d: to=%d, p=%f) ", i, succ.i, succ.p);
                }
                printf("\t");
            }
            printf("\n");
        }
    }
}

