#pragma once
#include <vector>
#include <iostream>
using namespace std;
//邻接表
template <class W>
struct Node
{
	Node(const W& weight, size_t src, size_t dst)
	: _weight(weight)
	, _src(src)
	, _dst(dst)
	, _pNext(NULL)
	{}

	W _weight;
	size_t _src;
	size_t _dst;
	Node* _pNext;
};

template <class V, class W, bool IsDirect = false>//无向图为false；有向图为true
class Graph
{
	typedef Node<W> Node;
	typedef Node* pNode;
public:
	Graph(const V* arr, size_t size)
		: _v(arr, arr + size)
	{
		_linkEdges.resize(size);
	}

	int GetIndex(const V& v)
	{
		for (size_t i = 0; i < _v.size(); i++)
		{
			if (_v[i] == v)
				return i;
		}
		return -1;
	}

	void AddEdges(const V& v1, const V& v2, const W& weight)
	{
		size_t srcIndex = GetIndex(v1);
		size_t dstIndex = GetIndex(v2);

		_Add(srcIndex, dstIndex, weight);
		if (!IsDirect)//false 无向图
			_Add(dstIndex, srcIndex, weight);
	}

	size_t Dev(const V& v)
	{
		size_t count = 0;
		size_t index = GetIndex(v);
		pNode pCur = _linkEdges[index];
		while (pCur)//如果是无向图，直接计算度，如果是有向图先计算出度
		{
			count++;
			pCur = pCur->_pNext;
		}
		if (IsDirect)
		{
			for (size_t i = 0; i < _v.size(); i++)//计算有向图的入度
			{
				if (i != index)
				{
					pCur = _linkEdges[i];
					while (pCur)
					{
						if (pCur->_dst == index)
							count++;
						pCur = pCur->_pNext;
					}
				}
			}
		}
		return count;
	}
private:
	void _Add(const size_t src, const size_t dst, const W& weight)
	{
		pNode pNew = new Node(weight, src, dst);
		pNode pCur = _linkEdges[src];
		while (pCur)
		{
			if(pCur->_weight == weight)
				return;
			pCur = pCur->_pNext;
		}
		pNew->_pNext = _linkEdges[src];
		_linkEdges[src] = pNew;
	}
private:
	vector<V> _v;
	vector<pNode> _linkEdges;
};

void test()
{
	char *pStr = "ABCDE";
	Graph<char, int, true> g(pStr, strlen(pStr));
	g.AddEdges('A', 'B', 10);
	g.AddEdges('B', 'D', 20);
	g.AddEdges('B', 'C', 10);
	g.AddEdges('C', 'D', 20);
	g.AddEdges('D', 'E', 30);
	g.AddEdges('E', 'A', 40);
	cout << g.Dev('A') << endl;
	cout << g.Dev('B') << endl;
	cout << g.Dev('C') << endl;
	cout << g.Dev('D') << endl;
	cout << g.Dev('E') << endl;
}