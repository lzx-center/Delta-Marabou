/home/center/Delta-Marabou/cmake-build-debug/Marabou /home/center/Delta-Marabou/resources/nnet/test1.nnet /home/center/Delta-Marabou/resources/nnet/testp.txt
Network: /home/center/Delta-Marabou/resources/nnet/test1.nnet
Number of layers: 3. Input layer size: 2. Output layer size: 1. Number of ReLUs: 2
Total number of variables: 7
-1.00x_{2}+0.20x_{0}-0.70x_{1} = 0.10
-1.00x_{3}+0.80x_{0}-0.80x_{1} = -0.00
-1.00x_{6}+0.40x_{4}+0.60x_{5} = -0.00
Property: /home/center/Delta-Marabou/resources/nnet/testp.txt

Engine: processInputQuery starting

Engine::processInputQuery: Input query (before preprocessing): 3 equations, 7 variables
Engine::processInputQuery: Input query (after preprocessing): 5 equations, 9 variables

-1.00x_{2}+0.20x_{0}-0.70x_{1} = 0.10
-1.00x_{3}+0.80x_{0}-0.80x_{1} = -0.00
-1.00x_{6}+0.40x_{4}+0.60x_{5} = -0.00
+1.00x_{4}-1.00x_{2}-1.00x_{7} = 0.00
+1.00x_{5}-1.00x_{3}-1.00x_{8} = 0.00
Input bounds:
x0: [ -1.0000,   1.0000]
x1: [ -1.0000,   1.0000]

Engine: Skip simulation...
-1.00x_{2}+0.20x_{0}-0.70x_{1} = 0.10
-1.00x_{3}+0.80x_{0}-0.80x_{1} = -0.00
-1.00x_{6}+0.40x_{4}+0.60x_{5} = -0.00
+1.00x_{4}-1.00x_{2}-1.00x_{7} = 0.00
+1.00x_{5}-1.00x_{3}-1.00x_{8} = 0.00
Engine: Number of redundant rows: 0 out of 5
Branching heuristics set to LargestInterval
Engine: processInputQuery done

Tableau:
$$
\begin{aligned}
x_{2}&=0.200x_{0}-0.700x_{1}-1.000x_{9}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{7}&=-0.200x_{0}+0.700x_{1}+1.000x_{4}+1.000x_{9}-1.000x_{12}\\
x_{6}&=0.400x_{4}+0.600x_{5}-1.000x_{11}\\
x_{8}&=-0.800x_{0}+0.800x_{1}+1.000x_{5}+1.000x_{10}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|-1.600|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|-0.000|0.000|0.000|**-0.000**|**-0.400**|-0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.800|1.600|0.800|1.600|1.280|1.000|1.600|0.100|-0.000|-0.000|0.000|0.000|


Engine::solve: Initial statistics

