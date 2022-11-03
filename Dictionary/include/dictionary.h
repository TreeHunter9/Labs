#pragma once

#include <functional>
#include <cstring>

template<class TKey, class TValue>
class Node
{
public:
	Node(TKey key)
		: key(key), next_node(nullptr)
	{}
public:
	TKey key;
	TValue value;
	Node<TKey, TValue>* next_node;
};

template<class TKey, class TValue>
class Dictionary
{
public:
	Dictionary()
		: m_bucket_size(m_default_bucket_size), m_node_count(0)
	{
		m_bucket = new Node<TKey, TValue>*[m_bucket_size] {nullptr};
		memset(m_bucket, 0, m_bucket_size);
	}

	Dictionary(unsigned int size)
		: m_bucket_size(size), m_node_count(0)
	{
		m_bucket = new Node<TKey, TValue>*[m_bucket_size] {nullptr};
		memset(m_bucket, 0, m_bucket_size);
	}

	~Dictionary()
	{
		ClearBucket();
	}

	TValue& operator[](TKey key)
	{
		std::size_t key_hash = std::hash<TKey>{}(key) % m_bucket_size;
		Node<TKey, TValue>* new_node = new Node<TKey, TValue>(key);

		if (m_bucket[key_hash] == nullptr)
		{
			m_bucket[key_hash] = new_node;
			m_node_count++;
			return new_node->value;
		}

		Node<TKey, TValue>* current_node = m_bucket[key_hash];
		int current_depth = 0;
		while (current_node)
		{
			if (current_node->key == key)
				throw std::invalid_argument("Key already exists");
			
			current_depth++;
			if (!current_node->next_node)
				break;
			current_node = current_node->next_node;
		}
		current_node->next_node = new_node;

		if (current_depth > m_max_depth)
			Resize();

		m_node_count++;
		return new_node->value;
	}

	void Add(const TKey key, TValue value)
	{
		this->operator[](key) = value;
	}

	bool TryAdd(const TKey key, const TValue value)
	{
		std::size_t key_hash = std::hash<TKey>{}(key) % m_bucket_size;
		Node<TKey, TValue>* new_node = new Node<TKey, TValue>(key);

		if (m_bucket[key_hash] == nullptr)
		{
			m_bucket[key_hash] = new_node;
			new_node->value = value;
			m_node_count++;
		}

		Node<TKey, TValue>* current_node = m_bucket[key_hash];
		int current_depth = 0;
		while (current_node)
		{
			if (current_node->key == key)
				return false;
			
			current_depth++;
			if (!current_node->next_node)
				break;
			current_node = current_node->next_node;
		}
		current_node->next_node = new_node;

		if (current_depth > m_max_depth)
			Resize();

		m_node_count++;
		return true;
	}

	TValue GetValue(const TKey& key)
	{
		Node<TKey, TValue>* found_node = GetNodeByKey(key);
		if (found_node)
			return found_node->value;

		throw std::invalid_argument("The dictionary does not have this key");
	}

	bool TryGetValue(const TKey& key, TValue& out_value)
	{
		Node<TKey, TValue>* found_node = GetNodeByKey(key);
		if (found_node)
		{
			out_value = found_node->value;
			return true;
		}
		return false;
	}

	bool ContainsKey(const TKey& key)
	{
		std::size_t key_hash = std::hash<TKey>{}(key) % m_bucket_size;
		Node<TKey, TValue>* node = m_bucket[key_hash];
		if (node == nullptr)
			return false;

		while(node)
		{
			if (node->key == key)
				return true;
			node = node->next_node;
		}
		return false;
	}

	bool RemoveKey(const TKey& key)
	{
		std::size_t key_hash = std::hash<TKey>{}(key) % m_bucket_size;
		if (!m_bucket[key_hash])
			return false;
		
		Node<TKey, TValue>* parent_node = m_bucket[key_hash];
		Node<TKey, TValue>* next_node = parent_node;
		if (parent_node->key == key)
		{
			delete parent_node;
			m_bucket[key_hash] = nullptr;
			return true;
		}
		while(next_node)
		{
			if (next_node->key == key)
			{
				parent_node->next_node = next_node->next_node;
				delete next_node;
				return true;
			}
			parent_node = next_node;
			next_node = parent_node->next_node;
		}
		return false;
	}

	void Clear()
	{
		ClearBucket();
		m_bucket_size = m_default_bucket_size;
		m_node_count = 0;
	}

	// Return bucket size
	int Size() const
	{
		return m_bucket_size;
	}

	// Return the number of elements
	int Count() const
	{
		return m_node_count;
	}
private:
	Node<TKey, TValue>* GetNodeByKey(const TKey& key)
	{
		std::size_t key_hash = std::hash<TKey>{}(key) % m_bucket_size;
		Node<TKey, TValue>* node = m_bucket[key_hash];
		while(node)
		{
			if (node->key == key)
				return node;
			node = node->next_node;
		}
		return nullptr;
	}

	void DeleteChainNodes(Node<TKey, TValue>* node)
	{
		Node<TKey, TValue>* current_node = node;
		Node<TKey, TValue>* delete_node = current_node;
		while(current_node)
		{
			delete_node = current_node;
			current_node = current_node->next_node;
			delete delete_node;
		}
	}

	void ClearBucket()
	{
		for (int i = 0; i < m_node_count; i++)
		{
			if (m_bucket[i] == nullptr)
				continue;
			
			DeleteChainNodes(m_bucket[i]);
			m_bucket[i] = nullptr;
		}
	}

	void FindNewPlace(Node<TKey, TValue>* node)
	{
		std::size_t key_hash = std::hash<TKey>{}(node->key) % m_bucket_size;

		if (m_bucket[key_hash] == nullptr)
		{
			m_bucket[key_hash] = node;
			return;
		}

		Node<TKey, TValue>* current_node = m_bucket[key_hash];
		while (current_node)
		{
			if (!current_node->next_node)
				break;
			current_node = current_node->next_node;
		}
		current_node->next_node = node;
	}

	void Resize()
	{
		int old_bucket_size = m_bucket_size;
		m_bucket_size *= m_size_multiplier;

		Node<TKey, TValue>** old_bucket = m_bucket;
		m_bucket = new Node<TKey, TValue>*[m_bucket_size] {nullptr};
		for (int i = 0; i < old_bucket_size; i++)
		{
			if (old_bucket[i] == nullptr)
				continue;
			
			Node<TKey, TValue>* node = old_bucket[i];
			while (node)
			{
				FindNewPlace(node);
				node = node->next_node;
			}
		}
		delete[] old_bucket;
	}
private:
	Node<TKey, TValue>** m_bucket;
	int m_node_count;
	int m_bucket_size;

	static const int m_max_depth = 10;
	static const int m_default_bucket_size = 10;
	static const int m_size_multiplier = 2;
};