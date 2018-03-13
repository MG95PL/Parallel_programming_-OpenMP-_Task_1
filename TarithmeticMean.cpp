
#include "TarithmeticMean.h"
#include <iostream>

void TarithmeticMean::setTableSize()
{
	std::cout << "Set table size\n";
	std::cin >> table_size;
}


void TarithmeticMean::memoryReservation()
{
	table = new long int[table_size];


	for (int i = 0; i < table_size; i++)
	{
		table[i] = i + 1;
	}
}



double TarithmeticMean::arithmeticMeanCalculate()
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

#undef VERSION 

}