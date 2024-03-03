//
// Created by angus on 03/03/2024.
//

#include "shapleyStochasticGame.h"
#include <soplex.h>
#include <algorithm>

shapleyStochasticGame::shapleyStochasticGame(vector<shapleyVertex> vertices) : vertices{vertices} {
    // find max payoff
    int_t M = 0;
    for(const auto& vertex : vertices) {
        for(const auto& row : vertex.payoffs) {
            for(const auto& cell : row) {
                M = M < cell ? cell : M;
            }
        }
    }

    f_t q = 1.f;

    for(const auto& vertex : vertices) {
        for(const auto& row : vertex.succs) {
            for(const auto& cell : row) {
                f_t current = 1;
                for(const auto& succ : cell) {
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
}

function<vector<int_t>(const vector<int_t>& v)> shapleyStochasticGame::getMonotoneFunction() {
    // TODO
    return [this](const vector<int_t>& v) {

        return vector<int_t>{};
    }
}
vector<int_t> shapleyStochasticGame::getBot() {
    vector<int_t> bot(vertices.size(), -N);
    return bot;
}
vector<int_t> shapleyStochasticGame::getTop() {
    vector<int_t> top(vertices.size(), N);
    return top;
}

// example usage of soplex below
//SoPlex mysoplex;
//
///* set the objective sense */
//mysoplex.setIntParam(SoPlex::OBJSENSE, SoPlex::OBJSENSE_MINIMIZE);
//
///* we first add variables */
//DSVector dummycol(0);
//mysoplex.addColReal(LPCol(3.0, dummycol, infinity, 1.0));
//mysoplex.addColReal(LPCol(2.0, dummycol, infinity, 1.0));
//
///* then constraints one by one */
//DSVector row1(2);
//row1.add(0, 0.2);
//row1.add(1, 1.0);
//mysoplex.addRowReal(LPRow(2.0, row1, infinity));
//
///* NOTE: alternatively, we could have added the matrix nonzeros in dummycol already; nonexisting rows are then
// * created automatically. */
//
///* write LP in .lp format */
//mysoplex.writeFileReal("dump_real.lp", NULL, NULL, NULL);
//
///* solve LP */
//SPxSolver::Status stat;
//DVector prim(2);
//DVector dual(1);
//stat = mysoplex.optimize();
//
///* get solution */
//if(stat == SPxSolver::OPTIMAL)
//{
//mysoplex.getPrimal(prim);
//mysoplex.getDual(dual);
//std::cout << "LP solved to optimality.\n";
//std::cout << "Objective value is " << mysoplex.objValueReal() << ".\n";
//std::cout << "Primal solution is [" << prim[0] << ", " << prim[1] << "].\n";
//std::cout << "Dual solution is [" << dual[0] << "].\n";
//}
//else
//{
//std::cout << "Error: SoPlex returned with status " << stat << ".\n";
//}
