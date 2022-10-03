#pragma once

template<class T>
class LinkedList
{
public:
	template<class T>
	class LinkedListNode
	{
	public:
		LinkedListNode(const T& value)
			: value(value)
		{}
	public:
		T* value;
		LinkedListNode* next;
		LinkedListNode* prev;
	};

	template<class T>
	class Iterator
	{
		using value_type = LinkedListNode<T>;
		using pointer = LinkedListNode<T>*;
		using reference = LinkedListNode<T>&;
	public:
		Iterator(pointer ptr)
			: m_ptr(ptr)
		{}

		reference operator*() const
		{
			return *m_ptr;
		}

		pointer operator->()
		{
			return m_ptr;
		}

		Iterator& operator++()
		{
			m_ptr = m_ptr->next;
			return *this;
		}

		Iterator operator++(int) 
		{
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		template<class T>
		friend bool operator==(const Iterator<T>& a, const Iterator<T>& b)
		{
			return a.m_ptr == b.m_ptr;
		}

		friend bool operator!=(const Iterator<T>& a, const Iterator<T>& b)
		{
			return !(a == b);
		}
	private:
		pointer m_ptr;
	};

	LinkedList();
	~LinkedList();

	void AddBegin(const T& value);
	void AddEnd(const T& value);
	void RemoveBegin();
	void RemoveEnd();
	void RemoveAll();
	T* GetBegin();
	T* GetEnd();
	void Remove(const T& value);
	bool HasItem(const T& value);

	Iterator<T> begin()
	{
		return Iterator(m_first);
	}
	Iterator<T> end()
	{
		return Iterator(nullptr);
	}
private:
	LinkedListNode<T>* FindNode(const T& value);
private:
	LinkedListNode<T>* m_first;
	LinkedListNode<T>* m_last;
};


