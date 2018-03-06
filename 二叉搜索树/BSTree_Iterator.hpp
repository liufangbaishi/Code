#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
template <class K, class V>
struct BSTreeNode
{
	BSTreeNode(const K& key = K(), const V& value = V())
	: _key(key)
	, _value(value)
	, _pLeft(NULL)
	, _pRight(NULL)
	, _pParent(NULL)
	{}
	BSTreeNode<K, V>* _pLeft;
	BSTreeNode<K, V>* _pRight;
	BSTreeNode<K, V>* _pParent;
	K _key;
	V _value;
};

template <class K, class V>
struct BSTIterator
{
	typedef BSTreeNode<K, V>* PNode;
	typedef BSTIterator<K, V> Self;
	BSTIterator()
		: _pNode(NULL)
		, _pHead(NULL)
	{}
	BSTIterator(PNode pNode, PNode pHead = PNode())
		: _pNode(pNode)
		, _pHead(pHead)
	{}
	BSTIterator(const Self& s)
		: _pNode(s._pNode)
		, _pHead(s._pHead)
	{}
	bool operator==(const Self& s)
	{
		return _pNode == s._pNode;
	}
	bool operator!=(const Self& s)
	{
		return _pNode != s._pNode;
	}
	K operator*()
	{
		return _pNode->_key;
	}
	PNode operator->()
	{
		return _pNode;
	}
	Self& operator++()
	{
		Increase();
		return *this;
	}
	Self operator++(int)
	{
		Self temp(*this);
		Increase();
		return temp;
	}
	Self& operator--()
	{
		Decrease();
		return *this;
	}
	Self operator--(int)
	{
		Self temp(*this);
		Decrease();
		return temp;
	}
	void Increase()
	{
		assert(_pNode != _pHead);//头结点之后增加，报错
		if (_pNode->_pRight)
		{
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
				_pNode = _pNode->_pLeft;
		}
		else
		{
			PNode pParent = _pNode->_pParent;
			while (_pNode == pParent->_pRight)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			if (_pNode->_pRight != pParent)
				_pNode = pParent;//9->头结点
		}
	}
	void Decrease()
	{
		assert(_pNode != _pHead->_pLeft);//最小的元素的结点之后减小，报错
		if (_pNode == _pHead)//头结点->9
			_pNode = _pNode->_pRight;
		else if (_pNode->_pLeft)
		{
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
				_pNode = _pNode->_pRight;
		}
		else
		{
			PNode pParent = _pNode->_pParent;
			while (_pNode == pParent->_pLeft)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			_pNode = pParent;
		}
	}
private:
	PNode _pNode;
	PNode _pHead;
};

template <class K, class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
	typedef Node* pNode;	
public:
	typedef BSTIterator<K, V> Iterator;
	BSTree()
	{
		_pHead = new Node();
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
		_pHead->_pParent = NULL;
	}

	pNode& GetRoot()//获取根结点
	{
		assert(_pHead);
		return _pHead->_pParent;
	}
	
	bool Insert(const K& key, const V& value)
	{
		pNode& _pRoot = GetRoot();
		if (NULL == _pRoot)
		{
			_pRoot = new Node(key, value);
			_pRoot->_pParent = _pHead;
			_pHead->_pParent = _pRoot;
			_pHead->_pLeft = _pRoot;
			_pHead->_pRight = _pRoot;
			return true;
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
			return false;
		pCur->_pParent = pParent;

		_pHead->_pLeft = MinNode();
		_pHead->_pRight = MaxNode();
		return true;
	}

	bool Delete(const K& key)
	{
		pNode& _pRoot = GetRoot();
		if (_pRoot == NULL)
			return false;

		pNode pDel = _pRoot;
		pNode pParent = NULL;
		while (pDel)
		{
			if (key < pDel->_key)
				pDel = pDel->_pLeft;
			else if (key > pDel->_key)
				pDel = pDel->_pRight;
			else
			{
				pParent = pDel->_pParent;
				if (pDel->_pLeft == NULL)//只有右子树
				{
					if (_pRoot == pDel)
						_pRoot = _pRoot->_pRight;
					else
					{
						if (pDel == pParent->_pLeft)
							pParent->_pLeft = pDel->_pRight;
						else
							pParent->_pRight = pDel->_pRight;
					}
					if (pDel->_pRight)
						pDel->_pRight->_pParent = pParent;
					delete pDel;
					pDel = NULL;
				}
				else if (pDel->_pRight == NULL)//只有左子树
				{
					if (_pRoot == pDel)
						_pRoot = _pRoot->_pLeft;
					else
					{
						if (pDel == pParent->_pRight)
							pParent->_pRight = pDel->_pLeft;
						else
							pParent->_pLeft = pDel->_pLeft;
					}
					if (pDel->_pLeft)
						pDel->_pLeft->_pParent = pParent;
					delete pDel;
					pDel = NULL;
				}
				else//左右子树都存在
				{
					pNode firstOfIn = pDel->_pRight;
					while (firstOfIn->_pLeft)
						firstOfIn = firstOfIn->_pLeft;
					pDel->_key = firstOfIn->_key;
					pDel->_value = firstOfIn->_value;

					pNode pParent = firstOfIn->_pParent;
					if (firstOfIn == pDel->_pRight)
					{
						pParent->_pRight = firstOfIn->_pRight;
						if (firstOfIn->_pRight)
							firstOfIn->_pRight->_pParent = pParent;
					}
					else
					{
						pParent->_pLeft = firstOfIn->_pLeft;
						if (firstOfIn->_pLeft)
							firstOfIn->_pLeft->_pParent = pParent;
					}
					delete firstOfIn;
					firstOfIn = NULL;
				}
				_pHead->_pLeft = MinNode();
				_pHead->_pRight = MaxNode();
				return true;
			}	
		}
		return false;
	}

	Iterator Begin()
	{
		return Iterator(_pHead->_pLeft, _pHead);
	}

	Iterator End()
	{
		return Iterator(_pHead, _pHead);
	}

	pNode Find(K key)//查找结点
	{
		return _Find(_pHead->_pParent, key);
	}	
private:
	pNode MinNode()
	{
		pNode pCur = GetRoot();
		if (NULL == pCur)
			return NULL;

		while (pCur->_pLeft)
			pCur = pCur->_pLeft;
		return pCur;
	}

	pNode MaxNode()
	{ 
		pNode pCur = GetRoot();
		if (NULL == pCur)
			return NULL;

		while (pCur->_pRight)
			pCur = pCur->_pRight;
		return pCur;
	}

	pNode _Find(pNode pRoot, K key)
	{
		if (NULL == pRoot)
			return NULL;

		if (key == pRoot->_key)
			return pRoot;
		else if (key < pRoot->_key)
			return _Find(pRoot->_pLeft, key);
		else
			return _Find(pRoot->_pRight, key);
	}
private:
	pNode _pHead;
};