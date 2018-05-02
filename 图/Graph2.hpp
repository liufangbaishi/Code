#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include "UnionFind.hpp"
#include <algorithm>
using namespace std;
//�ڽӱ�
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

template <class V, class W, bool IsDirect = false>//����ͼΪfalse������ͼΪtrue
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
		if (!IsDirect)//false ����ͼ
			_Add(dstIndex, srcIndex, weight);
	}

	size_t Dev(const V& v)
	{
		size_t count = 0;
		size_t index = GetIndex(v);
		pNode pCur = _linkEdges[index];
		while (pCur)//���������ͼ��ֱ�Ӽ���ȣ����������ͼ�ȼ������
		{
			count++;
			pCur = pCur->_pNext;
		}
		if (IsDirect)
		{
			for (size_t i = 0; i < _v.size(); i++)//��������ͼ�����
			{
				if (i != index)
				{
					pCur = _linkEdges[i];
					while (pCur)
					{
						if (pCur->_dst == index)//Ҳ����ֱ�ӱȽ϶���_v[pCur->_dst] == v
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
		vector<bool> visited(_v.size(), false);//����������Ϊtrue��Ĭ��Ϊfalse
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
		g._v = _v;//�½�һ��ͼ
		g._linkEdges.resize(_v.size());
		vector<LinkEdge*> edges;
		for (size_t i = 0; i < _v.size(); i++)
		{
			LinkEdge* pCur = _linkEdges[i];		
			while (pCur)
			{
				if (IsDirect || (!IsDirect && pCur->_src < pCur->_dst))//����ߵ�Ȩֵ������ͼֻ��Ҫ����һ�Σ�����src<dst
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
		sort(edges.begin(), edges.end(), Compare());//������ıߵ�Ȩֵ����С��������
		
		size_t count = _v.size() - 1;//��ǰ����ȡn-1����
		UnionFind u(_v.size());
		for (size_t i = 0; i < edges.size(); i++)
		{
			LinkEdge* pCur = edges[i];
			size_t srcRoot = u.FindRoot(pCur->_src);
			size_t dstRoot = u.FindRoot(pCur->_dst);
			if (srcRoot != dstRoot)//���������㲻��ͬһ�����ϣ��Ž��߼���
			{
				g._Add(pCur->_src, pCur->_dst, pCur->_weight);
				if (!IsDirect)//falseΪ����ͼ
					g._Add(pCur->_dst, pCur->_src, pCur->_weight);

				u.Union(pCur->_src, pCur->_dst);//�ϲ�
				count--;
				if (count == 0)
					break;
			}
		}
		if (count > 0)
			cout << "��С�������Ƿ�" << endl;
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