/*
Task 1
Write program which calculate arithmetic mean from n -elements table. 
The elements are intigers values from 0 to n. 
In for loop use OpenMP standard to make the program faster in 4 ways:

1. with no critical section
2. using critical section
3. using critical section and local variable
4. using  clause "reduction"

*/

#include <iostream>
#include <omp.h>
#include <chrono>
#include <ctime>

using namespace std;

class taskClass {

	long  int* table;
	long int table_size;
	double result;

public:

	~taskClass() { delete[] table; }

	void setTableSize()
	{
		cout << "Set table size\n";
		cin >> table_size;
	}


	void memoryReservation()
	{
		table = new long int[table_size];


		for (int i = 0; i < table_size; i++)
		{
			table[i] = i + 1;
		}
	}

	double arithmeticMeanCalculation()
	{

		// 1 = no critical section
		// 2 = critical section
		// 3 = critical section and local variable  
		// 4 = clause "reduction" 

#define VERSION 1

#if (VERSION == 1)
#pragma omp parallel for num_threads(5)

		for (int i = 0; i < table_size; i++)
		{
			result += static_cast<double>(table[i]);
		}
		return result / table_size;
#endif

#if (VERSION == 2)
#pragma omp parallel for num_threads(5)

		for (int i = 0; i < size; i++)
		{
#pragma omp critical 
			result += static_cast<double>(table[i]);
		}
		return result / size;
#endif

#if (VERSION == 3)
		double lresult = 0.0;

#pragma omp parallel for num_threads(5)

		for (int i = 0; i < size; i++)
		{
			lresult += static_cast<double>(table[i]);
		}

#pragma omp critical 
		result += lresult;
		return result / size;
#endif

#if (VERSION == 4)
#pragma omp parallel  num_threads(5)
#pragma opm for reduction(+: result)

		for (int i = 0; i < size; i++)
		{
			result += static_cast<double>(table[i]);
		}
		return result / size;
#endif



	}
#undef WERSJA 

};


int main()
{
	cout << "Hello\n";

	taskClass ob;

	ob.setTableSize();
	ob.memoryReservation();

	auto start = chrono::system_clock::now();         

	cout << ob.arithmeticMeanCalculation() << endl;

	auto end = chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds = end - start;
	cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";


	system("pause");

	return 0;
}