09:44:11 Statistics update:
--- Time Statistics ---
Total time elapsed: 0 milli (00:00:00)
Main loop: 0 milli (00:00:00)
Preprocessing time: 0 milli (00:00:00)
Unknown: 0 milli (00:00:00)
Breakdown for main loop:
[0.00%] Simplex steps: 0 milli
[0.00%] Explicit-basis bound tightening: 0 milli
[0.00%] Constraint-matrix bound tightening: 0 milli
[0.00%] Degradation checking: 0 milli
[0.00%] Precision restoration: 0 milli
[0.00%] Statistics handling: 0 milli
[0.00%] Constraint-fixing steps: 0 milli
[0.00%] Valid case splits: 0 milli. Average per split: 0.00 milli
[0.00%] Applying stored bound-tightening: 0 milli
[0.00%] SMT core: 0 milli
[0.00%] Symbolic Bound Tightening: 0 milli
[0.00%] SoI-based local search: 0 milli
[0.00%] SoI-based local search: 0 milli
[0.00%] Unaccounted for: 0 milli
--- Preprocessor Statistics ---
Number of preprocessor bound-tightening loop iterations: 3
Number of eliminated variables: 0
Number of constraints removed due to variable elimination: 0
Number of equations removed due to variable elimination: 0
--- Engine Statistics ---
Number of main loop iterations: 1
0 iterations were simplex steps. Total time: 0 milli. Average: 0.00 milli.
0 iterations were constraint-fixing steps. Total time: 0 milli. Average: 0.00 milli
Number of active piecewise-linear constraints: 2 / 2
Constraints disabled by valid splits: 0. By SMT-originated splits: 0
Last reported degradation: 0.0000000000. Max degradation so far: 0.0000000000. Restorations so far: 0
Number of simplex pivots we attempted to skip because of instability: 0.
Unstable pivots performed anyway: 0
--- Tableau Statistics ---
Total number of pivots performed: 0
Real pivots: 0. Degenerate: 0 (0.00%)
Degenerate pivots by request (e.g., to fix a PL constraint): 0 (0.00%)
Average time per pivot: 0.00 milli
Total number of fake pivots performed: 0
Total number of rows added: 0. Number of merged columns: 0
Current tableau dimensions: M = 5, N = 14
--- SMT Core Statistics ---
Total depth is 0. Total visited states: 1. Number of splits: 0. Number of pops: 0
Max stack depth: 0
--- Bound Tightening Statistics ---
Number of tightened bounds: 0.
Number of rows examined by row tightener: 0. Consequent tightenings: 0
Number of explicit basis matrices examined by row tightener: 0. Consequent tightenings: 0
Number of bound tightening rounds on the entire constraint matrix: 0. Consequent tightenings: 0
Number of bound notifications sent to PL constraints: 12. Tightenings proposed: 0
--- Basis Factorization statistics ---
Number of basis refactorizations: 2
--- Projected Steepest Edge Statistics ---
Number of iterations: 0.
Number of resets to reference space: 1. Avg. iterations per reset: 0
--- SBT ---
Number of tightened bounds: 0
--- SoI-based local search ---
Number of proposed phase pattern update: 0. Number of accepted update: 0 [0.00%]
Total time (% of local search time) updating SoI phase pattern : 0 milli [0.00%]
Total time obtaining current assignment: 0 milli [0.00%]
Total time getting SoI phase pattern : 0 milli [0.00%]

---
initial tableau
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|-1.600|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|-0.000|0.000|0.000|**-0.000**|**-0.400**|-0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.800|1.600|0.800|1.600|1.280|1.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

after split
Tableau:
$$
\begin{aligned}
x_{2}&=0.200x_{0}-0.700x_{1}-1.000x_{9}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{7}&=-0.200x_{0}+0.700x_{1}+1.000x_{4}+1.000x_{9}-1.000x_{12}\\
x_{6}&=0.400x_{4}+0.600x_{5}-1.000x_{11}\\
x_{8}&=-0.800x_{0}+0.800x_{1}+1.000x_{5}+1.000x_{10}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|-1.600|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|-0.000|0.000|0.000|**-0.000**|**-0.400**|-0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.800|1.600|0.800|1.600|1.280|1.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Tableau: Tableau performing pivot. Entering: 4, Leaving: 7
Tableau: Leaving variable increases. Current value: -0.400000000000000. Range: [0.000000000000000, 1.000000000000000]
Tableau: Entering variable increases. Current value: 0.000000000000000. Range: [0.000000000000000, 0.800000000000000]
Tableau: Change ratio is: 0.400000000000000

Tableau:
$$
\begin{aligned}
x_{2}&=0.200x_{0}-0.700x_{1}-1.000x_{9}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{4}&=0.200x_{0}-0.700x_{1}+1.000x_{7}-1.000x_{9}+1.000x_{12}\\
x_{6}&=0.080x_{0}-0.280x_{1}+0.400x_{7}+0.600x_{5}-0.400x_{9}-1.000x_{11}+0.400x_{12}\\
x_{8}&=-0.800x_{0}+0.800x_{1}+1.000x_{5}+1.000x_{10}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|-1.600|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|0.000|0.400|0.000|**0.160**|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.800|1.600|0.800|1.600|1.280|1.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Tableau: Tableau performing pivot. Entering: 5, Leaving: 6
Tableau: Leaving variable increases. Current value: 0.160000000000000. Range: [0.300000000000000, 1.280000000000000]
Tableau: Entering variable increases. Current value: 0.000000000000000. Range: [0.000000000000000, 1.600000000000000]
Tableau: Change ratio is: 0.233333333333333

