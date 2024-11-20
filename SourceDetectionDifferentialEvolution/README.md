Description: <br> &emsp; In the Cartesian coordinate system with 24 recievers placed as a square fence around two unknown sources. By using the measured data from each reciever and Differential Evolution the locations and signal constants of both sources were found. Signal of each source is aproximated as $S=\frac{A}{r}$ where $A$ is the constant and $r$ is the distance. Optimization function used in this problem is:<br>
$f_{\text{opt}}(\mathbf{x}) = \sum_{i=0}^{N-1} \left( 
\frac{A_1}{\sqrt{(x_i - x_R)^2 + (y_i - y_R)^2}} +
\frac{A_2}{\sqrt{(x_i - x_{P_2})^2 + (y_i - y_{P_2})^2}} - S_i
\right)^2$
<br>Accuracy: <br> &emsp;Convergence requirement for optimization function is $f\leq 10^{-14}$.
<br>Results: <br> &emsp;Positions of two sources: 
<br> &emsp; &emsp; (-8.500000105349315, 5.000000137059198),
<br> &emsp; &emsp; (6.5000002314768315, -6.499999901876407).
<br> &emsp; Source constants: -2.9999999534993194, 0.9999999689759355.
<br> &emsp; Value of function: $f = 7.676160886432267 \cdot 10^{-17}$.
