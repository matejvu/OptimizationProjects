#include<iostream>
#include<cmath>

using namespace std;

const int N = 12;
//8 -> Primer pod a)
//12 -> primer pod b)

//L2 norma: sqrt(sum(|x_i|^2))



typedef int hole[2];


const hole h1 = { 27, 331 };
const hole h2 = { 27, 568 };
const hole h3 = { 91, 403 };
const hole h4 = { 91, 528 };
const hole h5 = { 151, 496 };
const hole h6 = { 153, 378 };
const hole h7 = { 215, 458 };
const hole h8 = { 229, 327 };
const hole h9 = { 334, 605 };
const hole h10 = { 284, 317 };
const hole h11 = { 347, 264 };
const hole h12 = { 457, 251 };
const hole h13 = { 347, 451 };
const hole h14 = { 460, 451 };
const hole h15 = { 542, 291 };
const hole h16 = { 577, 421 };
const hole h17 = { 679, 196 };
const hole h18 = { 517, 560 };
const hole h19 = { 575, 560 };
const hole h20 = { 620, 584 };

const hole* HOLES[20] = { &h1,  &h2, &h3,  &h4, &h5,  &h6, &h7,  &h8, &h9,  &h10,
							&h11,  &h12, &h13,  &h14, &h15,  &h16, &h17,  &h18, &h19,  &h20 };


typedef struct {
	const hole* tacke[N];
}putanja;


double f(int path[N], double dM[][N]) {
	
	
	double pathLength = 0;

	for (int i = 0; i < N-1; i++) {
		//pathLength += sqrt(pow( (*HOLES[path[i]-1])[0] - (*HOLES[path[i+1] - 1])[0], 2) + pow( (*HOLES[path[i] - 1])[1] - (*HOLES[path[i + 1] - 1])[1], 2));
		pathLength += dM[path[i]-1][path[i + 1]-1];
	}

	

	return pathLength;
}



int main() {

	//distance matrix
	double distanceMatrix[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			distanceMatrix[i][j] = (double)sqrt(pow(( (*HOLES[i])[0] - (*HOLES[j])[0] ), 2) + pow(( (*HOLES[i])[1] - (*HOLES[j])[1] ), 2));
		}
	}




	cout << "RUPE:\n";
	
	for (int i = 0; i < N; i++) {
		cout << "{ "<<(*HOLES[i])[0] << " " << (*HOLES[i])[1] << " }\n";
	}


	cout << "\n\nRESENJE:\n";

	int minLength = INT_MAX;
	int minPath[N];

	int P[N];
	for (int i = 1; i <= N; P[i - 1] = i, i++);


	while (1) {
		
		double pathLength = f(P, distanceMatrix);
		

		if (minLength > pathLength) {
			minLength = pathLength;
			for (int i = 0; i < N; i++) { minPath[i] = P[i]; }
		}

		//next Permutation
		

		int k = -1;
		for (int i = 0; i < N - 1; i++) {
			if (P[i] < P[i + 1])k = i;
		}
		

		if (k == -1)break;	//Opadajuce soritrana

		int l = k+1;

		for (int i = 0; i < N; i++) {
			if (P[i] > P[k])l = i;
		}

		int pom = P[k];
		P[k] = P[l];
		P[l] = pom;

		for (int i = 0; i < (N - 1 - k) / 2; i++) {
			int pom = P[k + 1 + i];
			P[k + 1 + i] = P[N - 1 - i];
			P[N - 1 - i] = pom;
		}
	
	}

	cout << "Min length: " << minLength << "\n";
	cout << "Path: "; for (int i = 0; i < N; i++) { cout << minPath[i] << " "; }

	


	return 0;
}