Tableau:
$$
\begin{aligned}
x_{2}&=0.200x_{0}-0.700x_{1}-1.000x_{9}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{4}&=0.200x_{0}-0.700x_{1}+1.000x_{7}-1.000x_{9}+1.000x_{12}\\
x_{5}&=-0.133x_{0}+0.467x_{1}-0.667x_{7}+1.667x_{6}+0.667x_{9}+1.667x_{11}-0.667x_{12}\\
x_{8}&=-0.933x_{0}+1.267x_{1}-0.667x_{7}+1.667x_{6}+0.667x_{9}+1.000x_{10}+1.667x_{11}-0.667x_{12}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|-1.600|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|0.000|0.400|0.233|0.300|0.000|0.233|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.800|1.600|0.800|1.600|1.280|1.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Engine: Linear constraints satisfied. Now trying to satisfy non-linear constraints...
set entering var: x6
set leaving var: x5
Tableau:
$$
\begin{aligned}
x_{2}&=0.200x_{0}-0.700x_{1}-1.000x_{9}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{4}&=0.200x_{0}-0.700x_{1}+1.000x_{7}-1.000x_{9}+1.000x_{12}\\
x_{6}&=0.080x_{0}-0.280x_{1}+0.400x_{7}+0.600x_{5}-0.400x_{9}-1.000x_{11}+0.400x_{12}\\
x_{8}&=-0.800x_{0}+0.800x_{1}+1.000x_{5}+1.000x_{10}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|-1.600|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|0.000|0.400|0.000|**0.160**|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.800|1.600|0.800|1.600|1.280|1.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Engine:
Engine: Applying a split.
Engine: x3: upper bound set to 0.000
Engine: x5: upper bound set to 0.000
Engine: Done with split

Tableau:
$$
\begin{aligned}
x_{2}&=0.200x_{0}-0.700x_{1}-1.000x_{9}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{4}&=0.200x_{0}-0.700x_{1}+1.000x_{7}-1.000x_{9}+1.000x_{12}\\
x_{6}&=0.080x_{0}-0.280x_{1}+0.400x_{7}+0.600x_{5}-0.400x_{9}-1.000x_{11}+0.400x_{12}\\
x_{8}&=-0.800x_{0}+0.800x_{1}+1.000x_{5}+1.000x_{10}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|-1.600|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|0.000|0.400|0.000|**0.160**|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.800|0.000|0.800|0.000|1.280|1.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Tableau: Tableau performing pivot. Entering: 7, Leaving: 6
Tableau: Leaving variable increases. Current value: 0.160000000000000. Range: [0.300000000000000, 0.320000000000000]
Tableau: Entering variable increases. Current value: 0.000000000000000. Range: [0.000000000000000, 1.000000000000000]
Tableau: Change ratio is: 0.350000000000000

Tableau:
$$
\begin{aligned}
x_{2}&=0.200x_{0}-0.700x_{1}-1.000x_{9}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=-0.200x_{0}+0.700x_{1}+2.500x_{6}-1.500x_{5}+1.000x_{9}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-0.800x_{0}+0.800x_{1}+1.000x_{5}+1.000x_{10}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|-1.600|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|0.000|0.750|0.000|0.300|0.350|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|0.500|0.800|0.000|0.800|0.000|0.320|1.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Engine: Linear constraints satisfied. Now trying to satisfy non-linear constraints...
set entering var: x9
set leaving var: x2
Tableau:
$$
\begin{aligned}
x_{9}&=0.200x_{0}-0.700x_{1}-1.000x_{2}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=2.500x_{6}-1.500x_{5}-1.000x_{2}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-0.800x_{0}+0.800x_{1}+1.000x_{5}+1.000x_{10}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|-1.600|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.750|0.000|0.750|0.000|0.300|-0.000|0.000|**-0.250**|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|0.500|0.800|0.000|0.800|0.000|0.320|1.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Engine:
Engine: Applying a split.
Engine: x2: upper bound set to 0.000
Engine: x4: upper bound set to 0.000
Engine: Done with split

