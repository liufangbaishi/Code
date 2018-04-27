#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
//邻接矩阵
template <class V, class W, bool IsDirect = false>
class Graph
{
public:
	Graph(const V* arr, size_t size)
		: _v(arr, arr + size)
	{
		_edges.resize(size);
		for (size_t i = 0; i < size; i++)
			_edges[i].resize(size);
	}
	int GetIndex(const V& v)
	{
		for (size_t i = 0; i < _v.size(); i++)
		{
			if (_v[i] == v)
				return i;
		}
		assert(false);
		return -1;
	}

	void AddEdges(const V v1, const V v2, const W& weight)
	{
		size_t index1 = GetIndex(v1);
		size_t index2 = GetIndex(v2);

		_edges[index1][index2] = weight;
		if (!IsDirect)//无向图需要两次，有向图只需要一次  false为无向图
			_edges[index2][index1] = weight;
	}

	void Print()
	{
		for (size_t i = 0; i < _v.size(); i++)
		{
			printf("%c ", _v[i]);
			for (size_t j = 0; j < _v.size(); j++)
			{
				printf("%2d  ", _edges[i][j]);
			}
			cout << endl;
		}
	}
	size_t Dev(const V& v)
	{
		size_t index = GetIndex(v);
		size_t count = 0;//false为无向图，无向图度的计算是遍历一行，true是有向图，有向图度的计算：出度+入度
		for (size_t i = 0; i < _v.size(); i++)
		{
			if (_edges[index][i] > 0)
				count++;
			if (IsDirect && _edges[i][index] > 0)
				count++;
		}
		return count;
	}
private:
	vector<V> _v;
	vector<vector<W>> _edges;
};
void test()
{
	char *pStr = "ABCDE";
	Graph<char, int, true> g(pStr, strlen(pStr));
	g.AddEdges('A', 'D', 10);
	g.AddEdges('A', 'E', 20);
	g.AddEdges('B', 'C', 10);
	g.AddEdges('B', 'D', 20);
	g.AddEdges('B', 'E', 30);
	g.AddEdges('A', 'D', 10);
	g.AddEdges('C', 'E', 40);

	for (size_t i = 0; i < strlen(pStr); i++)
	{
		printf(" ");
		printf("%2c ", pStr[i]);
	}	
	cout << endl;
	g.Print();
	cout << "A点的度为：" << g.Dev('A') << endl;
	cout << "B点的度为：" << g.Dev('B') << endl;
	cout << "C点的度为：" << g.Dev('C') << endl;
	cout << "D点的度为：" << g.Dev('D') << endl;
	cout << "E点的度为：" << g.Dev('E') << endl;
}