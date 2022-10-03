#include "linked_list.h"

template<class T>
LinkedList<T>::LinkedList()
	: m_first(nullptr), m_last(nullptr)
{}
template<class T>
LinkedList<T>::~LinkedList()
{}

template<class T>
void LinkedList<T>::AddBegin(const T& value)
{
	LinkedListNode* node = new LinkedListNode(value);
	if (!m_first)
	{
		m_first = node;
		m_last = node;
		return;
	}

	node->next = m_first;
	m_first->prev = node;
	m_first = node;
}

template<class T>
void LinkedList<T>::AddEnd(const T& value)
{
	LinkedListNode* node = new LinkedListNode(value);
	if (!m_first)
	{
		m_first = node;
		m_last = node;
		return;
	}

	node->prev = m_last;
	m_last->next = node;
	m_last = node;
}

template<class T>
void LinkedList<T>::RemoveBegin()
{
	if (!m_first)
		return;
	
	if (m_first == m_last)
	{
		delete m_first;
		return;
	}

	LinkedListNode* delNode = m_first;
	m_first = m_first->next;
	m_first->prev = nullptr;
	delete delNode;
}

template<class T>
void LinkedList<T>::RemoveEnd()
{
	if (!m_first)
		return;

	if (m_first == m_last)
	{
		delete m_first;
		return;
	}

	LinkedListNode* delNode = m_last;
	m_last = m_last->prev;
	m_last->next = nullptr;
	delete delNode;
}

template<class T>
void LinkedList<T>::RemoveAll()
{
	
}

template<class T>
T* LinkedList<T>::GetBegin()
{
	return m_first->value;
}

template<class T>
T* LinkedList<T>::GetEnd()
{
	return m_last->value;
}

template<class T>
void LinkedList<T>::Remove(const T& value)
{
	LinkedListNode* foundNode = FindNode(value);
	if (!foundNode)
		return;

	LinkedListNode* prevNode = foundNode->prev;
	LinkedListNode* nextNode = foundNode->next;
	if (!prevNode)
	{
		RemoveBegin();
		return;
	}
	if (!nextNode)
	{
		RemoveEnd();
		return;
	}
	prevNode->next = nextNode;
	nextNode->prev = prevNode;
	delete foundNode;
}

template<class T>
bool LinkedList<T>::HasItem(const T& value)
{
	return FindNode(value);
}

template<class T>
LinkedList<T>::LinkedListNode<T>* LinkedList<T>::FindNode(const T& value)
{
	LinkedListNode* node = m_first;
	while (node != nullptr)
	{
		if (node->value == value)
			return node;

		node = node->next;
	}

	return nullptr;
}