Tableau:
$$
\begin{aligned}
x_{9}&=0.200x_{0}-0.700x_{1}-1.000x_{2}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=2.500x_{6}-1.500x_{5}-1.000x_{2}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-0.800x_{0}+0.800x_{1}+1.000x_{5}+1.000x_{10}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|-1.600|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.000|0.000|**0.750**|0.000|0.300|0.750|0.000|**0.500**|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|0.500|0.000|0.000|0.000|0.000|0.320|1.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Judge unsat!
Tableau:
$$
\begin{aligned}
x_{9}&=0.200x_{0}-0.700x_{1}-1.000x_{2}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=2.500x_{6}-1.500x_{5}-1.000x_{2}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-0.800x_{0}+0.800x_{1}+1.000x_{5}+1.000x_{10}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-0.650|-1.200|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.000|0.000|0.000|0.000|0.000|0.000|0.000|**0.500**|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|0.500|0.000|0.000|0.000|0.000|0.000|1.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Engine: Restore state starting
Engine: 	Restoring tableau state
Engine: 	Restoring constraint states
Engine:
Engine: Applying a split.
Engine: x2: lower bound set to 0.000
Engine: x7: upper bound set to 0.000
Engine: Done with split

Tableau:
$$
\begin{aligned}
x_{9}&=0.200x_{0}-0.700x_{1}-1.000x_{2}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=2.500x_{6}-1.500x_{5}-1.000x_{2}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-0.800x_{0}+0.800x_{1}+1.000x_{5}+1.000x_{10}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|0.000|-1.600|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.000|0.000|0.750|0.000|0.300|**0.750**|0.000|**0.500**|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|0.500|0.800|0.000|0.800|0.000|0.320|0.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Tableau: Tableau performing pivot. Entering: 2, Leaving: 9
Tableau: Leaving variable decreases. Current value: 0.500000000000000. Range: [0.100000000000000, 0.100000000000000]
Tableau: Entering variable increases. Current value: 0.000000000000000. Range: [0.000000000000000, 0.800000000000000]
Tableau: Change ratio is: 0.400000000000000

Tableau:
$$
\begin{aligned}
x_{2}&=0.200x_{0}-0.700x_{1}-1.000x_{9}\\
x_{3}&=0.800x_{0}-0.800x_{1}-1.000x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=-0.200x_{0}+0.700x_{1}+2.500x_{6}-1.500x_{5}+1.000x_{9}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-0.800x_{0}+0.800x_{1}+1.000x_{5}+1.000x_{10}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|0.000|-1.200|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|0.000|0.750|0.000|0.300|**0.350**|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|0.143|0.800|0.000|0.800|0.000|0.320|0.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Tableau: Tableau performing pivot. Entering: 0, Leaving: 3
Tableau: Leaving variable increases. Current value: 0.000000000000000. Range: [-0.914285714285714, 0.000000000000000]
Tableau: Entering variable increases. Current value: -1.000000000000000. Range: [-1.000000000000000, 0.142857142857143]
Tableau: Change ratio is: 0.000000000000000

Tableau:
$$
\begin{aligned}
x_{2}&=0.250x_{3}-0.500x_{1}-1.000x_{9}+0.250x_{10}\\
x_{0}&=1.250x_{3}+1.000x_{1}+1.250x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=-0.250x_{3}+0.500x_{1}+2.500x_{6}-1.500x_{5}+1.000x_{9}-0.250x_{10}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-1.000x_{3}+1.000x_{5}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|0.000|-0.914|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|0.000|0.750|0.000|0.300|**0.350**|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|0.143|0.143|0.800|0.000|0.800|0.000|0.320|0.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Tableau:
$$
\begin{aligned}
x_{2}&=0.250x_{3}-0.500x_{1}-1.000x_{9}+0.250x_{10}\\
x_{0}&=1.250x_{3}+1.000x_{1}+1.250x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=-0.250x_{3}+0.500x_{1}+2.500x_{6}-1.500x_{5}+1.000x_{9}-0.250x_{10}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-1.000x_{3}+1.000x_{5}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|0.000|-0.914|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|0.000|0.750|0.000|0.300|**0.350**|-0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|0.143|0.143|0.800|0.000|0.800|0.000|0.320|0.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Tableau:
$$
\begin{aligned}
x_{2}&=0.250x_{3}-0.500x_{1}-1.000x_{9}+0.250x_{10}\\
x_{0}&=1.250x_{3}+1.000x_{1}+1.250x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=-0.250x_{3}+0.500x_{1}+2.500x_{6}-1.500x_{5}+1.000x_{9}-0.250x_{10}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-1.000x_{3}+1.000x_{5}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|0.000|-0.914|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|0.000|0.750|0.000|0.300|**0.350**|-0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|0.143|0.143|0.800|0.000|0.800|0.000|0.320|0.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Judge unsat!
Tableau:
$$
\begin{aligned}
x_{2}&=0.250x_{3}-0.500x_{1}-1.000x_{9}+0.250x_{10}\\
x_{0}&=1.250x_{3}+1.000x_{1}+1.250x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=-0.250x_{3}+0.500x_{1}+2.500x_{6}-1.500x_{5}+1.000x_{9}-0.250x_{10}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-1.000x_{3}+1.000x_{5}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|0.000|-0.914|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|0.000|0.750|0.000|0.300|**0.350**|-0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|0.143|0.143|0.800|0.000|0.800|0.000|0.320|0.000|1.600|0.100|-0.000|-0.000|0.000|0.000|

