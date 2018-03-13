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
#include "TarithmeticMean.h"

using namespace std;

int main()
{
	cout << "Hello\n";

	TarithmeticMean ob;

	ob.setTableSize();
	ob.memoryReservation();

	auto start = chrono::system_clock::now();         

	cout << ob.arithmeticMeanCalculate() << endl;

	auto end = chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds = end - start;
	cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";


	return 0;
}
