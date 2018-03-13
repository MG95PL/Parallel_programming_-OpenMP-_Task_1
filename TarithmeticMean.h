#pragma once


class TarithmeticMean
{
	long  int* table;
	long int table_size;
	double result;

public:

	~TarithmeticMean() { delete[] table; }

	void setTableSize();
	void memoryReservation();
	double arithmeticMeanCalculate();

};