Engine: Restore state starting
Engine: 	Restoring tableau state
Engine: 	Restoring constraint states
Engine:
Engine: Applying a split.
Engine: x3: lower bound set to 0.000
Engine: x8: upper bound set to 0.000
Engine: Done with split

Tableau:
$$
\begin{aligned}
x_{2}&=0.250x_{3}-0.500x_{1}-1.000x_{9}+0.250x_{10}\\
x_{0}&=1.250x_{3}+1.000x_{1}+1.250x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=-0.250x_{3}+0.500x_{1}+2.500x_{6}-1.500x_{5}+1.000x_{9}-0.250x_{10}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-1.000x_{3}+1.000x_{5}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|0.000|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.400|0.000|0.750|0.000|0.300|0.350|-0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.800|1.600|0.800|1.600|1.280|1.000|0.000|0.100|-0.000|-0.000|0.000|0.000|

Engine: Linear constraints satisfied. Now trying to satisfy non-linear constraints...
set entering var: x9
set leaving var: x2
Tableau:
$$
\begin{aligned}
x_{9}&=0.250x_{3}-0.500x_{1}-1.000x_{2}+0.250x_{10}\\
x_{0}&=1.250x_{3}+1.000x_{1}+1.250x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=2.500x_{6}-1.500x_{5}-1.000x_{2}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-1.000x_{3}+1.000x_{5}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|0.000|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.750|0.000|0.750|0.000|0.300|0.000|0.000|**-0.250**|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.800|1.600|0.800|1.600|1.280|1.000|0.000|0.100|-0.000|-0.000|0.000|0.000|

Engine:
Engine: Applying a split.
Engine: x2: upper bound set to 0.000
Engine: x4: upper bound set to 0.000
Engine: Done with split

Tableau:
$$
\begin{aligned}
x_{9}&=0.250x_{3}-0.500x_{1}-1.000x_{2}+0.250x_{10}\\
x_{0}&=1.250x_{3}+1.000x_{1}+1.250x_{10}\\
x_{4}&=2.500x_{6}-1.500x_{5}+2.500x_{11}\\
x_{7}&=2.500x_{6}-1.500x_{5}-1.000x_{2}+2.500x_{11}-1.000x_{12}\\
x_{8}&=-1.000x_{3}+1.000x_{5}-1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|0.000|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.000|0.000|**0.750**|0.000|0.300|0.750|0.000|**0.500**|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.000|1.600|0.000|1.600|1.280|1.000|0.000|0.100|-0.000|-0.000|0.000|0.000|

Tableau: Tableau performing pivot. Entering: 5, Leaving: 8
Tableau: Leaving variable increases. Current value: 0.000000000000000. Range: [0.000000000000000, 0.000000000000000]
Tableau: Entering variable increases. Current value: 0.000000000000000. Range: [0.000000000000000, 1.600000000000000]
Tableau: Change ratio is: 0.000000000000000

Tableau:
$$
\begin{aligned}
x_{9}&=0.250x_{3}-0.500x_{1}-1.000x_{2}+0.250x_{10}\\
x_{0}&=1.250x_{3}+1.000x_{1}+1.250x_{10}\\
x_{4}&=-1.500x_{3}+2.500x_{6}-1.500x_{8}+2.500x_{11}-1.500x_{13}\\
x_{7}&=-1.500x_{3}+2.500x_{6}-1.500x_{8}-1.000x_{2}+2.500x_{11}-1.000x_{12}-1.500x_{13}\\
x_{5}&=1.000x_{3}+1.000x_{8}+1.000x_{13}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|0.000|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-1.000|-1.000|0.000|0.000|**0.750**|0.000|0.300|0.750|0.000|**0.500**|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.000|1.600|0.000|1.600|0.960|1.000|0.000|0.100|-0.000|-0.000|0.000|0.000|

