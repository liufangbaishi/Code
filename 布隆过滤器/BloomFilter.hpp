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
	BloomFilter(size_t size)//size��ʾ������5������λ��ʾһ����
		: _bmp(size * 10)
		, _size(0)
	{}

	bool Insert(const K& key)
	{
		size_t bitCount = _bmp.Size();//λͼ�ܴ洢bitCount������λ
		size_t index1 = KToInt1()(key) % bitCount;//�ַ���ת�������ͣ�ת��������ֿ��ܴ���λͼ��λ��������Ҫȡģ
		size_t index2 = KToInt2()(key) % bitCount;
		size_t index3 = KToInt3()(key) % bitCount;
		size_t index4 = KToInt4()(key) % bitCount;
		size_t index5 = KToInt5()(key) % bitCount;

		_bmp.Set(index1);//���Ͳ��뵽λͼ��
		_bmp.Set(index2);
		_bmp.Set(index3);
		_bmp.Set(index4);
		_bmp.Set(index5);
		_size++;

		cout << index1 << " " << index2 << " " << index3 << " " << index4 << " " << index5;//��ӡ������������	
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
			return false;//index1����λͼ�У�˵��key��������
		if (!_bmp.Test(index2))
			return false;
		if (!_bmp.Test(index3))
			return false;
		if (!_bmp.Test(index4))
			return false;
		if (!_bmp.Test(index5))
			return false;
		return true;//��������������ڣ�key���п���������
	}

private:
	BitMap _bmp;//λͼ�洢�˵���Ϣ
	size_t _size;//��ʾ���˼�����
};


void test()
{
	BloomFilter<string> b(5);
	b.Insert("С��");
	b.Insert("С��");
	b.Insert("С��");
	b.Insert("С��");
	b.Insert("С��");
	b.Insert("С��");
	if (b.IsInBloomFilter("С��"))
		cout << "С��������֮��" << endl;
	if (!b.IsInBloomFilter("С��"))
		cout << "С����������֮��" << endl;
}