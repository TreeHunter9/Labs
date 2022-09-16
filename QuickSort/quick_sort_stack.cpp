#include "quick_sort_stack.h"

QuickSortStack::QuickSortStack(int size)
	: m_segments(new StackSegment[size]), m_size(size)
{}

QuickSortStack::~QuickSortStack()
{
	delete[] m_segments;
}

void QuickSortStack::Push(int leftIndex, int rightIndex)
{
	if (leftIndex < rightIndex && m_size > m_top + 1)
	{
		m_segments[++m_top] = { leftIndex, rightIndex };
	}
}

void QuickSortStack::Pop(int& outLeftIndex, int& outRightIndex)
{
	outLeftIndex = m_segments[m_top].left;
	outRightIndex = m_segments[m_top].right;
	m_top--;
}

bool QuickSortStack::IsEmpty()
{
	return m_top <= -1;
}
