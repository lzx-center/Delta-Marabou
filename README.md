#  DeepInc 

Constraint solving is a fundamental approach for verifying deep neural networks (DNNs). In the field of AI safety, DNNs often undergo modifications in their structure and parameters for purposes such as repair or attack. In such scenarios, we propose the problem of incremental DNN verification, which aims to determine whether a safety property still holds after the DNN has been modified. To address this problem, we present an incremental satisfiability modulo theory (SMT) algorithm based on the Reluplex framework. Our algorithm, called DeepInc, simulates the key features of the configurations that infer the verification results of the old solving procedure. It heuristically checks whether the proofs remain valid for the modified DNN. Experimental results demonstrate that DeepInc outperforms Marabou inefficiency in most cases. Moreover, for cases where the property is violated both before and after modification, DeepInc achieves significantly faster acceleration, even when compared to the state-of-the-art verifier $\alpha,\beta$-CROWN.


Build and Dependencies
------------------------------------------------------------------------------

DeepInc depends on the Boost library,
which is automatically downloaded and built when you run make. Library CXXTEST
comes included in the repository.

The marabou build process uses CMake version 3.12 (or later).
You can get CMake [here](https://cmake.org/download/).

Marabou can be built for Linux, MacOS, or Windows machines.

### Build Instructions for Linux or MacOS

To build marabou using CMake run:
```
cd path/to/DeepInc/repo/folder
mkdir build 
cd build
cmake ..
```
For configuring to build a static Marabou binary, use the following flag
```
cmake .. 
```
To build, run the following:
```
cmake --build . --target Marabou -j 20
```

To compile in debug mode (default is release)
```
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

The compiled binary will be in the *build* directory, named _Marabou_



Getting Started
-----------------------------------------------------------------------------
### To run DeepInc from Command line 
After building Marabou the binary is located at *build/Marabou* (or *build\Release\Marabou.exe* for Windows). The
repository contains sample networks and properties in the *resources* folder.

To run Marabou, execute from the repo directory, for example:
```
./build/Marabou resources/nnet/acasxu/ACASXU_experimental_v2a_2_7.nnet resources/properties/acas_property_3.txt
```
on Linux or MacOS

### Using the run script (*Recommended*)
For ease of use, we also provide a example python script (resources/runMarabou.py). The script can take the same arguments
as the Marabou binary. The difference is that the python script also supports networks in onnx format.

Moreover, instead of passing in a property file, you could define your property with the Python API
calls [here](https://github.com/NeuralNetworkVerification/Marabou/blob/master/resources/runMarabou.py#L80-L81).

### Choice of solver configurations

Currently the default configuration of Marabou is a *single-threaded* one that
uses DeepPoly analysis for bound tightening, and the DeepSoI procedure during the complete search.
For optimal runtime performance, you need to build Marabou with Gurobi enabled (See sub-section below for Gurobi installation),
so that LPs are solved by Gurobi instead of the open-source native simplex engine.  

You could also leverage *parallelism* by setting the num-workers option to N. This will spawn N threads, each solving
the original verification query using the single-threaded configuration with
a different random seed. This is the preferred parallelization strategy for low level of parallelism (e.g. N < 30).
For example to solve a query using this mode with 4 threads spawned:
```
./resources/runMarabou.py resources/nnet/mnist/mnist10x10.nnet resources/properties/mnist/image3_target6_epsilon0.05.txt --num-workers=4
```

If you have access to a large number of threads, you could also consider the Split-and-Conquer mode (see below).

### Using the Split and Conquer (SNC) mode
In the SNC mode, activated by *--snc* Marabou decomposes the problem into *2^n0*
sub-problems, specified by *--initial-divides=n0*. Each sub-problem will be
solved with initial timeout of *t0*, supplied by *--initial-timeout=t0*. Every
sub-problem that times out will be divided into *2^n* additional sub-problems,
*--num-online-divides=n*, and the timeout is multiplied by a factor of *f*,
*--timeout-factor=f*. Number of parallel threads *t* is specified by
*--num-workers=t*.

So to solve a problem in SNC mode with 4 initial splits and initial timeout of 5s, 4 splits on each timeout and a timeout factor of 1.5:
```
build/Marabou resources/nnet/acasxu/ACASXU_experimental_v2a_2_7.nnet resources/properties/acas_property_3.txt --snc --initial-divides=4 --initial-timeout=5 --num-online-divides=4 --timeout-factor=1.5 --num-workers=4
```




People
-----------------------------------------------------------------------------
Authors and contributors to the Marabou project can be found in AUTHORS and THANKS files, respectively.
