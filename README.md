#  Marabou [![Marabou](https://github.com/NeuralNetworkVerification/Marabou/actions/workflows/ci.yml/badge.svg)](https://github.com/NeuralNetworkVerification/Marabou/actions/workflows/ci.yml) [![codecov.io](https://codecov.io/github/NeuralNetworkVerification/Marabou/coverage.svg?branch=master)](https://codecov.io/github/NeuralNetworkVerification/Marabou?branch=master)
Deep neural networks are revolutionizing the way complex systems are designed.
Instead of spending long hours hand-crafting complex software, many engineers
now opt to use deep neural networks (DNNs) - machine learning models, created by
training algorithms that generalize from a finite set of examples to previously
unseen inputs. Consequently, there is a pressing need for tools and techniques
for network analysis and certification. To help address that need, we present
Marabou, a framework for verifying deep neural networks. 

Marabou is an SMT-based tool that can answer queries about a network’s
properties by transforming these queries into constraint satisfaction problems.
It can accommodate networks with different activation functions and topologies,
and it performs high-level reasoning on the network that can curtail the search
space and improve performance. It also supports parallel execution to further
enhance scalability. Marabou accepts multiple input formats, including protocol
buffer files generated by the popular TensorFlow framework for neural networks.

A DNN verification query consists of two parts: (i) a neural network, and (ii) a
property to be checked; and its result is either a formal guarantee that the
network satisfies the property, or a concrete input for which the property is
violated (a counter-example). There are several types of verification queries
that Marabou can answer: 
* Reachability queries: if inputs is in a given range is the output
guaranteed to be in some, typically safe, range.
* Robustness queries: test whether there exist adversarial points around a given
  input point that change the output of the network.

Marabou supports fully connected feed-forward and convolutional NNs with
piece-wise linear activation functions, in the .nnet and TensorFlow formats.
Properties can be specified using inequalites over input and output variables or
via Python interface. 

For more details about the features of Marabou check out the [tool
paper](https://aisafety.stanford.edu/marabou/MarabouCAV2019.pdf)
([slides](https://aisafety.stanford.edu/marabou/fomlas19.html)) and our [**recent work**](https://arxiv.org/abs/2203.11201)
based on Sum-of-Infeasibilities, which is now the default solving mode of Marabou. 

For more information about the input formats please check the
[wiki](https://github.com/NeuralNetworkVerification/Marabou/wiki/Marabou-Input-Formats).

A guide to Split and Conquer mode is available in [resources/SplitAndConquerGuide.ipynb](resources/SplitAndConquerGuide.ipynb). The Jupyter Notebook gives on overview of SnC's parameters, discusses several runtime examples and a few rules of thumb to choose parameter values.



Build and Dependencies
------------------------------------------------------------------------------

Marabou depends on the Boost library,
which is automatically downloaded and built when you run make. Library CXXTEST
comes included in the repository.

The marabou build process uses CMake version 3.12 (or later).
You can get CMake [here](https://cmake.org/download/).

Marabou can be built for Linux, MacOS, or Windows machines.

### Build Instructions for Linux or MacOS

To build marabou using CMake run:
```
cd path/to/marabou/repo/folder
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

To run tests we use [ctest](https://cmake.org/cmake/help/v3.15/manual/ctest.1.html).
The tests have labels according to level (unit/system/regress0/regress1...), and the code they are testing (engine/common etc...).  
For example to run all unit tests execute in the build directory:
```
ctest -L unit
```
On every build we run the unit tests, and on every pull request we run unit,
system, regress0 and regress1.

Another option to build and run all of the tests is: 
```
cd path/to/marabou/repo/folder
mkdir build 
cd build
cmake ..
make check -j PROC_NUM
```


Getting Started
-----------------------------------------------------------------------------
### To run Marabou from Command line 
After building Marabou the binary is located at *build/Marabou* (or *build\Release\Marabou.exe* for Windows). The
repository contains sample networks and properties in the *resources* folder.
For more information see [resources/README.md](resources/README.md).

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

A guide to Split and Conquer is available as a Jupyter Notebook in [resources/SplitAndConquerGuide.ipynb](resources/SplitAndConquerGuide.ipynb).

### Use LP Relaxation
Marabou has an option to use LP relaxation for bound tightening.
For now we use Gurobi as an LP solver. Gurobi requires a license (a free
academic license is available), after getting one the software can be downloaded
[here](https://www.gurobi.com/downloads/gurobi-optimizer-eula/) and [here](https://www.gurobi.com/documentation/9.5/quickstart_linux/software_installation_guid.html#section:Installation) are
installation steps, there is a [compatibility
issue](https://support.gurobi.com/hc/en-us/articles/360039093112-C-compilation-on-Linux) that should be addressed.
A quick installation reference:
```
export INSTALL_DIR=/opt
sudo tar xvfz gurobi9.5.1_linux64.tar.gz -C $INSTALL_DIR
cd $INSTALL_DIR/gurobi951/linux64/src/build
sudo make
sudo cp libgurobi_c++.a ../../lib/
```
Next it is recommended to add the following to the .bashrc (but not necessary) 
```
export GUROBI_HOME="/opt/gurobi951/linux64"
export PATH="${PATH}:${GUROBI_HOME}/bin"
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${GUROBI_HOME}/lib"

```

After installing Gurobi compile marabou as follows:
```
cmake .. -DENABLE_GUROBI=ON
cmake --build . 
```
If you did not set the GUROBI_HOME environment variable, then use the following:
```
cmake .. -DENABLE_GUROBI=ON -DGUROBI_DIR=<PATH_TO_GUROBI>
```

### Tests
We have three types of tests:  
* unit tests - test specific small components, the tests are located alongside the code in a _tests_ folder (for example: _src/engine/tests_), to add a new set of tests, add a file named *Test_FILENAME* (where *FILENAME* is what you want to test), and add it to the CMakeLists.txt file (for example src/engine/CMakeLists.txt)
* system tests - test an end to end use case but still have access to internal functionality. Those tests are located in _src/system_tests_. To add new set of tests create a file named *Test_FILENAME*, and add it also to _src/system_tests/CMakeLists.txt_.
* regression tests - test end to end functionality thorugh the API, each test is defined by:  
  * network_file - description of the "neural network" supporting nnet and mps formats (using the extension to decdie on the format)  
  * property_file - optional, constraint on the input and output variables  
  * expected_result - sat/unsat  

The tests are divided into 5 levels to allow variability in running time, to add a new regression tests: 
  * add the description of the network and property to the _resources_ sub-folder 
  * add the test to: _regress/regressLEVEL/CMakeLists.txt_ (where LEVEL is within 0-5) 
In each build we run unit_tests and system_tests, on pull request we run regression 0 & 1, in the future we will run other levels of regression weekly / monthly. 

Acknowledgments
-----------------------------------------------------------------------------

The Marabou project is partially supported by grants from the Binational Science
Foundation (2017662), the Defense Advanced Research Projects Agency
(FA8750-18-C-0099), the Semiconductor Research Corporation (2019-AU-2898), the
Federal Aviation Administration, Ford Motor Company, Intel Corporation, the
Israel Science Foundation (683/18), the National Science Foundation (1814369,
DGE-1656518), Siemens Corporation, General Electric, and the Stanford CURIS program.


Marabou is used in a number of flagship projects at [Stanford's AISafety
center](http://aisafety.stanford.edu).



People
-----------------------------------------------------------------------------
Authors and contributors to the Marabou project can be found in AUTHORS and THANKS files, respectively.
