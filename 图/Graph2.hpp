#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include "UnionFind.hpp"
#include <algorithm>
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
	Graph()
	{}

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
						if (pCur->_dst == index)//也可以直接比较顶点_v[pCur->_dst] == v
							count++;
						pCur = pCur->_pNext;
					}
				}
			}
		}
		return count;
	}

	void Print()
	{
		for(size_t index = 0; index < _v.size(); index++)
		{
			pNode pCur = _linkEdges[index];
			cout << _v[index] << ": ";
			while (pCur)
			{
				cout << _v[pCur->_src] << "->" << _v[pCur->_dst] << " ";
				pCur = pCur->_pNext;
			}
			cout << endl;
		}
	}

	void BFS(const V& v)
	{
		queue<int> q;
		vector<bool> visited(_v.size(), false);//遍历过的置为true，默认为false
		size_t index = GetIndex(v);
		q.push(index);
		_BFS(q, visited);
		for (size_t i = 0; i < _v.size(); i++)
		{
			if (visited[i] == false)
			{
				q.push(i);
				_BFS(q, visited);
			}
		}
		cout << endl;
	}

	void DFS(const V& v)
	{
		size_t index = GetIndex(v);
		vector<bool> visited(_v.size(), false);
		_DFS(index, visited);

		for (size_t i = 0; i < _v.size(); i++)
		{
			if (visited[i] == false)
				_DFS(i, visited);
		}
		cout << endl;
	}

	typedef Graph<V, W, IsDirect> Self;
	typedef Node LinkEdge;
	Self Kruskal()
	{
		Self g;
		g._v = _v;//新建一个图
		g._linkEdges.resize(_v.size());
		vector<LinkEdge*> edges;
		for (size_t i = 0; i < _v.size(); i++)
		{
			LinkEdge* pCur = _linkEdges[i];		
			while (pCur)
			{
				if (IsDirect || (!IsDirect && pCur->_src < pCur->_dst))//保存边的权值。无向图只需要保存一次，保存src<dst
					edges.push_back(pCur);
				pCur = pCur->_pNext;
			}		
		}

		class Compare
		{
		public:
			bool operator()(const LinkEdge* left, const LinkEdge* right)
			{
				return left->_weight < right->_weight;
			}
		};
		sort(edges.begin(), edges.end(), Compare());//将保存的边的权值，从小到大排序
		
		size_t count = _v.size() - 1;//从前往后取n-1条边
		UnionFind u(_v.size());
		for (size_t i = 0; i < edges.size(); i++)
		{
			LinkEdge* pCur = edges[i];
			size_t srcRoot = u.FindRoot(pCur->_src);
			size_t dstRoot = u.FindRoot(pCur->_dst);
			if (srcRoot != dstRoot)//若两个顶点不在同一个集合，才将边加上
			{
				g._Add(pCur->_src, pCur->_dst, pCur->_weight);
				if (!IsDirect)//false为无向图
					g._Add(pCur->_dst, pCur->_src, pCur->_weight);

				u.Union(pCur->_src, pCur->_dst);//合并
				count--;
				if (count == 0)
					break;
			}
		}
		if (count > 0)
			cout << "最小生成树非法" << endl;
		return g;
	}
private:
	void _DFS(int index, vector<bool>& visited)
	{
		cout << _v[index] << " ";
		visited[index] = true;
		pNode pCur = _linkEdges[index];
		while (pCur)
		{
			if (visited[pCur->_dst] == false)
				_DFS(pCur->_dst, visited);
			pCur = pCur->_pNext;
		}
	}

	void _BFS(queue<int>& q, vector<bool>& visited)
	{
		while (!q.empty())
		{
			size_t index = q.front();
			q.pop();
			if (visited[index] == true)
				continue;
			cout << _v[index] << " ";
			visited[index] = true;
			pNode pCur = _linkEdges[index];
			while (pCur)
			{
				if (visited[pCur->_dst] == false)
					q.push(pCur->_dst);
				pCur = pCur->_pNext;
			}
		}
	}

	void _Add(const size_t src, const size_t dst, const W& weight)
	{
		pNode pNew = new Node(weight, src, dst);
		pNode pCur = _linkEdges[src];

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
	Graph<char, int> g(pStr, strlen(pStr));
	g.AddEdges('E', 'A', 40);
	g.AddEdges('A', 'B', 50);
	g.AddEdges('A', 'D', 10);
	g.AddEdges('B', 'C', 100);
	g.AddEdges('C', 'D', 20);
	g.AddEdges('D', 'E', 30);
	

	//g.Print();
	//g.BFS('A');
	g.DFS('A');

	//Graph<char, int, true> k = g.Kruskal();
	//k.Print();
}