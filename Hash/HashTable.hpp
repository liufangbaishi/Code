// 静态的哈希表
// 缺陷：1. 不能动态的增加
// 2.字符串的查找
// 3.除留余数法素数问题
#pragma once

#include <iostream>
using namespace std;

#define MAX_SIZE 10
typedef enum State { EXIST, DELETE, EMPTY };
template <class K>
struct Elem
{
	K _key;
	State _state;
};

template <class K, bool IsLine = true>
class HashTable
{
public:
	HashTable()
		: _size(0)
	{
		for (size_t i = 0; i < MAX_SIZE; i++)
			_hashTable[i]._state = EMPTY;
	}

	bool Insert(const K& key)
	{
		if (_size * 10 / MAX_SIZE > 7)
			return false;

		size_t addr = HashFunc(key);
		size_t i = 1;
		while (_hashTable[addr]._state != EMPTY)
		{
			if (_hashTable[addr]._state == EXIST && key == _hashTable[addr]._key)
				return false;

			if (IsLine)
				LineCheck(addr);//线性探测
			else
				SecondCheck(addr, i++);//二次探查
		}
		_hashTable[addr]._key = key;
		_hashTable[addr]._state = EXIST;
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
private:
	size_t HashFunc(const K& key)
	{
		return key % MAX_SIZE;
	}

	void LineCheck(size_t& addr)
	{
		++addr;
		if (addr >= MAX_SIZE)
			addr = 0;
	}

	void SecondCheck(size_t& addr, size_t i)
	{
		addr = addr + ((i << 1) + 1);
		if (addr >= MAX_SIZE)
			addr %= MAX_SIZE;
	}
private:
	Elem<K> _hashTable[MAX_SIZE];
	size_t _size;
};

void test()
{
	int arr[] = { 12, 22, 33, 9, 29, 55 };
	HashTable<int> ht;
	if (ht.Empty())
	{
		for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		{
			ht.Insert(arr[i]);
		}
		cout << ht.Size() << endl;
		ht.Delete(22);
		ht.Insert(33);
		cout << ht.Size() << endl;
	}
}