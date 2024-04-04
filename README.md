# tarski

algorithms for solving the `Tarski` problem. that is, algorithms for finding fixpoints of monotone functions `f : [N]^d -> [N]^d`
on bounded sublattices of the integer lattice. applications of `Tarski` to problems in game theory are also included.

## usage
install [soplex](https://soplex.zib.de/), [SCIP](https://www.scipopt.org/), [cmake](https://cmake.org/), [GMP](https://gmplib.org/), [boost](https://www.boost.org/).

clone the repository,
change the include directory paths lib paths for all dependencies in [CMakeLists.txt](https://github.com/angusjoshi/tarski/blob/main/src/CMakeLists.txt) to be the location on your machine.

```
cd src
cmake .
make
./src
```

all data used in plots for the report can be found in [makePlots.py](https://github.com/angusjoshi/tarski/blob/main/src/analysis/makePlots.py),
and was manually entered after running the included C++ program.
