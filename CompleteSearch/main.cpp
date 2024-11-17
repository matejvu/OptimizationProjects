#include<iostream>
#include<complex>

#include<chrono>

using namespace std;


long long f(long long x1, long long x2, long long x3, long long x4) {
	if (x1 + x2 + x3 + x4 == 777  && x1 * x2 * x3 * x4==777000000)return 0;
	return 1;
}


int main() {


	int task = 0;
	//0: zadaak pod a)
	//1: zadatak pod b)

	std::chrono::duration<double>;

	int brPoziva = 0;
	switch (task)
	{
	case 0: {
		
		cout << "Potpuna pretraga kroz 4 promenljive\n\n";

		auto start = std::chrono::high_resolution_clock::now();
		for (long long x1 = 0; x1 < 778; x1++) {
			for (long long x2 = 0; x2 < 778; x2++) {
				for (long long x3 = 0; x3 < 778; x3++) {
					for (long long x4 = 0; x4 < 778; x4++) {

						brPoziva++;
						if (f(x1, x2, x3, x4) == 0) {
							cout << x1 << " " << x2 << " " << x3 << " " << x4 << "\n";
							
						}

					}
				}
			}
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double>duration = end - start;
		std::cout << "\nExecution time: " << duration.count() << " seconds." << std::endl;
		
	}break;

	case 1: {

		cout << "Potpuna pretraga kroz 3 promenljive\n\n";

		auto start = std::chrono::high_resolution_clock::now();
		for (long long x1 = 0; x1 < 778; x1++) {
			for (long long x2 = 0; x2 < 778; x2++) {
				for (long long x3 = 0; x3 < 778; x3++) {
					long long x4 = 777 - x1 - x2 - x3;

					brPoziva++;
					if (f(x1, x2, x3, x4) == 0) {
						cout << x1 << " " << x2 << " " << x3 << " " << x4 << "\n";
						
					}

				}
			}
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double>duration = end - start;
		std::cout << "\nExecution time: " << duration.count() << " seconds." << std::endl;

	}break;


	
	default:
		break;
	}
	



	cout << "Br. poziva optimizacione funkcije f: " << brPoziva;


	return 0;

}
