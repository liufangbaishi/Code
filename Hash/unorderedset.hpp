#pragma once
#include "HashBucket.hpp"
template <class K, class KeyToInt = KeyToIntDef<K>>
class UnorderedSet
{
public:
	typename typedef HashTable<K, K, KeyToInt>::Iterator Iterator;
	UnorderedSet()
		: _ht()
	{}

	pair<Iterator, bool> Insert(const K& key)
	{
		return _ht.InsertUnique(make_pair(key, K()));
	}

	bool Erase(const K& key)
	{
		size_t ret = _ht.Erase(key);
		if (ret > 0)
			return true;
		else
			return false;
	}

	Iterator Begin()
	{
		return _ht.Begin();
	}

	Iterator End()
	{
		return _ht.End();
	}

	size_t Size()
	{
		return _ht.Size();
	}

	bool Empty()
	{
		return _ht.Empty();
	}

	void Clear()
	{
		return _ht.Clear();
	}

	Iterator Find()
	{
		return _ht.Find();
	}

	size_t Count(const K& key)
	{
		return _ht.Count();
	}

	size_t BucketCount()
	{
		return _ht.BucketCount();
	}

	size_t BucketSize(size_t bucketNo)
	{
		return _ht.BucketSize(bucketNo);
	}

	~UnorderedSet()
	{
		_ht.~HashTable();
	}
private:
	HashTable<K, K, KeyToInt> _ht;
};

#include <string>
using namespace std;
void Test()
{
	UnorderedSet<string, StringToInt> m;
	m.Insert("111");
	m.Insert("222");
	m.Insert("333");
	m.Insert("111");
	m.Insert("444");
	m.Erase("111");
	UnorderedSet<string, StringToInt>::Iterator it = m.Begin();
	while (it != m.End())
	{
		cout << (*it).first << " ";
		it++;
	}
	cout << endl;
	cout << "5号:";
	cout << m.BucketSize(5) << endl;
	cout << "桶个数:";
	cout << m.BucketCount() << endl;
	cout << "元素个数：" << m.Size() << endl;
	m.Clear();
}