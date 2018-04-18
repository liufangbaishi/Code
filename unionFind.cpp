#include <iostream>
#include <vector>
using namespace std;
class UnionFind
{
public:
	UnionFind(size_t size)
		: _set(size, -1)//���캯��
	{
		// _set.resize(size, -1);//��-1��ʼ��   3�ַ���������ʵ��
		// _set.assign(size, -1);
	}
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
private:
	int FindRoot(int x)// ���Ҹ����
	{
		while (_set[x] >= 0)
			x = _set[x];
		return x;
	}
private:
	vector<int> _set;
};

size_t friends(const int n, const int m, int r[][2])
{
	UnionFind u(n + 1);
	for (int i = 0; i < m; i++)
		u.Union(r[i][0], r[i][1]);
	return u.Count() - 1;
}
int main()
{
	const int m = 3;
	const int n = 5;
	// vector<vector<int>> v = { { 1, 2 }, { 2, 3 }, { 4, 5 } };
	int r[3][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 } };
	cout << "����Ȧ����:" << friends(n, m, r) << endl;
	return 0;
}