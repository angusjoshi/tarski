#include <iostream>
#include "fixpoint/latticeUtil.h"
#include "fixpoint/recursiveBinarySearch.h"
#include "fixpoint/fixDecompAlgorithm.h"
#include <chrono>
#include "arrival/generateInstance.h"
#include "arrival/arrivalUtil.h"
#include "arrival/preprocessInstance.h"
#include "arrival/simpleWalk.h"
#include "arrival/arrivalInstance.h"
#include "analysis/runAnalysis.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <ortools/linear_solver/linear_solver.h>
#include <ortools/glpk/glpk_computational_form.h>
#include "config.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration;



int main() {
//    fixpointExample();
//    randExample();
//    arrivalFixpointExample();
    int_t x = 1;
    list<int_t> arr;
    arr.
    runAndPrintAnalysis();
    return 0;
}


