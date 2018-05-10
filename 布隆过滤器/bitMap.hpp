#pragma once
#include <vector>
#include <iostream>
using namespace std;

class BitMap
{
public:
	BitMap(size_t bitSet = 10)
		: _bitCount(bitSet)
	{
		_bitSet.resize((bitSet >> 5) + 1);//����5λ�����ǳ���32����bit��λ��ת���ֽ���
	}

	void Set(size_t whichBit) //��1
	{
		size_t index = whichBit >> 5;
		if (whichBit < _bitCount)
			_bitSet[index] |= 1 << (whichBit % 32);//A|0=A 0|1=1
	}

	void ReSet(size_t whichBit) //�ָ�0
	{
		size_t index = whichBit >> 5;
		if (whichBit < _bitCount)
			_bitSet[index] &= ~(1 << (whichBit % 32));//A&1=A 1&0=0   
		//Ҳ�����������ͬΪ0������Ϊ1  A^0=A 1^1=0
	}

	bool Test(size_t whichBit)//0����0,1���ط�0
	{
		size_t index = whichBit >> 5;
		if (whichBit < _bitCount)
			return _bitSet[index] & (1 << (whichBit % 32));//0&1=0 1&1=1
		cout << "����λ������" << endl;
		return false;
	}

	size_t Count()const //1�ĸ��� 
	{
		char* pBitCount = "\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4";
		size_t count = 0;
		for (size_t i = 0; i < _bitSet.size(); i++)
		{
			int value = _bitSet[i];
			int j = 0;
			while (j < sizeof(int))//j<4  һ��һ���ֽ�
			{
				count += pBitCount[value & 0x0F]; //ȡ����λ & 0000 1111
				value >>= 4;
				count += pBitCount[value & 0x0F]; //��ȡ��λ
				value >>= 4;
				j++;
			}
		}
		return count;
	}

	size_t Size()const
	{
		return _bitCount;
	}
private:
	vector<int> _bitSet;
	size_t _bitCount;
};
