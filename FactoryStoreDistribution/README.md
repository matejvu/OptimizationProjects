Description: <br> &emsp; Optimized the problem of distribution of products between 5 factories and 4 stores with different delivery prices and demands. 
The method of optimization iz linprog function from scipy library.
<br>Accuracy: <br> &emsp;Solution is the number of products which is integer so there is no rounding.
<br>Results: <br> &emsp;Represented as matrix(factories x stores) 
<br> &emsp;&emsp;  250	250	0	0
<br> &emsp;&emsp;  0	50	200	50
<br> &emsp;&emsp;  0	200	0	0
<br> &emsp;&emsp;  0	0	0	250
<br> &emsp;&emsp;  750	0	0	0
<br> &emsp; Cost of delivery: 3875.0
