//
// Created by angus on 02/12/2023.
//

#include "runAnalysis.h"
#include "../arrival/generateRandomInstance.h"
#include <iostream>
#include "../fixpoint/latticeUtil.h"
#include "../arrival/arrivalUtil.h"
#include "../arrival/arrivalInstance.h"
#include "../arrival/preprocessInstance.h"
#include "../fixpoint/fixDecompAlgorithm.h"

using namespace std;

vector<int> sizes {3, 5, 8, 12, 15, 20};
vector<int> danqiyeSizes {3, 4, 5, 6, 7, 8};

void runAndPrintAnalysis() {
    vector<pair<int, int>> instance = generateRandomInstance(23);

    cout << "\n\n\n ===============RAND=============\n";
    printInstance(instance);

    vector<pair<int, int>> preprocessedInstance = preprocessInstance(instance);

    cout << "\n\n\n ===============PROCESSED=============\n";
    printInstance(preprocessedInstance);

    ArrivalInstance arrivalInstance {std::move(preprocessedInstance)};
    auto g = arrivalInstance.getDirectionFunction();
    auto bot = arrivalInstance.getBot();
    auto top = arrivalInstance.getTop();

    int queryCounter = 0;
    auto f =  [&g, &queryCounter] (const auto& v) {
        queryCounter++;
        return g(v);
    };

//    auto fixpoint = findFixpointRecBin(bot, top, f);
    auto fixpoint = findFixpointByFixDecomposition(bot, top, f);

    cout << "done!!!!!!! fixpoint is: ";
    printVec(fixpoint);
    vector<direction> dirs = f(fixpoint);
    cout << "query count is: " << queryCounter << endl;

    int sinkInflow = arrivalInstance.computeSinkInflow(fixpoint);
    cout << "sinkInflow is: " << sinkInflow << endl;

    assert(isAllFixed(dirs));
}