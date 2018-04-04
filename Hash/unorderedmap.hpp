#pragma once
#include "HashBucket.hpp"
template <class K, class V, class KeyToInt = KeyToIntDef<K>>
class UnorderedMap
{
public:
	typename typedef HashTable<K, V, KeyToInt>::Iterator Iterator;
	UnorderedMap()
		: _ht()
	{}

	pair<Iterator, bool> Insert(const pair<K, V>& kv)
	{
		return _ht.InsertUnique(kv);
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

	V& operator[](const K& key)
	{
		return _ht.FindORInsert(key);
	}

	~UnorderedMap()
	{
		_ht.~HashTable();
	}
private:
	HashTable<K, V, KeyToInt> _ht;
};

#include <string>
using namespace std;
void Test()
{
	UnorderedMap<string, string, StringToInt> m;
	m.Insert(make_pair("111", "111"));
	m.Insert(make_pair("222", "222"));
	m.Insert(make_pair("333", "333"));
	m.Insert(make_pair("111", "444"));
	m.Insert(make_pair("444", "444"));
	cout << m["444"] << endl;
	cout << m["555"] << endl;
	m.Erase("111");
	UnorderedMap<string, string, StringToInt>::Iterator it = m.Begin();
	while (it != m.End())
	{
		cout << (*it).first << "->" << it->second << endl;
		it++;
	}
	cout << endl;
	cout << "5号:";
	cout << m.BucketSize(5) << endl;
	cout << "桶个数:";
	cout << m.BucketCount() << endl;
	cout << "元素个数：" << m.Size() << endl;
}