#include <iostream>
#include "examples.h"
#include "latticeUtil.h"
#include "recursiveBinarySearch.h"
#include "fixDecompAlgorithm.h"
#include <chrono>


int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    vector<int> x {2, 1, 4, 5, 2, 2, 8, 3, 4, 2, 8, 5, 2, 8, 6};
    auto example2 = [&x](const vector<int>& v) -> const auto& {
        assert(v.size() == 15);

        return x;
    };


    long long queryCount = 0;
    auto f = [&example2, &queryCount] (const auto& v) -> const auto& {
        queryCount++;
        return example2(v);
    };

    auto g = getDirectionFunction(f);

    vector<int> bot {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<int> top {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    auto t1 = high_resolution_clock::now();

//    auto fixpoint = findFixpointRecBin(bot, top, g);
    auto fixpoint = findFixpointByFixDecomposition(bot, top, g);

    auto t2 = high_resolution_clock::now();


    cout << "fixpoint is: ";
    printVec(fixpoint);
    cout << endl << "query count is: " << queryCount << endl;

    duration<double, std::milli> ms = t2 - t1;
    std::cout << "time was: " << ms.count() << "ms" << endl;

    return 0;
}


