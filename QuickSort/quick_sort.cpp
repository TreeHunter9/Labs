#include <math.h>

#include "quick_sort_stack.h"

namespace sort
{
	void swap(int& value1, int& value2);

	void QuickSort(int* arr, int size)
	{
		if (size == 1)
			return;

		int leftIndex = 0;
		int rightIndex = size - 1;

		int leftCounter;
		int rightCounter;

		int pivotValue;

		QuickSortStack stack(log10((double)size) / log10(2.0) + 1);
		stack.Push(leftIndex, rightIndex);

		while (stack.IsEmpty() == false)
		{
			stack.Pop(leftIndex, rightIndex);

			while (leftIndex < rightIndex)
			{
				leftCounter = leftIndex;
				rightCounter = rightIndex;

				pivotValue = arr[(leftIndex + rightIndex) / 2];

				while (leftCounter <= rightCounter)
				{
					while (arr[leftCounter] < pivotValue)
						leftCounter++;
					while (arr[rightCounter] > pivotValue)
						rightCounter--;

					if (leftCounter <= rightCounter)
					{
						swap(arr[leftCounter], arr[rightCounter]);
						leftCounter++;
						rightCounter--;
					}
				}
				if (rightCounter - leftIndex < rightIndex - leftCounter)
				{
					stack.Push(leftCounter, rightIndex);
					rightIndex = rightCounter;
				}
				else
				{
					stack.Push(leftIndex, rightCounter);
					leftIndex = leftCounter;
				}
			}
		}
	}

	void swap(int& value1, int& value2)
	{
		int temp = value1;
		value1 = value2;
		value2 = temp;
	}
}