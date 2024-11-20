#include<stdlib.h>>
#include<iostream>
#include<fstream>
#include<cmath>


using namespace std;

typedef struct ParamData {
    int EliteParentsFactor;
    int EliteBreedingsFactor;
    int SavedOldElite;
    int  UnprivilegedParentsFactor;
    double mutationProbability;

};


int random_int(int a, int b) {
    int res;
    res = a + rand() % (b + 1 - a);
    return res;
}
double random_float(double a, double b)
{
    double res;
    res = a + (double)rand() / (double)(RAND_MAX / (b - a));
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
void random_permutation(int n, int* p)
{
    int i, j, s;
    for (i = n - 1; i > 0; i--)
    {
        j = random_int(0, i);
        if (i != j)
        {
            s = p[i];
            p[i] = p[j];
            p[j] = s;
        }
    }
}
void generateGenerationZero(int** population, int popSize, int geneSize) {

    for (int i = 0; i < popSize; i++) {
        int* gene = new int[geneSize];
        for (int j = 0; j < geneSize; j++)gene[j] = random_int(0, 2);
        population[i] = gene;
    }
}

void shuffle(int* niz, int n) {
    int* newOrder = new int[n];
    int* stariNiz = new int[n];
    for (int i = 0; i < n; i++) {
        newOrder[i] = i;
        stariNiz[i] = niz[i];
    }
    random_permutation(n, newOrder);
    for (int i = 0; i < n; i++) {
        niz[i] = stariNiz[newOrder[i]];
    }
    delete[] stariNiz;
    delete[] newOrder;
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

    if (F1 < 0 || F2 < 0)return 2 * available;
    return F1 + F2;
}
int calculateFValuesForPopulation(int* fValues, int popSize, int** population, int geneSize, int* s, ofstream& ff, int cMin) {

    int instanceMin = 0;

    for (int instance = 0; instance < popSize; instance++) {
        fValues[instance] = f(population[instance], geneSize, s);
        if (fValues[instance] < fValues[instanceMin])instanceMin = instance;
        if (fValues[instance] < cMin) {
            cMin = fValues[instance];
        }
        ff << cMin << ",";
    }
    return instanceMin;
}

void sort_selected(int* &selected, int* fValues, int popSize) {

    for (int i = 0; i < popSize / 2 - 1; i++) {
        for (int j = i + 1; j < popSize / 2; j++) {
            if (fValues[selected[j]] < fValues[selected[i]]) {  
                int pom = selected[i];
                selected[i] = selected[j];
                selected[j] = pom;
            }
        }
    }

}
void performTurnirSelection(int** population,int popSize, int* fValues, int* &selected) {
    int* parovi = new int[popSize];
    selected = new int[popSize / 2];
    for (int i = 0; i < popSize; i++)parovi[i] = i;
    random_permutation(popSize, parovi);

    for (int i = 0; i < popSize; i += 2) {
        int instance1 = parovi[i];
        int instance2 = parovi[i+1];

        if (fValues[instance1] < fValues[instance2]) {
            selected[i / 2] = instance1;
        }
        else {
            selected[i / 2] = instance2;
        }
    }
    delete[] parovi;

    //sort_selected(selected, fValues, popSize);
}
void performDecimationSelection(int** population, int popSize, int* fValues, int*& selected) {
    for (int i = 0; i < popSize-1; i++) {
        for (int j = i + 1; j < popSize; j++) {
            if (fValues[j] < fValues[i]) {
                int pom = fValues[i];
                fValues[i] = fValues[j];
                fValues[j] = pom;

                int* pomPok = population[i];
                population[i] = population[j];
                population[j] = pomPok;
            }
        }
    }//vrv moze i da se sortira selected samo po fvalues

    selected = new int[popSize / 2];
    for (int i = 0; i < popSize / 2; i++) {
        selected[i] = i;
    }
}
void performSelectionSelection(int** population, int popSize, int* fValues, int*& selected) {
    selected = new int[popSize/2];
    for (int i = 0; i < popSize/2; i++)selected[i] = i;

    sort_selected(selected, fValues, popSize);
}

void makeOffspring(int** population,int &inst, int* parent1, int* parent2, int geneSize, double probability) {
    double p = random_float(0, 1);
    if (p <= probability) {
        int crossPoint = random_int(0, geneSize - 1);
        int* child1 = new int[geneSize];
        int* child2 = new int[geneSize];
        for (int j = 0; j < geneSize; j++) {
            if (j < crossPoint) {
                child1[j] = parent1[j];
                child2[j] = parent2[j];
            }
            else {
                child1[j] = parent2[j];
                child2[j] = parent1[j];
            }
        }
        population[inst++] = child1;
        population[inst++] = child2;
    }
}
void performSATBreedeing(int** &population, int popSize,int geneSize, int* selected) {
    int** oldPopulation = population;
    population = new int* [popSize];

    int inst = 0;
    for (int i = 0; i < 50; i+=2) {
        int* parent1 = new int[geneSize];
        int* parent2 = new int[geneSize];
        for (int j = 0; j < geneSize; j++) {
            parent1[j] = oldPopulation[selected[i]][j];
            parent2[j] = oldPopulation[selected[i + 1]][j];
        }
        //1702422593
        for(int br=0; br<1;br++)makeOffspring(population, inst, parent1, parent2, geneSize, 1);
        /*double p = random_float(0, 1);
        if (p < probability) {
            int crossPoint = random_int(0, geneSize - 1);
            int* child1 = new int[geneSize];
            int* child2 = new int[geneSize];
            for (int j = 0; j < geneSize; j++) {
                //parent1[j] = oldPopulation[selected[i]][j];
                //parent2[j] = oldPopulation[selected[i + 1]][j];

                if (j < crossPoint) {
                    child1[j] = parent1[j];
                    child2[j] = parent2[j];
                }
                else {
                    child1[j] = parent2[j];
                    child2[j] = parent1[j];
                }
            }
            population[inst++] = child1;
            population[inst++] = child2;
        }*/
        population[inst++] = parent1;
        population[inst++] = parent2;
        //1702421296
        //1702421340
        //1702422593 za manji mut
    }

    while (inst < popSize) {
        int bound;
        //if (inst < popSize/8)bound = popSize/100;
        //else bound = popSize / 2 - 1;
        bound = 750;

        int p1 = random_int(0,bound);
        int p2 = random_int(0,bound);
        //int* parent1 = population[p1];
        //int* parent2 = population[p2];
        int *parent1 = oldPopulation[selected[p1]];
        int *parent2 = oldPopulation[selected[p2]];

        makeOffspring(population, inst, parent1, parent2, geneSize, 0.8);

    }
    
    for (int i = 0; i < popSize; i++)delete[] oldPopulation[i];
    delete[] oldPopulation;
}
void performSATBreedeingS(int**& population, int popSize, int geneSize, int* selected) {
    int** oldPopulation = population;
    population = new int* [popSize];

    int inst = 0;
    for (int i = 0; i < 50; i += 2) {
        int* parent1 = new int[geneSize];
        int* parent2 = new int[geneSize];
        for (int j = 0; j < geneSize; j++) {
            parent1[j] = oldPopulation[selected[i]][j];
            parent2[j] = oldPopulation[selected[i + 1]][j];
        }
       
        for (int br = 0; br < 1; br++)makeOffspring(population, inst, parent1, parent2, geneSize, 1);
       
        population[inst++] = parent1;
        population[inst++] = parent2;
       
    }

    while (inst < popSize) {
        int bound;
        //if (inst < popSize/8)bound = popSize/100;
        //else bound = popSize / 2 - 1;
        bound = 750;

        int p1 = random_int(0, bound);
        int p2 = random_int(0, bound);
        //int* parent1 = population[p1];
        //int* parent2 = population[p2];
        int* parent1 = oldPopulation[selected[p1]];
        int* parent2 = oldPopulation[selected[p2]];

        makeOffspring(population, inst, parent1, parent2, geneSize, 0.8);

    }

    for (int i = 0; i < popSize; i++)delete[] oldPopulation[i];
    delete[] oldPopulation;
}

int performMutation(int** population, int popSize, int geneSize, double probability) {

    int mutatedInstances = 0;
    for (int instance = 0; instance < popSize; instance++) {
        bool mutated = false;
        double p = random_float(0, 1);
        if (p <= probability) {
            mutated = true;

            /*for (int gene = 0; gene < geneSize; gene++) {
                p = random_float(0, 1);
                if (p <= probability) {
                    int newGene;
                    do {
                        newGene = random_int(0, 2);
                    } while (newGene == population[instance][gene]);
                    population[instance][gene] = newGene;
                }
            }*/

            int mutatedGene = random_int(0, geneSize - 1);
            int newGene;
            do {
                newGene = random_int(0, 2);
            } while (newGene == population[instance][mutatedGene]);
            population[instance][mutatedGene] = newGene;
        }
        if (mutated)mutatedInstances++;
    }
    return mutatedInstances;
}



int geneticAlgorithm(int* s, int populationSize, int geneSize, int generation, int& cMin, ofstream& f, int* solution) {
    int** population = new int* [populationSize];
    int* individualFValues = new int[populationSize];
    int minimum = INT_MAX;

    generateGenerationZero(population, populationSize, geneSize);
    for (int g = 1; g <= generation; g++) {
        //cout << "Generation" << g << ":\n";
        int bestInstance = calculateFValuesForPopulation(individualFValues, populationSize, population, geneSize, s, f, cMin);
        //cout << "\tBest instance[" << bestInstance << "]\n";
        cout << "\tF value: " << individualFValues[bestInstance] << endl;
        minimum = individualFValues[bestInstance];
        if (g == generation)cout << "Br1: " << individualFValues[bestInstance] << endl;
        if (individualFValues[bestInstance] < cMin) {
            cMin = individualFValues[bestInstance];
            for (int i = 0; i < geneSize; i++)solution[i] = population[bestInstance][i];
        }

        int* selected = nullptr;

        //performDecimationSelection(population,populationSize, individualFValues, selected);
        //performTurnirSelection(population, populationSize, individualFValues, selected);
        performSelectionSelection(population, populationSize, individualFValues, selected);

        performSATBreedeing(population, populationSize, geneSize, selected);
        //performSATBreedeing(population, populationSize, geneSize, selected, p);

        int mN = performMutation(population, populationSize, geneSize, 0.8);
        //cout << "\tMutations in new generation: " << (double)mN/(double)populationSize << endl;

        delete[] selected;

        
    }

    
    delete[]individualFValues;
    for (int i = 0; i < populationSize; i++)delete[]population[i];
    delete[]population;


    //f << minimum;
    return minimum;
}


double oneStart(int n, int* s, int generation, int populationSize,int geneS) {

    int sumaMinimuma = 0;
    
    int* solution = new int[geneS];

    for (int i = 0; i < n; i++) {
        int kumulativniMinimum = pow(2, 26);
        ofstream f;
        string fajlName = "data";
        char* c = new char[4];
        _itoa_s(i, c, 4, 10);
        fajlName += c;
        fajlName += ".txt";
        
        cout << fajlName << endl;
        f.open(fajlName, 'w');

        sumaMinimuma += geneticAlgorithm(s, populationSize, geneS, generation, kumulativniMinimum, f, solution);
        f.close();
        cout << "Kumulativni[" << i << "]: " << kumulativniMinimum << endl;
        for (int s = 0; s < geneS; s++)cout << solution[s];
        cout << endl;
    }
    
    double prosek = (sumaMinimuma) / (double)n;
    return prosek;

}




int main() {

    //seed
    int seed = 1702425257;
    srand(seed);

	//meta initialzation
    int generation = 50;
    int populationSize = 20000;


	int geneSize = 64;
	int s[64] = { 173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708, 631252, 148665, 150254, 4784408, 344759,
	440109, 4198037, 329673, 28602, 144173, 1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997, 254845,
	486167, 2667146, 264004, 297223, 94694, 1757457, 576203, 8577828, 498382, 8478177, 123575, 4062389, 3001419,
	196884, 617991, 421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834, 201919, 56080, 2142553, 326263,
	8172117, 2304253, 4761871, 205387, 6148422, 414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571 };

	

   
    
    int rez = oneStart(20, s, generation, populationSize, geneSize);
    
    
   
    cout << "\nseed: " << seed << endl;
}
