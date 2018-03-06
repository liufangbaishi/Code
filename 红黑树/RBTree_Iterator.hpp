#pragma once
#include <iostream>
using namespace std;

enum COLOR { RED, BLACK };
template <class K, class V>
struct RBNode
{
	RBNode(const K& key = K(), const V& value = V(), const COLOR color = RED)
	: _pLeft(NULL)
	, _pRight(NULL)
	, _pParent(NULL)
	, _key(key)
	, _value(value)
	, _color(color)
	{}
	RBNode<K, V>* _pLeft;
	RBNode<K, V>* _pRight;
	RBNode<K, V>* _pParent;
	K _key;
	V _value;
	COLOR _color;
};

template <class K, class V, class Ref, class Ptr>
struct RBTreeIterator
{
private:
	typedef RBNode<K, V> Node;
	typedef Node* pNode;
	typedef RBTreeIterator<K, V, Ref, Ptr> Self;
public:
	RBTreeIterator()
		: _pNode(NULL)
	{}

	RBTreeIterator(pNode pnode)
		: _pNode(pnode)
	{}

	RBTreeIterator(Self& s)
		: _pNode(s._pNode)
	{}

	bool operator==(const Self& s)
	{
		return _pNode == s._pNode;
	}

	bool operator!=(const Self& s)
	{
		return _pNode != s._pNode;
	}

	Ptr operator->()
	{
		return &(_pNode->_key);
	}

	Ref operator*()
	{
		return _pNode->_key;
	}

	Self& operator++()
	{
		Increasement();
		return *this;
	}

	Self operator++(int)
	{
		Self tmp(*this);
		Increasement();
		return tmp;
	}

	Self& operator--()
	{
		Decreasement();
		return *this;
	}

	Self operator--(int)
	{
		Self tmp(*this);
		Decreasement();
		return tmp;
	}

private:
	void Increasement()
	{
		if (_pNode->_pRight)
		{
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
				_pNode = _pNode->_pLeft;
		}
		else
		{
			pNode pParent = _pNode->_pParent;
			while (_pNode == pParent->_pRight)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			if (_pNode->_pRight != pParent)
				_pNode = pParent;
		}
	}

	void Decreasement()
	{
		if (_pNode->_pParent->_pParent==_pNode && _pNode->_color==RED)
			_pNode = _pNode->_pRight;
		else if (_pNode->_pLeft)
		{
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
				_pNode = _pNode->_pRight;
		}
		else
		{
			pNode pParent = _pNode->_pParent;
			while (_pNode == pParent->_pLeft)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			_pNode = pParent;
		}
	}
private:
	pNode _pNode;
};

template <class K, class V>
class RBTree
{
	typedef RBNode<K, V> Node;
	typedef Node* pNode;
public:
	typedef RBTreeIterator<K, V, K&, K*> Iterator;
	RBTree()
	{
		_pHead = new Node();
		_pHead->_color = RED;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
		_pHead->_pParent = NULL;
	}

	pair<bool, pNode> Insert(const K& key, const V& value)
	{
		pNode& _pRoot = GetRoot();
		if (NULL == _pRoot)
		{
			_pRoot = new Node(key, value);
			_pRoot->_color = BLACK;
			_pRoot->_pParent = _pHead;
			_pHead->_pLeft = _pRoot;
			_pHead->_pRight = _pRoot;
			_pHead->_pParent = _pRoot;
			_count++;
			return pair<bool, pNode>(true, _pRoot);
		}
		pNode pCur = _pRoot;
		pNode pParent = NULL;
		while (pCur)
		{
			pParent = pCur;
			if (key < pCur->_key)
				pCur = pCur->_pLeft;
			else
				pCur = pCur->_pRight;
		}
		pCur = new Node(key, value);
		if (key < pParent->_key)
			pParent->_pLeft = pCur;
		else if (key > pParent->_key)
			pParent->_pRight = pCur;
		else
			return make_pair(false, (pNode)NULL);
		pCur->_pParent = pParent;
		//调节颜色
		while (pCur!=_pRoot && pParent->_color==RED)
		{
			pNode grandFather = pParent->_pParent;
			if (pParent == grandFather->_pLeft)
			{
				pNode uncle = grandFather->_pRight;
				if (uncle && uncle->_color == RED)//情况三
				{
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;
					pCur = grandFather;
					pParent = pCur->_pParent;
				}
				else
				{
					if (pCur == pParent->_pRight)//情况五
					{
						RotateL(pParent);
						swap(pParent, pCur);
					}
					pParent->_color = BLACK;//情况四
					grandFather->_color = RED;
					RotateR(grandFather);
				}
			}
			else
			{
				pNode uncle = grandFather->_pLeft;
				if (uncle && uncle->_color == RED)
				{
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;
					pCur = grandFather;
					pParent = pCur->_pParent;
				}
				else
				{
					if (pCur == pParent->_pLeft)
					{
						RotateR(pParent);
						swap(pParent, pCur);
					}
					pParent->_color = BLACK;
					grandFather->_color = RED;
					RotateL(grandFather);
				}
			}
		}
		_pRoot->_color = BLACK;
		_pHead->_pLeft = MinNode();
		_pHead->_pRight = MaxNode();
		_count++;
		return make_pair(true, pCur);
	}

	Iterator Begin()
	{
		return Iterator(_pHead->_pLeft);
	}

	Iterator End()
	{
		return Iterator(_pHead);
	}

	int Size()
	{
		return _count;
	}
private:
	pNode& GetRoot()
	{
		return _pHead->_pParent;
	}

	pNode MinNode()
	{
		if (NULL == _pHead->_pParent)
			return NULL;
		pNode pCur = _pHead->_pParent;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;
		return pCur;
	}

	pNode MaxNode()
	{
		if (NULL == _pHead->_pParent)
			return NULL;
		pNode pCur = _pHead->_pParent;
		while (pCur->_pRight)
			pCur = pCur->_pRight;
		return pCur;
	}
	void RotateL(pNode pParent)
	{
		pNode& _pRoot = GetRoot();
		pNode pSubR = pParent->_pRight;
		pNode pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;
		pNode pPParent = pParent->_pParent;
		pSubR->_pLeft = pParent;
		pParent->_pParent = pSubR;
		pSubR->_pParent = pPParent;
		if (pParent == _pRoot)
			_pRoot = pSubR;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
	}

	void RotateR(pNode pParent)
	{
		pNode& _pRoot = GetRoot();
		pNode pSubL = pParent->_pLeft;
		pNode pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pParent->_pLeft = pSubLR;
		pNode pPParent = pParent->_pParent;
		pSubL->_pRight = pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;
		if (pParent == _pRoot)
			_pRoot = pSubL;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}
private:
	pNode _pHead;
	int _count;
};
