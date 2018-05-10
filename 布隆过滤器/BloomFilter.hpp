#pragma once
#include "comm.hpp"
#include "bitMap.hpp"
#include <iostream>

template <class K, class KToInt1 = KeyToInt1,
				   class KToInt2 = KeyToInt2, 
				   class KToInt3 = KeyToInt3, 
				   class KToInt4 = KeyToInt4, 
				   class KToInt5 = KeyToInt5>
class BloomFilter
{
public:
	BloomFilter(size_t size)//size表示人数，5个比特位表示一个人
		: _bmp(size * 10)
		, _size(0)
	{}

	bool Insert(const K& key)
	{
		size_t bitCount = _bmp.Size();//位图能存储bitCount个比特位
		size_t index1 = KToInt1()(key) % bitCount;//字符串转换成整型，转换后的数字可能大于位图的位数，所以要取模
		size_t index2 = KToInt2()(key) % bitCount;
		size_t index3 = KToInt3()(key) % bitCount;
		size_t index4 = KToInt4()(key) % bitCount;
		size_t index5 = KToInt5()(key) % bitCount;

		_bmp.Set(index1);//整型插入到位图中
		_bmp.Set(index2);
		_bmp.Set(index3);
		_bmp.Set(index4);
		_bmp.Set(index5);
		_size++;

		cout << index1 << " " << index2 << " " << index3 << " " << index4 << " " << index5;//打印索引，做测试	
		cout << endl;
		return true;
	}

	bool IsInBloomFilter(const K& key)
	{
		size_t bitCount = _bmp.Size();
		size_t index1 = KToInt1()(key) % bitCount;
		size_t index2 = KToInt2()(key) % bitCount;
		size_t index3 = KToInt3()(key) % bitCount;
		size_t index4 = KToInt4()(key) % bitCount;
		size_t index5 = KToInt5()(key) % bitCount;
		if (!_bmp.Test(index1))
			return false;//index1不在位图中，说明key不在其中
		if (!_bmp.Test(index2))
			return false;
		if (!_bmp.Test(index3))
			return false;
		if (!_bmp.Test(index4))
			return false;
		if (!_bmp.Test(index5))
			return false;
		return true;//五个索引表明都在，key才有可能在其中
	}

private:
	BitMap _bmp;//位图存储人的信息
	size_t _size;//表示存了几个人
};


void test()
{
	BloomFilter<string> b(5);
	b.Insert("小明");
	b.Insert("小黄");
	b.Insert("小花");
	b.Insert("小兰");
	b.Insert("小熊");
	b.Insert("小泽");
	if (b.IsInBloomFilter("小熊"))
		cout << "小熊在名单之中" << endl;
	if (!b.IsInBloomFilter("小王"))
		cout << "小王不在名单之中" << endl;
}