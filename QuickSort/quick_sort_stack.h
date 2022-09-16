#pragma once

class QuickSortStack
{
public:
	QuickSortStack(int size);
	~QuickSortStack();

	void Push(int leftIndex, int rightIndex);
	void Pop(int& outLeftIndex, int& outRightIndex);
	bool IsEmpty();
private:
	struct StackSegment
	{
		int left;
		int right;
	};

	StackSegment* m_segments;
	int m_size;
	int m_top = -1;
};

