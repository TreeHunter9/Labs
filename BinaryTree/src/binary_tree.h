#pragma once

#include <stdexcept>
#include <iostream>

template<class T>
class Node
{
public:
    Node(const T& value)
		: value(value), left_node(nullptr), right_node(nullptr), parent_node(nullptr)
	{}

	Node(const T& value, Node<T>* parent)
		: value(value), parent_node(parent), right_node(nullptr), left_node(nullptr)
	{}
public:
	T value;
    Node<T>* left_node;
    Node<T>* right_node;
	Node<T>* parent_node;
};

template<class T>
class BinaryTree
{
public:
	BinaryTree()
		: m_root(nullptr)
	{}

	~BinaryTree()
	{
		DeleteNode(m_root);
	}

	void Insert(const T& value)
	{
		if (!m_root)
		{
			m_root = new Node<T>(value);
			return;
		}

		Node<T>* parent = FindParentNode(value);
		if (value < parent->value)
		{
			parent->left_node = new Node<T>(value, parent);
		}
		else
		{
			parent->right_node = new Node<T>(value, parent);
		}
	}

	void Remove(const T& value)
	{
		Node<T>* found_node = FindNodeByValue(value);
		if (!found_node)
			throw std::invalid_argument("The value to delete is not found");

		Node<T> *x, *y;
		if (found_node->left_node == nullptr || found_node->right_node == nullptr )
		{
			y = found_node;
		}
		else
		{
			y = found_node->right_node;
			while(y->left_node != nullptr)
				y = y->left_node;
		}

		if (y->left_node != nullptr)
			x = y->left_node;
		else
			x = y->right_node;

		if (x!= nullptr)
			x->parent_node = y->parent_node;
		if (y->parent_node != nullptr)
		{
			if( y == y->parent_node->left_node ) y->parent_node->left_node = x;
			else y->parent_node->right_node = x;
		}
		else
			m_root = x;
		if(y != found_node)
		{
			found_node->value = y->value;
		}
		delete y;
	}

	void RemoveAll()
	{
		DeleteNode(m_root);
		m_root = nullptr;
	}

	bool HasValue(const T& value)
	{
		return FindNodeByValue(value);
	}

	bool IsEmpty() const
	{
		return !m_root;
	}

	void PrintAll() const
	{
		PrintNode(m_root);
	}
private:
	Node<T>* FindParentNode(const T& value)
	{
		Node<T>* parent_node = nullptr;
		Node<T>* current_node = m_root;
		while (current_node)
		{
			parent_node = current_node;
			if (value < parent_node->value)
				current_node = parent_node->left_node;
			else
				current_node = parent_node->right_node;
		}
		return parent_node;
	}

	Node<T>* FindNodeByValue(const T& value)
	{
		Node<T>* current_node = m_root;
		while (current_node)
		{
			if (value < current_node->value)
				current_node = current_node->left_node;
			else if (value > current_node->value)
				current_node = current_node->right_node;
			else
				return current_node;
		}
		return nullptr;
	}

	void DeleteNode(Node<T>* node)
	{
		if (node->left_node)
			DeleteNode(node->left_node);
		if (node->right_node)
			DeleteNode(node->right_node);
		delete node;
	}

	void PrintNode(Node<T>* node) const
	{
		if (node->left_node)
			PrintNode(node->left_node);
		std::cout << node->value << ' ';
		if (node->right_node)
			PrintNode(node->right_node);
	}
private:
	Node<T>* m_root;
};

