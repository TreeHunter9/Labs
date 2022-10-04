#pragma once

template<class T>
class LinkedListNode;

template<class T>
class LinkedListIterator
{
public:
	using ValueType = LinkedListNode<T>;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;	
public:
	LinkedListIterator(PointerType ptr)
		: m_ptr(ptr)
	{}

	LinkedListIterator<T>& operator++()
	{
		m_ptr = m_ptr->next;
		return *this;
	}

	LinkedListIterator<T>& operator++(int) 
	{
		LinkedListIterator<T> tmp = *this;
		++(*this);
		return tmp;
	}

	LinkedListIterator<T>& operator--()
	{
		m_ptr = m_ptr->prev;
		return *this;
	}

	LinkedListIterator<T>& operator--(int)
	{
		LinkedListIterator<T> tmp = *this;
		--(*this);
		return tmp;
	}

	PointerType operator->()
	{
		return m_ptr;
	}

	ReferenceType operator*() const
	{
		return *m_ptr;
	}

	bool operator==(const LinkedListIterator<T>& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const LinkedListIterator<T>& other) const
	{
		return !(*this == other);
	}
private:
	PointerType m_ptr;
};

template<class T>
class LinkedList
{
public:
	LinkedList()
		: m_first(nullptr), m_last(nullptr)
	{}

	~LinkedList()
	{
		RemoveAll();
	}

	void AddBegin(const T& value)
	{
		LinkedListNode<T>* node = new LinkedListNode(value);
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

	void AddEnd(const T& value)
	{
		LinkedListNode<T>* node = new LinkedListNode(value);
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
	
	void RemoveBegin()
	{
		if (!m_first)
			return;
		
		if (m_first == m_last)
		{
			delete m_first;
			m_first = nullptr;
			m_last = nullptr;
			return;
		}

		LinkedListNode<T>* delNode = m_first;
		m_first = m_first->next;
		m_first->prev = nullptr;
		delete delNode;
	}

	void RemoveEnd()
	{
		if (!m_first)
			return;

		if (m_first == m_last)
		{
			delete m_first;
			m_first = nullptr;
			m_last = nullptr;
			return;
		}

		LinkedListNode<T>* delNode = m_last;
		m_last = m_last->prev;
		m_last->next = nullptr;
		delete delNode;
	}

	void Remove(const T& value)
	{
		LinkedListNode<T>* foundNode = FindNode(value);
		if (!foundNode)
			return;

		LinkedListNode<T>* prevNode = foundNode->prev;
		LinkedListNode<T>* nextNode = foundNode->next;

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
	
	void RemoveAll()
	{
		while (m_last)
		{
			RemoveEnd();
		}
	}

	T GetBegin() const
	{
		return m_first->value;
	}

	T GetEnd() const
	{
		return m_last->value;
	}

	bool HasItem(const T& value) const
	{
		return FindNode(value);
	}

	bool IsEmpty() const
	{
		return !m_first;
	}

	LinkedListIterator<T> begin() const
	{
		return LinkedListIterator<T>(m_first);
	}

	LinkedListIterator<T> end() const
	{
		return LinkedListIterator<T>(nullptr);
	}
private:
	LinkedListNode<T>* FindNode(const T& value)
	{
		LinkedListNode<T>* node = m_first;
		while (node != nullptr)
		{
			if (node->value == value)
				return node;

			node = node->next;
		}

		return nullptr;
	}
private:
	LinkedListNode<T>* m_first;
	LinkedListNode<T>* m_last;
};

template<class T>
class LinkedListNode
{
public:
	LinkedListNode(const T& value)
		: value(value), next(nullptr), prev(nullptr)
	{}
public:
	T value;
private:
	LinkedListNode<T>* next;
	LinkedListNode<T>* prev;

	friend LinkedListIterator<T>;
	friend LinkedList<T>;
};