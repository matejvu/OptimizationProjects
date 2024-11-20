Description: <br> &emsp; Implementation of Reannealing i.e. repeated interactions of simulated annealing is used to detemrmine the optimal way to pack files into 2 large directories. The hamming distance was used as a metric since this problem classifies as SAT. Program consist of 20 independent annealing optimizations whith each annealing including 10 iterations of "reheating".
<br> &emsp; Used parameters:
<br> &emsp; $a = 0.9646$
<br> &emsp; $h_max = 5$
<br> &emsp; $h_min = 2$
<br>Directions:
<br> &emsp; When running the main.cpp code, 20 data.txt files and a minimumValue file are generated.
The data files are used by SimulatedAnnealing.py to plot graphs.
The minimumValue file contains the smallest solution obtained from all 20 runs of simulated annealing.
The images grafik1 and grafik2 are examples of the resulting graphs.

Accuracy: <br> &emsp; There was no specific convergence criterium.
Results: <br> &emsp;Can be found in the minimumValue file,


