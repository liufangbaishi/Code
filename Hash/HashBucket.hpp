#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "comm.hpp"
using namespace std;

template <class K, class V>
struct HashNode
{
	pair<K, V> _kv;
	HashNode<K, V>* _pNext;
	HashNode(const pair<K, V>& kv)
		: _kv(kv)
		, _pNext(NULL)
	{}
};

template <class K, class V, class KeyToInt>
class HashTable;//声明

template <class K, class V, class KeyToInt = KeyToIntDef<K>>
struct HashTableIterator
{
	typedef HashNode<K, V> Node;
	typedef Node* PNode;
	typedef HashTableIterator<K, V, KeyToInt> Self;

	PNode _pCur;
	HashTable<K, V, KeyToInt>* _ht;
public:
	HashTableIterator()
		: _pCur(NULL)
		, _ht(NULL)
	{}

	HashTableIterator(const PNode pCur, HashTable<K, V, KeyToInt>* ht)
		: _pCur(pCur)
		, _ht(ht)
	{}

	HashTableIterator(Self& s)
		: _pCur(s._pCur)
		, _ht(s._ht)
	{}

	Self& operator++()
	{
		Next();
		return *this;
	}

	Self operator++(int)
	{
		HashTableIterator temp(*this);
		Next();
		return temp;
	}

	pair<K, V>& operator*()
	{
		return _pCur->_kv;
	}

	pair<K, V>* operator->()
	{
		return &(operator*());
	}

	bool operator==(const Self& s)
	{
		return _pCur == s._pCur;
	}

	bool operator!=(const Self& s)
	{
		return _pCur != s._pCur;
	}
private:
	void Next()
	{
		if (_pCur->_pNext)
			_pCur = _pCur->_pNext;
		else
		{//找下一个非空桶
			size_t bucketNo = _ht->HashFunc(_pCur->_kv.first) + 1;
			for (; bucketNo < _ht->_hashTable.capacity(); bucketNo++)
			{
				if (_ht->_hashTable[bucketNo])
				{
					_pCur = _ht->_hashTable[bucketNo];
					return;
				}
			}
			_pCur = NULL;//没有找到
		}
		return;
	}
};

template <class K, class V, class KeyToInt = KeyToIntDef<K>>
class HashTable
{
	typedef HashNode<K, V> Node;
	typedef Node* PNode;
	friend HashTableIterator<K, V, KeyToInt>;
public:
	typedef HashTableIterator<K, V, KeyToInt> Iterator;
public:
	HashTable(size_t capacity = 10)
	{
		//capacity = GetNextPrimer(capacity);
		_hashTable.resize(capacity);
		_size = 0;
	}

	Iterator Begin()
	{
		for (size_t bucketNo = 0; bucketNo < _hashTable.capacity(); bucketNo++)
		{
			if (_hashTable[bucketNo])
				return Iterator(_hashTable[bucketNo], this);
		}
		return Iterator(NULL, this);
	}

	Iterator End()
	{
		return Iterator(NULL, this);
	}

	pair<Iterator, bool> InsertEqual(const pair<K, V>& kv)//允许重复
	{
		CheckCapacity();
		size_t bucketNo = HashFunc(kv.first);
		PNode pNewNode = new Node(kv);
		pNewNode->_pNext = _hashTable[bucketNo];//头插
		_hashTable[bucketNo] = pNewNode;
		_size++;
		return make_pair(Iterator(pNewNode, this), true);
	}

	pair<Iterator, bool> InsertUnique(const pair<K, V>& kv)//key值唯一
	{
		CheckCapacity();
		size_t bucketNo = HashFunc(kv.first);
		PNode pCur = _hashTable[bucketNo];
		while (pCur)
		{
			if (kv.first == pCur->_kv.first)
				return make_pair(Iterator(pCur, this), false);
			pCur = pCur->_pNext;
		}
		pCur = new Node(kv);
		pCur->_pNext = _hashTable[bucketNo];
		_hashTable[bucketNo] = pCur;
		_size++;
		return make_pair(Iterator(pCur, this), true);
	}

	Iterator Find(const K& key)
	{
		size_t bucketNo = HashFunc(key);
		PNode pCur = _hashTable[bucketNo];

		while (pCur)
		{
			if (pCur->_kv.first == key)
				return Iterator(pCur, this);
			pCur = pCur->_pNext;
		}
		return Iterator(NULL, this);
	}