Tableau: Tableau performing pivot. Entering: 3, Leaving: 4
Tableau: Leaving variable decreases. Current value: 0.000000000000000. Range: [0.000000000000000, 0.000000000000000]
Tableau: Entering variable increases. Current value: 0.500000000000000. Range: [0.500000000000000, 1.600000000000000]
Tableau: Change ratio is: 0.500000000000000

Tableau:
$$
\begin{aligned}
x_{9}&=-0.167x_{4}-0.500x_{1}+0.417x_{6}-0.250x_{8}-1.000x_{2}+0.250x_{10}+0.417x_{11}-0.250x_{13}\\
x_{0}&=-0.833x_{4}+1.000x_{1}+2.083x_{6}-1.250x_{8}+1.250x_{10}+2.083x_{11}-1.250x_{13}\\
x_{3}&=-0.667x_{4}+1.667x_{6}-1.000x_{8}+1.667x_{11}-1.000x_{13}\\
x_{7}&=1.000x_{4}-1.000x_{2}-1.000x_{12}\\
x_{5}&=-0.667x_{4}+1.667x_{6}+1.667x_{11}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|-1.000|-1.000|0.500|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|-0.375|-1.000|0.000|0.500|0.000|0.500|0.300|0.000|0.000|**0.625**|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.000|1.600|0.000|1.600|0.960|1.000|0.000|0.100|-0.000|-0.000|0.000|0.000|

Tableau: Tableau performing pivot. Entering: 1, Leaving: 9
Tableau: Leaving variable decreases. Current value: 0.100000000000000. Range: [0.100000000000000, 0.100000000000000]
Tableau: Entering variable increases. Current value: 0.050000000000000. Range: [0.050000000000000, 1.000000000000000]
Tableau: Change ratio is: 1.050000000000000

Tableau:
$$
\begin{aligned}
x_{1}&=-0.333x_{4}-2.000x_{9}+0.833x_{6}-0.500x_{8}-2.000x_{2}+0.500x_{10}+0.833x_{11}-0.500x_{13}\\
x_{0}&=-1.167x_{4}-2.000x_{9}+2.917x_{6}-1.750x_{8}-2.000x_{2}+1.750x_{10}+2.917x_{11}-1.750x_{13}\\
x_{3}&=-0.667x_{4}+1.667x_{6}-1.000x_{8}+1.667x_{11}-1.000x_{13}\\
x_{7}&=1.000x_{4}-1.000x_{2}-1.000x_{12}\\
x_{5}&=-0.667x_{4}+1.667x_{6}+1.667x_{11}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|0.050|-0.475|0.500|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|0.675|0.050|0.000|0.500|0.000|0.500|0.300|-0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.000|1.600|0.000|1.600|0.960|1.000|0.000|0.100|-0.000|-0.000|0.000|0.000|

Engine: Linear constraints satisfied. Now trying to satisfy non-linear constraints...
Before declaring sat, recomputing...
Tableau:
$$
\begin{aligned}
x_{1}&=-0.333x_{4}-2.000x_{9}+0.833x_{6}-0.500x_{8}-2.000x_{2}+0.500x_{10}+0.833x_{11}-0.500x_{13}\\
x_{0}&=-1.167x_{4}-2.000x_{9}+2.917x_{6}-1.750x_{8}-2.000x_{2}+1.750x_{10}+2.917x_{11}-1.750x_{13}\\
x_{3}&=-0.667x_{4}+1.667x_{6}-1.000x_{8}+1.667x_{11}-1.000x_{13}\\
x_{7}&=1.000x_{4}-1.000x_{2}-1.000x_{12}\\
x_{5}&=-0.667x_{4}+1.667x_{6}+1.667x_{11}\\
\end{aligned}
$$
Assignment
|variable|$0}$$|$1}$$|$2}$$|$3}$$|$4}$$|$5}$$|$6}$$|$7}$$|$8}$$|$9}$$|$10}$$|$11}$$|$12}$$|$13}$$|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|Lower bound|-1.000|0.050|-0.475|0.500|0.000|0.000|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Assignment|0.675|0.050|0.000|0.500|0.000|0.500|0.300|0.000|0.000|0.100|-0.000|-0.000|0.000|0.000|
|Upper bound|1.000|1.000|0.000|1.600|0.000|1.600|0.960|1.000|0.000|0.100|-0.000|-0.000|0.000|0.000|

