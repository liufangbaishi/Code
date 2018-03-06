#pragma once
#include <iostream>
using namespace std;
template <class K, class V>
struct BSTreeNode
{
	BSTreeNode(const K& key, const V& value)
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
class BSTree
{
	typedef BSTreeNode<K, V> Node;
	typedef Node* pNode;
public:
	BSTree()
		: _pRoot(NULL)
	{}

	bool Insert_N(const K& key, const V& value)//非递归插入
	{
		if (NULL == _pRoot)
		{
			_pRoot = new Node(key, value);
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
	  pCur->_pParent=pParent;
		return true;
	}

	bool Insert(const K& key, const V& value)//递归插入
	{
		return _Insert(_pRoot, key, value);
	}

	void InOrder()//中序遍历
	{
		_InOrder(_pRoot);
	}

	//bool Delete_N(const K& key)//非递归删除
	//{
	//	if (NULL == _pRoot)//空树
	//		return false;
	//	pNode pDel = Find(key);
	//	if (pDel->_pLeft == NULL)//只有右子树
	//	{
	//		pNode pParent = pDel->_pParent;
	//		if (pDel == _pRoot)
	//			_pRoot = _pRoot->_pRight;
	//		else if (pDel == pParent->_pLeft)
	//			pParent->_pLeft = pDel->_pRight;
	//		else
	//			pParent->_pRight = pDel->_pRight;
	//		if (pDel->_pRight)//将要删除的结点的左孩子的双亲结点连接好
	//			pDel->_pRight->_pParent = pParent;
	//		delete pDel;
	//		pDel = NULL;
	//		return true;
	//	}
	//	else if (pDel->_pRight == NULL)//只有左子树
	//	{
	//		pNode pParent = pDel->_pParent;
	//		if (pDel == _pRoot)
	//			_pRoot = _pRoot->_pLeft;
	//		else if (pDel == pParent->_pRight)
	//			pParent->_pRight = pDel->_pLeft;
	//		else
	//			pParent->_pLeft = pDel->_pLeft;
	//		if (pDel->_pLeft)//将要删除的结点的左孩子的双亲结点连接好
	//			pDel->_pLeft->_pParent = pParent;
	//		delete pDel;
	//		pDel = NULL;
	//		return true;
	//	}
	//	else//左右子树都存在
	//	{
	//		pNode firstOfIn = pDel->_pRight;
	//		while (firstOfIn->_pLeft)
	//			firstOfIn = firstOfIn->_pLeft;
	//		pDel->_key = firstOfIn->_key;
	//		pDel->_value = firstOfIn->_value;

	//		pNode pParent = firstOfIn->_pParent;
	//		if (firstOfIn == pDel->_pRight)
	//		{
	//			pParent->_pRight = firstOfIn->_pRight;
	//			if (firstOfIn->_pRight)
	//				firstOfIn->_pRight->_pParent = pParent;
	//		}
	//		else
	//		{
	//			pParent->_pLeft = firstOfIn->_pLeft;
	//			if (firstOfIn->_pLeft)
	//				firstOfIn->_pLeft->_pParent = pParent;
	//		}
	//		delete firstOfIn;
	//		firstOfIn = NULL;
	//	}
	//	return false;
	//}

	bool Delete_N(const K& key)//非递归删除
	{
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
				else
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
				return true;
			}
		}
		return false;
	}

	bool Delete(K key)//递归删除
	{
		return _Delete(_pRoot, key);
	}

	pNode Find(K key)//查找结点
	{
		return _Find(_pRoot, key);
	}

	pNode BSTreeToList()
	{
		if (NULL == _pRoot)
			return NULL;
		pNode pHead = _pRoot;//定义链表的头结点
		while (pHead->_pLeft)
			pHead = pHead->_pLeft;
		pNode prev = NULL;
		_BSTreeToList(_pRoot, prev);
		return pHead;
	}
private:
	void _BSTreeToList(pNode pRoot, pNode& prev)
	{
		if (NULL == pRoot)
			return;
		_BSTreeToList(pRoot->_pLeft, prev);
		pRoot->_pLeft = prev;
		if (prev)
			prev->_pRight = pRoot;
		prev = pRoot;
		_BSTreeToList(pRoot->_pRight, prev);
	}

	bool _Insert(pNode& pRoot, const K& key, const V& value)
	{
		if (NULL == pRoot)
		{
			pRoot = new Node(key, value);
			return true;
		}
		
		if (key < pRoot->_key)
			return _Insert(pRoot->_pLeft, key, value);
		else if (key > pRoot->_key)
			return _Insert(pRoot->_pRight, key, value);
		else
			return false;
	}

	bool _Delete(pNode& pRoot, K key)
	{
		if (NULL == pRoot)
			return false;
		if (key < pRoot->_key)
			return _Delete(pRoot->_pLeft, key);
		else if (key> pRoot->_key)
			return _Delete(pRoot->_pRight, key);
		else
		{
			if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight)
			{
				delete pRoot;
				pRoot = NULL;
				return true;
			}
			else if (NULL == pRoot->_pLeft)
			{
				pNode pDel = pRoot;
				pRoot = pRoot->_pRight;
				delete pDel;
				pDel = NULL;
				return true;
			}
			else if (NULL == pRoot->_pRight)
			{
				pNode pDel = pRoot;
				pRoot = pRoot->_pLeft;
				delete pDel;
				pDel = NULL;
				return true;
			}
			else
			{
				pNode firstOfIn = pRoot->_pRight;
				while (firstOfIn->_pLeft)
					firstOfIn = firstOfIn->_pLeft;

				pRoot->_key = firstOfIn->_key;
				pRoot->_value = firstOfIn->_value;
				return _Delete(pRoot->_pRight, firstOfIn->_key);
			}
		}
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

	void _InOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << "<" << pRoot->_key << "," << pRoot->_value << ">" << endl;
			_InOrder(pRoot->_pRight);
		}
	}
private:
	pNode _pRoot;
};
