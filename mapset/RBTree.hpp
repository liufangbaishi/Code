#pragma once
#include <iostream>
using namespace std;
#include <assert.h>
enum COLOR {RED, BLACK};
template <class Value>
struct RBNode
{
	RBNode(const Value& v = Value(), const COLOR color = RED)
		: _value(v)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _color(color)
	{}
	Value _value;
	RBNode<Value> *_pLeft;
	RBNode<Value> *_pRight;
	RBNode<Value> *_pParent;
	COLOR _color;
};
     // RBIterator<Value, Value&, Value*> 
template <class Value, class Ref, class Ptr>
struct RBIterator
{
	typedef RBNode<Value> Node;
	typedef RBIterator<Value, Ref, Ptr> Self;
	RBIterator()
		: _pNode(NULL)
	{}

	RBIterator(Node* node)
		: _pNode(node)
	{}

	RBIterator(const Self& s)
		: _pNode(s._pNode)
	{}

	RBIterator operator=(const Self& s)
	{
		if (&s != this)
		{
			_pNode = s._pNode;
		}
		return *this;
	}

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
		return &(_pNode->_value);
	}

	Ref operator*()
	{
		return _pNode->_value;
	}

	Self& operator++()
	{
		Increase();
		return *this;
	}

	Self operator++(int)
	{
		Self tmp(*this);
		Increase();
		return tmp;
	}

	Self& operator--()
	{
		Decrease();
		return *this;
	}

	Self operator--(int)
	{
		Self tmp(*this);
		Decrease();
		return tmp;
	}
private:
	void Increase()
	{
		assert(_pNode);
		if (_pNode->_pRight)
		{
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
				_pNode = _pNode->_pLeft;
		}
		else
		{
			Node* pParent = _pNode->_pParent;
			while (pParent->_pRight == _pNode)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			if (_pNode->_pRight != pParent)
				_pNode = pParent;
		}
	}
	void Decrease()
	{
		assert(_pNode);
		if (_pNode->_pParent->_pParent == _pNode && _pNode->_color == RED)
			_pNode = _pNode->_pRight;
		else if (_pNode->_pLeft)
		{
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
				_pNode = _pNode->_pRight;
		}
		else
		{
			Node* pParent = _pNode->_pParent;
			while (pParent->_pLeft == _pNode)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			_pNode = pParent;
		}
	}
private:
	Node* _pNode;
};


template <class K, class V, class KeyOfValue>
class RBTree
{
	typedef RBNode<V> Node;
	typedef Node* pNode;
	typedef V Value;
public:
	typedef RBIterator<Value, Value&, Value*> Iterator;
	RBTree()
	{
		_pHead = new Node();
		_pHead->_color = RED;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}
	Iterator Begin()
	{
		return _pHead->_pLeft;
	}
	Iterator End()
	{
		return _pHead;
	}
	pair<bool, Iterator> Insert(const Value& v)
	{
		pNode& _pRoot = GetRoot();
		if (_pRoot == NULL)
		{
			_pRoot = new Node(v);
			_pRoot->_color = BLACK;
			_pRoot->_pParent = _pHead;
			_pHead->_pLeft = _pRoot;
			_pHead->_pRight = _pRoot;
			_pHead->_pParent = _pRoot;
			_count++;
			return pair<bool, Iterator>(true, Iterator(_pRoot));
		}

		KeyOfValue keyofvalue;
		pNode cur = _pRoot;
		pNode parent = NULL;
		while (cur)
		{
			if (keyofvalue(cur->_value)  < keyofvalue(v))
			{
				parent = cur;
				cur = cur->_pRight;
			}
			else if (keyofvalue(cur->_value) > keyofvalue(v))
			{
				parent = cur;
				cur = cur->_pLeft;
			}
			else
				return make_pair(false, Iterator(cur));
		}
		cur = new Node(v);
		if (keyofvalue(v) < keyofvalue(parent->_value))
			parent->_pLeft = cur;
		else 
			parent->_pRight = cur;
		cur->_pParent = parent;
		//调节颜色
		while (cur != _pRoot && parent->_color == RED)
		{
			pNode grandFather = parent->_pParent;
			if (parent == grandFather->_pLeft)
			{
				pNode uncle = grandFather->_pRight;
				if (uncle && uncle->_color == RED)//情况三
				{
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;
					cur = grandFather;
					parent = cur->_pParent;
				}
				else
				{
					if (cur == parent->_pRight)//情况五
					{
						RotateL(parent);
						swap(parent, cur);
					}
					parent->_color = BLACK;//情况四
					grandFather->_color = RED;
					RotateR(grandFather);
				}
			}
			else
			{
				pNode uncle = grandFather->_pLeft;
				if (uncle && uncle->_color == RED)
				{
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;
					cur = grandFather;
					parent = cur->_pParent;
				}
				else
				{
					if (cur == parent->_pLeft)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					parent->_color = BLACK;
					grandFather->_color = RED;
					RotateL(grandFather);
				}
			}
		}
		_pRoot->_color = BLACK;
		_pHead->_pLeft = MinNode();
		_pHead->_pRight = MaxNode();
		_count++;
		return make_pair(true, Iterator(cur));
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
			pSubLR->_pParent = pParent;
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