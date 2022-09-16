#include <iostream>
#include <chrono>

#include "quick_sort.h"

int main()
{
	int* arr = new int[8] {1, 12, 67, 6, 23, 6, 4, 20};
	auto start = std::chrono::high_resolution_clock::now();
	sort::QuickSort(arr, 8);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = end - start;
	for (int i = 0; i < 8; i++)
		std::cout << arr[i] << ' ';

	std::cout << '\n' << "Execution time: " 
		<< std::chrono::duration_cast<std::chrono::microseconds>(duration) << '\n';
}
