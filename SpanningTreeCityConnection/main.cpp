#include <iostream>


int f(int len, int* T, int** cM) {
	int n = len + 2;

	int* histogram = new int[n];

	for (int i = 0; i < n; i++) {
		histogram[i] = 0;
	}
	

	int c = 0;
	for (int i = 1; i < 2 * (n-1); i+=2) {
		histogram[T[i] - 1]++;
		histogram[T[i - 1] - 1]++;
		c += cM[T[i] - 1][T[i - 1] - 1];
	}
	
	for (int i = 0; i < n; i++) {
		if (histogram[i] >= 4)c += 250 * (histogram[i] - 3);
	}

	delete[] histogram;
	return c;
}




void SequenceToSpanningTree(int* P, int len, int* T) {

	int i, j, q = 0;
	int n = len + 2;
	int* V = new int[n];

	for (i = 0; i < n; i++)
		V[i] = 0;

	for (i = 0; i < len; i++)
		V[P[i] - 1] += 1;

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (V[j] == 0)
			{
				V[j] = -1;
				T[q++] = j + 1;
				T[q++] = P[i];
				V[P[i] - 1]--;
				break;
			}
		}
	}
	j = 0;

	for (i = 0; i < n; i++)
	{
		if (V[i] == 0 && j == 0)
		{
			T[q++] = i + 1;
			j++;
		}
		else if (V[i] == 0 && j == 1)
		{
			T[q++] = i + 1;
			break;
		}
	}

	delete[] V;
}


void main(void)
{

	//parametri
	int n = 10;
	int k = n - 2;
	
	
	//matrica cena
	int costM[10][10] = {
		{ 0,   374,  350,  223,  108,  178,  252,  285,  240,  356},
		{374,	 0,   27,  166,  433,  199,  135,   95,  136,   17},
		{350,	27,    0,   41,   52,  821,  180,  201,  131,  247},
		{223,  166,   41,    0,  430,   47,   52,   84,   40,  155},
		{108,  433,   52,  430,    0,  453,  478,  344,  389,  423},
		{178,  199,  821,   47,  453,    0,   91,   37,   64,  181},
		{252,  135,  180,   52,  478,   91,    0,   25,   83,  117},
		{285,   95,  201,   84,  344,   37,   25,    0,   51,   42},
		{240,  136,  131,   40,  389,   64,   83,   51,    0,  118},
		{356,   17,  247,  155,  423,  181,  117,   42,  118,    0}
	};
	

	int** cmm = new int* [n];
	for (int i = 0; i < n; i++) {
		cmm[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cmm[i][j] = costM[i][j];
		}
	}

	//min cost & path
	int minCost = INT_MAX;
	int* bestTree = new int[2 * (k + 1)];
	for (int i = 0; i < 2 * (k + 1); i++)bestTree[i] = 0;


	
	//pravljenje varijacija sa ponavljanjem

	int q;
	int* P = new int[k];
	for (int i = 0; i < k; i++)
		P[i] = 0;
	do
	{	
		//print variation
		/*r(int i = 0; i < k; i++)
		{
			printf("%5d ", P[i] + 1);
		}
		printf("\n");*/
		for (int i = 0; i < k; i++)P[i] += 1;

		int len = k;
		int* T = new int[2 * (len + 1)];

		//pravljenje stabla grafa
		SequenceToSpanningTree(P, len, T);


		//vracanje vrednosti za algoritam varijacija(0 - n-1)
		for (int i = 0; i < k; i++) {
			P[i] -= 1;
		}

		

		//Obrada T
		int c = f(len, T, cmm);
		if (c < minCost) {
			minCost = c;
			for (int i = 0; i < 2 * (k + 1); i++)bestTree[i] = T[i];
		}

		//Nastavak varicjacije
		q = k - 1;
		while (q >= 0)
		{
			P[q]++;
			if (P[q] == n)
			{
				P[q] = 0;
				q--;
			}
			else
				break;
		}
	} while (q >= 0);
	delete[] P;



	for (int i = 0; i < 2 * (k + 1); i++)
	{
		printf("%c", 'A' - 1 + bestTree[i]);
		if ((i + 1) % 2 == 0 && i < 2 * k)
			printf(" - ");
	}
	printf("\n");
	std::cout << "Cena: " << minCost << std::endl;
}