	Iterator Erase(Iterator pos)//key值唯一
	{
		if (pos._pCur == NULL)
			return Iterator(NULL, this);
		size_t key = pos._pCur->_kv.first;
		size_t bucketNo = HashFunc(key);
		PNode pCur = _hashTable[bucketNo];
		PNode pPre = NULL;
		while (pCur)
		{
			if (pCur->_kv.first == key)
			{
				if (_hashTable[bucketNo] == pCur)//pCur是首元素结点
					_hashTable[bucketNo] = pCur->_pNext;
				else
					pPre->_pNext = pCur->_pNext;
				delete pCur;
				pCur = NULL;
				_size--;
				return Iterator(pPre, this);
			}
			else
			{
				pPre = pCur;
				pCur = pCur->_pNext;
			}
		}
		return Iterator(NULL, this);
	}

	size_t Erase(const K& key)//key值可以重复
	{
		size_t oldsize = _size;
		size_t bucketNo = HashFunc(key);
		PNode pCur = _hashTable[bucketNo];
		PNode pPre = NULL;
		while (pCur)
		{
			if (pCur->_kv.first == key)
			{
				if (pCur == _hashTable[bucketNo])
				{
					_hashTable[bucketNo] = pCur->_pNext;
					delete pCur;
					pCur = _hashTable[bucketNo];
				}
				else
				{
					pPre->_pNext = pCur->_pNext;
					delete pCur;
					pCur = pPre->_pNext;
				}
				_size--;
			}
			else
			{
				pPre = pCur;
				pCur = pPre->_pNext;
			}
		}
		if (oldsize == _size)
			return 0;
		else
			return oldsize - _size;
	}

	size_t Count(const K key)//值为key的元素个数
	{
		size_t count = 0;
		size_t bucketNo = HashFunc(key);
		PNode pCur = _hashTable[bucketNo];
		while (pCur)
		{
			if (pCur->_kv.first == key)
				count++;
			pCur = pCur->_pNext;
		}
		return count;
	}

	size_t BucketCount()const//桶的个数
	{
		return _hashTable.capacity();
	}

	size_t BucketSize(size_t bucketNo)const//桶内元素个数
	{
		size_t count = 0;
		PNode pCur = _hashTable[bucketNo];
		while (pCur)
		{
			count++;
			pCur = pCur->_pNext;
		}
		return count;
	}

	V& FindORInsert(const K& key)
	{
		Iterator ret = InsertUnique(make_pair(key, V())).first;
		return (*ret).second;
	}

	bool Empty()const
	{
		return _size == 0;
	}

	size_t Size()const
	{
		return _size;
	}

	void Clear()
	{
		for (size_t bucketNo = 0; bucketNo < _hashTable.capacity(); bucketNo++)
		{
			PNode pCur = _hashTable[bucketNo];
			while (pCur)
			{
				_hashTable[bucketNo] = pCur->_pNext;
				delete pCur;
				pCur = _hashTable[bucketNo];
				_size--;
			}
		}
	}

	~HashTable()
	{
		Clear();
	}
private:
	size_t HashFunc(const K& key)
	{
		return KeyToInt()(key) % _hashTable.capacity();
	}

	void CheckCapacity()
	{
		size_t capacity = _hashTable.capacity();
		if (_size == capacity)
		{
			HashTable<K, V, KeyToInt> newHt(GetNextPrime(capacity));
			for (size_t bucketNo = 0; bucketNo < capacity; bucketNo++)
			{
				PNode pCur = _hashTable[bucketNo];
				while (pCur)
				{
					newHt.InsertEqual(pCur->_kv);
					pCur = pCur->_pNext;
				}
			}
			_hashTable.swap(newHt._hashTable);
		}
	}
private:
	vector<PNode> _hashTable;
	size_t _size;
};

void test()
{
	HashTable<int, int> ht;
	ht.InsertEqual(make_pair(1, 1));
	ht.InsertEqual(make_pair(5, 5));
	ht.InsertEqual(make_pair(15, 15));
	ht.InsertEqual(make_pair(15, 15));
	ht.InsertEqual(make_pair(35, 35));
	ht.InsertEqual(make_pair(9, 9));
	HashTable<int, int>::Iterator it = ht.Begin();
	if (!ht.Empty())
	{
		while (it != ht.End())
		{
			cout << it->first << " " ;
			cout << (*it).second << endl;
			it++;
		}
		cout << endl;
		cout << ht.BucketSize(5) << endl;
		cout << ht.BucketCount() << endl;
		cout << ht.Count(15) << endl;
	}
	it = ht.Begin();
	cout << ht.Erase(15) << endl;
	HashTable<int, int>::Iterator ret = ht.Find(1);
	ht.Erase(ret);
	cout << ht.Size() << endl;
	ht.Clear();

	HashTable<string, string, StringToInt> ht1;
	ht1.InsertUnique(make_pair("111", "111"));
	ht1.InsertUnique(make_pair("111", "111"));
	cout << ht1.FindORInsert("111") << endl;
}