Engine: Linear constraints satisfied. Now trying to satisfy non-linear constraints...

Engine::solve: sat assignment found

09:44:11 Statistics update:
--- Time Statistics ---
Total time elapsed: 4 milli (00:00:00)
Main loop: 3 milli (00:00:00)
Preprocessing time: 0 milli (00:00:00)
Unknown: 0 milli (00:00:00)
Breakdown for main loop:
[63.82%] Simplex steps: 2 milli
[0.08%] Explicit-basis bound tightening: 0 milli
[0.00%] Constraint-matrix bound tightening: 0 milli
[0.00%] Degradation checking: 0 milli
[0.00%] Precision restoration: 0 milli
[0.00%] Statistics handling: 0 milli
[0.47%] Constraint-fixing steps: 0 milli
[0.00%] Valid case splits: 0 milli. Average per split: 0.00 milli
[0.06%] Applying stored bound-tightening: 0 milli
[2.32%] SMT core: 0 milli
[4.47%] Symbolic Bound Tightening: 0 milli
[0.00%] SoI-based local search: 0 milli
[0.00%] SoI-based local search: 0 milli
[28.79%] Unaccounted for: 1 milli
--- Preprocessor Statistics ---
Number of preprocessor bound-tightening loop iterations: 3
Number of eliminated variables: 0
Number of constraints removed due to variable elimination: 0
Number of equations removed due to variable elimination: 0
--- Engine Statistics ---
Number of main loop iterations: 21
11 iterations were simplex steps. Total time: 2 milli. Average: 0.18 milli.
3 iterations were constraint-fixing steps. Total time: 0 milli. Average: 0.00 milli
Number of active piecewise-linear constraints: 0 / 2
Constraints disabled by valid splits: 0. By SMT-originated splits: 2
Last reported degradation: 0.0000000000. Max degradation so far: 0.0000000000. Restorations so far: 0
Number of simplex pivots we attempted to skip because of instability: 0.
Unstable pivots performed anyway: 0
--- Tableau Statistics ---
Total number of pivots performed: 11
Real pivots: 6. Degenerate: 5 (45.45%)
Degenerate pivots by request (e.g., to fix a PL constraint): 3 (60.00%)
Average time per pivot: 0.18 milli
Total number of fake pivots performed: 0
Total number of rows added: 0. Number of merged columns: 0
Current tableau dimensions: M = 5, N = 14
--- SMT Core Statistics ---
Total depth is 2. Total visited states: 6. Number of splits: 3. Number of pops: 2
Max stack depth: 2
--- Bound Tightening Statistics ---
Number of tightened bounds: 16.
Number of rows examined by row tightener: 8. Consequent tightenings: 8
Number of explicit basis matrices examined by row tightener: 1. Consequent tightenings: 1
Number of bound tightening rounds on the entire constraint matrix: 0. Consequent tightenings: 0
Number of bound notifications sent to PL constraints: 25. Tightenings proposed: 0
--- Basis Factorization statistics ---
Number of basis refactorizations: 2
--- Projected Steepest Edge Statistics ---
Number of iterations: 8.
Number of resets to reference space: 3. Avg. iterations per reset: 2
--- SBT ---
Number of tightened bounds: 6
--- SoI-based local search ---
Number of proposed phase pattern update: 0. Number of accepted update: 0 [0.00%]
Total time (% of local search time) updating SoI phase pattern : 0 milli [0.00%]
Total time obtaining current assignment: 0 milli [0.00%]
Total time getting SoI phase pattern : 0 milli [0.00%]
Search Tree size: 6
sat
Input assignment:
x0 = 0.675000
x1 = 0.050000

Output:
y0 = 0.300000

Summary path /home/center/Delta-Marabou/resources/nnet/test1.nnet.summary

进程已结束,退出代码0
