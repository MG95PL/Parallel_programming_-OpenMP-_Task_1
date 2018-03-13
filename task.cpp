#include <iostream>
#include <omp.h>
#include <chrono>
#include <ctime>

using namespace std;

class taskClass {

	long  int* x;
	long int size;
	double result; 

public:

	~taskClass() { delete[] x; }

	void step1()
	{
		cout << "Set table size\n";
		cin >> size;
	}


	void step2()
	{
		x = new long int[size];


		for (int i = 0; i < size; i++)
		{
			x[i] = i+1;
		}
	}

	double average()
	{
#define WERSJA 1
		// 1 = pragma for
		// 2 = sekcja krytyczna
		// 3 = sekscja krytyczna i zmienna lokalna  
		// 4 = reduction 

#if (WERSJA == 1)
#pragma omp parallel for num_threads(5)

		for (int i = 0; i < size; i++)
		{
			result += static_cast<double>(x[i]);
		}
			return result / size;
#endif
			
#if (WERSJA == 2)
#pragma omp parallel for num_threads(5)

			for (int i = 0; i < size; i++)
			{
#pragma omp critical 
				result += static_cast<double>(x[i]);
			}
			return result / size;
#endif

#if (WERSJA == 3)
		double lresult = 0.0;

#pragma omp parallel for num_threads(5)

		for (int i = 0; i < size; i++)
		{
			lresult += static_cast<double>(x[i]);
		}

#pragma omp critical 
		result += lresult;
		return result / size;
#endif

#if (WERSJA == 4)
#pragma omp parallel  num_threads(5)
#pragma opm for reduction(+: result)

			for (int i = 0; i < size; i++)
			{ 
				result += static_cast<double>(x[i]);
			}
		return result / size;
#endif

	

	}
#undef WERSJA 

};






int main()
{
	cout << "hello\n";

	taskClass ob;

	ob.step1();
	ob.step2();

	auto start = chrono::system_clock::now();

	cout << ob.average() << endl;

	auto end = chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds = end - start;
	cout << "elapsed time: " << elapsed_seconds.count() << "s\n";




	return 0;
}
