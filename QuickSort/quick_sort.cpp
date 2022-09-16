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

		int pivotIndex;
		int pivotValue;

		QuickSortStack stack(size);
		stack.Push(leftIndex, rightIndex);

		while (stack.IsEmpty() == false)
		{
			stack.Pop(leftIndex, rightIndex);

			leftCounter = leftIndex;
			rightCounter = rightIndex - 1;

			pivotIndex = (leftIndex + rightIndex) / 2;
			pivotValue = arr[pivotIndex];

			swap(arr[pivotIndex], arr[rightIndex]);

			while (leftCounter < rightCounter)
			{
				while (arr[leftCounter] < pivotValue)
					leftCounter++;
				while (arr[rightCounter] > pivotValue)
					rightCounter--;

				if (leftCounter >= rightCounter)
					break;

				swap(arr[leftCounter], arr[rightCounter]);

				leftCounter++;
			}

			swap(arr[leftCounter], arr[rightIndex]);

			if (leftCounter - leftIndex == 2)
			{
				if (arr[leftIndex] > arr[leftIndex + 1])
				{
					swap(arr[leftIndex], arr[leftIndex + 1]);
				}
			}
			else if (leftCounter - leftIndex > 1)
			{
				stack.Push(leftIndex, leftCounter - 1);
			}

			if (rightIndex - rightCounter == 2)
			{
				if (arr[rightIndex] < arr[rightIndex - 1])
				{
					swap(arr[rightIndex], arr[rightIndex - 1]);
				}
			}
			else if (rightIndex - rightCounter > 1)
			{
				stack.Push(leftCounter + 1, rightIndex);
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