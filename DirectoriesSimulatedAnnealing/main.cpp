#include<fstream>
#include<cmath>
#include<iostream>
#include<stdlib.h>
#include <stdio.h>


using namespace std;

int random_int(int a, int b) {
	int res;
	res = a + rand() % (b + 1 - a);
	return res;
}

void random_combination(int n, int k, int* P)
{
	if (k > n) return;

	int i, j, r, c;
	int* Q = new int[n];

	for (i = 0; i < n; i++)
		Q[i] = 0;

	for (i = 0; i < k; i++)
	{
		r = random_int(0, n - 1 - i);
		c = 0;
		for (j = 0; j < n; j++)
		{
			if (Q[j] == 0)
			{
				if (r == c)
				{
					Q[j]++;
					break;
				}
				c++;
			}
		}
	}

	c = 0;
	for (i = 0; i < n; i++)
	{

		if (Q[i] == 1)
		{
			P[c] = i + 1;
			c++;

		}
	}
	delete[] Q;
}



int rand_val() {
	return rand() % 3;
}


int hamming_distance(int i,int itot, int hmin, int hmax) {
	double rez = hmin - hmax;
	rez = rez / (double)(itot - 1);
	rez = rez * (i - 1) + hmax;
	return (int)rez;
}


double probability(int dE, double T) {

	double exponent = (double)dE / T;
	exponent *= (-1.0);
	double e = exp(1.0);
	double rez = pow(e, exponent);
	//cout << rez << endl;
	return rez;

}

int f(int* x, int n, int* s) {
	const int available = pow(2, 25);
	int F1 = available;
	int F2 = available;
	for (int i = 0; i < n; i++) {
		switch (x[i]) {
		case 1: {F1 -= s[i]; }break;
		case 2: {F2 -= s[i]; }break;
		default:break;
		}
	}

	if (F1<0 || F2<0)return 2 * available;
	return F1+F2;




}

typedef struct Data
{
	int n;
	int* x;
	int* s;
	int hmin;
	int hmax;
	int itot;
	double T;
	double a;

	//minimization
	int* cF;
	int minF;
	int* minX;
};



int annealing(ostream& fajl, Data* d, int numOfIter) {
	int n = d->n;
	int* x = d->x;
	int* s = d->s;
	int hmin = d->hmin;
	int hmax = d->hmax;
	int itot = d->itot;
	double T = d->T;
	double a = d->a;

	int* cF = d->cF;
	int minF = d->minF;
	int* minX = d->minX;


	int granulation = itot;

	for (int i = 1; i <= itot; i++) {

		int h = hamming_distance(i, itot, hmin, hmax);
		int* locationsForSwitch = new int[h];
		random_combination(n, h, locationsForSwitch);

		/*if (i % granulation == 1) {
			cout << "h: " << h << endl;
			cout << "\nH: ";
			for (int j = 0; j < h; j++)cout << locationsForSwitch[j] << " ";
			cout << endl;
		}*/



		int* newx = new int[n];
		for (int br = 0; br < n; br++) {
			newx[br] = x[br];
		}
		/*if (i % granulation == 1) {
			cout << "newx osnova: \n";
			for (int j = 0; j < n; j++)cout << newx[j];
			cout << endl;
		}*/
		//cange on locations
		for (int br = 0; br < h; br++) {
			while (newx[locationsForSwitch[br] - 1] == x[locationsForSwitch[br] - 1]) {
				newx[locationsForSwitch[br] - 1] = rand_val();
			}
		}
		/*if (i % granulation == 1) {
			for (int j = 0; j < n; j++)cout << newx[j];
			cout << endl;
		}*/
		delete[] locationsForSwitch;


		int Fx = f(x, n, s);
		fajl << minF << ",";
		//if (i % granulation == 1)cout << "Fx: " << Fx << endl;
		int Fnewx = f(newx, n, s);
		//if (i % granulation == 1)cout << "Fnewx: " << Fnewx << endl;

		//minimzation
		cF[numOfIter*itot + i-1] = Fx;
		if (minF > Fx) {
			minF = Fx;
			for (int pomm = 0; pomm < n; pomm++)d->minX[pomm] = x[pomm];
		}

		//determinating change of x
		int dE = Fnewx - Fx;
		bool flagchanged = 0;
		double prag = -1;
		double p = -1;
		if (dE < 0) {
			delete[] x;
			x = newx;
			flagchanged = true;
		}
		else {
			prag = (double)rand() / (float)RAND_MAX;
			if (dE == 0) {
				if (prag < 0.5) {
					delete[] x;
					x = newx;
					flagchanged = true;
				}
			}
			if (dE > 0) {
				p = probability(dE, T);
				if (p > prag) {
					delete[] x;
					x = newx;
					flagchanged = true;
				}
				/*if (i < 100) {
					for (int br = 0; br < n; br++) {
						cout << x[br];
					}cout << endl;
					cout << Fx << endl;
					for (int br = 0; br < n; br++) {
						cout << newx[br];
					}cout << endl;
					cout << Fnewx << endl;
					cout << "dE: " << dE << endl;
					cout << "T: " << T << endl;
					cout << "p: " << p << endl;

					//cout << "prag: " << prag << endl;
				}*/
			}
		}
		if (flagchanged == false) {
			delete[] newx;
			//if (i % granulation == 1)cout << "no switch" << endl;
		}
		else {
			//cout << "change";
			/*cout << "------------------------------------yes switch-----------------------------------------" << endl;
			cout << "   Fx: " << Fx << endl;
			cout << "Fnewx: " << Fnewx << endl;
			cout << "T: " << T << endl;
			cout << "dE: " << dE << endl;
			cout << "p: " << p << endl;
			cout << "prag: " << prag << endl;
			cout << "---------------------------------------------------------------------------------------" << endl;*/
		}

		//decrese temp
		T *= a;

	}

	//save progress
	d->x = x;
	d->minF = minF;
	d->minX = minX;
	return minF;
}


