#pragma once
#include <vector>
using namespace std;
class UnionFind
{
public:
	UnionFind(size_t size)
		: _set(size, -1)//���캯��
	{}
	void Union(int x1, int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		if (root1 != root2)
		{
			_set[root1] += _set[root2];
			_set[root2] = root1;
		}
	}
	size_t Count()// �ϲ���ĸ���
	{
		size_t count = 0;
		for (size_t i = 0; i < _set.size(); i++)
		{
			if (_set[i] < 0)
				count++;
		}
		return count;
	}
	int FindRoot(int x)// ���Ҹ����
	{
		while (_set[x] >= 0)
			x = _set[x];
		return x;
	}
private:
	vector<int> _set;
};