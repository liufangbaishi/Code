#pragma once
#include "comm.hpp"
#include <iostream>
#include <vector>
using namespace std;
typedef enum State { EXIST, DELETE, EMPTY };

template <class K>
struct Elem
{
	K _key;
	State _state;
};

template <class K, class KeyToInt, bool IsLine = true>
class HashTable
{
public:
	HashTable(size_t capacity = 4)
	{
		//capacity = GetNextPrime(capacity);
		_hashTable.resize(capacity);

		for (size_t i = 0; i < capacity; i++)
			_hashTable[i]._state = EMPTY;
		_size = 0;
		_capacity = capacity;
	}

	bool Insert(const K& key)
	{
		CheckCapacity();

		size_t addr = HashFunc(key);
		size_t i = 1;
		
		while (_hashTable[addr]._state != EMPTY)
		{
			if (_hashTable[addr]._key == key && _hashTable[addr]._state == EXIST)
				return false;

			if (IsLine)
				LineCheck(addr);
			else
				SecondCheck(addr, i++);
		}
		_hashTable[addr]._state = EXIST;
		_hashTable[addr]._key = key;
		_size++;
		return true;
	}

	bool Delete(const K& key)
	{
		int ret = Find(key);
		if (ret == -1)
			return false;//不存在

		_size--;
		_hashTable[ret]._state = DELETE;
		return true;
	}

	int Find(const K& key)
	{
		size_t addr = HashFunc(key);
		size_t i = 1;
		while (_hashTable[addr]._state != EMPTY)
		{
			if (_hashTable[addr]._state == EXIST && _hashTable[addr]._key == key)
				return addr;

			if (IsLine)
				LineCheck(addr);
			else
				SecondCheck(addr, i++);
		}
		return -1;
	}

	size_t Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	~HashTable()
	{
		_hashTable.~vector();
		_size = 0;
		_capacity = 0;
	}
private:
	void CheckCapacity()
	{
		if (_size * 10 / _capacity >= 7)
		{
			size_t newCapacity = GetNextPrime(_capacity);
			HashTable<K, KeyToInt> newHt(newCapacity);
			for (size_t i = 0; i < _capacity; i++)
			{
				if (_hashTable[i]._state == EXIST)
					newHt.Insert(_hashTable[i]._key);
			}
			_capacity = newCapacity;
			Swap(newHt);
		}
	}

	void Swap(HashTable<K, KeyToInt>& ht)
	{
		swap(_hashTable, ht._hashTable);
		swap(_capacity, ht._capacity);
		swap(_size, ht._size);
	}

	size_t HashFunc(const K& key)
	{
		return KeyToInt()(key) % _capacity;
	}

	void LineCheck(size_t& addr)
	{
		++addr;
		if (addr >= _capacity)
			addr = 0;
	}

	void SecondCheck(size_t& addr, size_t i)
	{
		addr = addr + ((i << 1) + 1);
		if (addr >= _capacity)
			addr %= _capacity;
	}
private:
	vector<Elem<K>> _hashTable;
	size_t _size;
	size_t _capacity;
};

void test()
{
	HashTable<string, StringToInt/*KeyToIntDef<string>*/> ht1;
	ht1.Insert("111");
	ht1.Insert("222");
	ht1.Insert("333");
	ht1.Insert("abc");
	ht1.Insert("你好");
	cout << ht1.Size() << endl;

	if (ht1.Find("111") != -1)
		cout << "找到了" << endl;
	else
		cout << "没有找到" << endl;
	ht1.Delete("333");
	cout << ht1.Size() << endl;
}