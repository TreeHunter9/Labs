#include <iostream>
#include <chrono>
#include <stdlib.h>

#include "quick_sort.h"

int main()
{
	srand(time(NULL));
	int size = 1000;
	int* arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 100;
	}
	
	auto start = std::chrono::steady_clock::now();
	sort::QuickSort(arr, size);
	auto end = std::chrono::steady_clock::now();

	auto duration = end - start;
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << ' ';

	std::cout << '\n' << "Execution time: " << duration.count() << " ns" << '\n';
}