int reanniling(ofstream &f, int* s, int n, int numIterations, int paramA, int factorHMax, int*solution) {

	
	int* x = new int[n];
	for (int i = 0; i < n; i++) {
		x[i] = rand_val();
	}

	int hmin = 2;
	int hmax = n / factorHMax;
	int itot = 100000;
	double T = 64 * 1024 * 1024;
	double a = paramA;

	//cumulative;
	int* cF = new int[numIterations * itot];
	int minF = pow(2, 26);
	int* minX = new int[n];
	for (int br = 0; br < n; br++)minX[br] = 0;

	Data* d = new Data();
	d->n = n;
	d->x = x;
	d->s = s;
	d->hmin = hmin;
	d->hmax = hmax;
	d->itot = itot;
	d->T = T;
	d->a = a;
	d->cF = cF;
	d->minF = minF;
	d->minX = minX;




	for (int i = 0; i < numIterations; i++) {

		minF = annealing(f, d, i);
		cout << "Najmanje resejne[" << i << "]: " << minF << endl;
		//f << "Najmanje resejne[" << i << "]: " << minF << endl;

		//prepare for reanniling
		delete[] d->x;
		d->x = new int[n];
		for (int pom = 0; pom < n; pom++)d->x[pom] = d->minX[pom];
		d->minF = minF;
		d->T = T;
	}

	for (int i = 0; i < n; i++)solution[i] = d->minX[i];
	return minF;

}

 
int main() {
	//seed: 1700922184
	//vr(117) 1700924117. hmax = 1/3, a = 0.98
	int seed = time(NULL);
	srand(seed);

	//initialize program
	int numOfExecutions = 20;

	//initialize reanneling
	int numIterations = 10;
	int a = 0.9646;
	int factorHmax =12;

	//initialization Simulated-Annealing
	int n = 64;
	int s[64] = { 173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708, 631252, 148665, 150254, 4784408, 344759,
	440109, 4198037, 329673, 28602, 144173, 1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997, 254845,
	486167, 2667146, 264004, 297223, 94694, 1757457, 576203, 8577828, 498382, 8478177, 123575, 4062389, 3001419,
	196884, 617991, 421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834, 201919, 56080, 2142553, 326263,
	8172117, 2304253, 4761871, 205387, 6148422, 414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571 };


	//Dobar seed:  1700936392

	
	int sumOfMins = 0;
	int numOfExtremes = 0;

	//minimization
	
	int trenMin = (int)pow(2, 26);
	int* solution = new int[n];
	int* trenMinX = new int[n];




	for (int i = 0; i < numOfExecutions; i++) {
		ofstream f;

		string fajlName = "data";
		char* c = new char[4];
		_itoa_s(i, c, 4, 10);
		fajlName += c;
		fajlName += ".txt";
		cout << fajlName << endl;

		f.open(fajlName);

		cout << "Reannealing #" << i << ": " << endl;
		int ret = reanniling(f, s, n, numIterations, a, factorHmax, solution);
		sumOfMins += ret;
		if (ret > 2000)numOfExtremes++;
		cout << endl;
		f.close();

		//minimization
		if (ret < trenMin) {
			trenMin = ret;
			for (int j = 0; j < n; j++) trenMinX[j] = solution[j];
		}

	}


	fstream ff;
	string minFName = "minimumValue.txt";
	ff.open(minFName);
	ff << trenMin << endl;
	for (int i = 0; i < n; i++)ff << trenMinX[i];
	ff.close();


	cout << "Avg. min value: " << sumOfMins / numOfExecutions << endl;
	cout << "Extremes: " << numOfExtremes << endl;

	cout << "seed: " << seed << endl;

	
}

