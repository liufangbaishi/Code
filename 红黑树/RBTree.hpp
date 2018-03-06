//#pragma once
//#include <iostream>
//using namespace std;
//enum COLOR { RED, BLACK };
//template <class K, class V>
//struct RBNode
//{
//	RBNode(const K& key, const V& value, const COLOR color = RED)
//	: _pLeft(NULL)
//	, _pRight(NULL)
//	, _pParent(NULL)
//	, _key(key)
//	, _value(value)
//	, _color(color)
//	{}
//	RBNode<K, V>* _pLeft;
//	RBNode<K, V>* _pRight;
//	RBNode<K, V>* _pParent;
//	K _key;
//	V _value;
//	COLOR _color;
//};
//
//template < class K, class V>
//class RBTree
//{
//	typedef RBNode<K, V> Node;
//	typedef Node* pNode;
//public:
//	RBTree()
//		: _pRoot(NULL)
//	{}
//
//	bool Insert(const K& key, const V& value)
//	{
//		if (NULL == _pRoot)//������ֱ�Ӳ���
//		{
//			_pRoot = new Node(key, value, BLACK);
//			return true;
//		}
//
//		pNode pCur = _pRoot;//�ǿ�����(1)���Ҵ�����Ľ���λ��
//		pNode pParent = NULL;
//		while (pCur)
//		{
//			if (key < pCur->_key)
//			{
//				pParent = pCur;
//				pCur = pCur->_pLeft;
//			}
//			else
//			{
//				pParent = pCur;
//				pCur = pCur->_pRight;
//			}
//		}
//		pCur = new Node(key, value);//(2)������
//		if (key < pParent->_key)
//			pParent->_pLeft = pCur;
//		else if (key > pParent->_key)
//			pParent->_pRight = pCur;
//		else
//			return false;
//		pCur->_pParent = pParent;
//
//		while (_pRoot != pCur && pParent->_color == RED)//(3)����
//		{
//			pNode grandFather = pParent->_pParent;
//			if (pParent == grandFather->_pLeft)
//			{
//				pNode uncle = grandFather->_pRight;
//
//				if (uncle && uncle->_color == RED)//�����
//				{
//					pParent->_color = BLACK;
//					uncle->_color = BLACK;
//					grandFather->_color = RED;
//					pCur = grandFather;
//					pParent = pCur->_pParent;
//				}
//				else
//				{
//					if (pCur == pParent->_pRight)//�������Ժϲ��������
//					{
//						RotateL(pParent);
//						swap(pCur, pParent);
//					}
//					pParent->_color = BLACK;//�����
//					grandFather->_color = RED;
//					RotateR(grandFather);
//				}
//			}
//			else
//			{
//				pNode uncle = grandFather->_pLeft;
//
//				if (uncle && uncle->_color == RED)//�����
//				{
//					pParent->_color = BLACK;
//					uncle->_color = BLACK;
//					grandFather->_color = RED;
//					pCur = grandFather;
//					grandFather = pCur->_pParent;
//				}
//				else
//				{
//					if (pCur == pParent->_pLeft)
//					{
//						RotateR(pParent);
//						swap(pCur, pParent);
//					}
//					pParent->_color = BLACK;
//					grandFather->_color = RED;
//					RotateL(grandFather);
//				}
//			}
//		}
//		_pRoot->_color = BLACK;
//		return true;
//	}
//
//	void InOrder()
//	{
//		return _InOrder(_pRoot);
//	}
//
//	bool IsCheck()//���ں�����ļ��飬���ǿ���ͨ�����������еĺ��������м���
//	{
//		if (NULL == _pRoot)
//			return true;
//
//		if (_pRoot->_color == RED)//��������2
//		{
//			cout << "�������ɫ���Ǻ�ɫ" << endl;
//			return false;
//		}
//
//		pNode pCur = _pRoot;
//		int blackCount = 0;//��¼����ߵ�һ��·����ɫ���ĸ���
//		int k = 0;
//		while (pCur)
//		{
//			if (pCur->_color == BLACK)
//				blackCount++;
//			pCur = pCur->_pLeft;
//		}
//		return _IsCheck(_pRoot, k, blackCount);
//	}
//
//private:
//	void RotateL(pNode pParent)//����
//	{
//		pNode pSubR = pParent->_pRight;
//		pNode pSubRL = pSubR->_pLeft;
//
//		pParent->_pRight = pSubRL;
//		if (pSubRL)
//			pSubRL->_pParent = pParent;
//		pNode pPParent = pParent->_pParent;
//		pSubR->_pLeft = pParent;
//		pParent->_pParent = pSubR;
//		pSubR->_pParent = pPParent;
//		if (pParent == _pRoot)
//			_pRoot = pSubR;
//		else
//		{
//			if (pParent == pPParent->_pLeft)
//				pPParent->_pLeft = pSubR;
//			else
//				pPParent->_pRight = pSubR;
//		}
//	}
//
//	void RotateR(pNode pParent)//�ҵ���
//	{
//		pNode pSubL = pParent->_pLeft;
//		pNode pSubLR = pSubL->_pRight;
//
//		pParent->_pLeft = pSubLR;
//		if (pSubLR)
//			pParent->_pLeft = pSubLR;
//		pNode pPParent = pParent->_pParent;
//		pSubL->_pRight = pParent;
//		pParent->_pParent = pSubL;
//		pSubL->_pParent = pPParent;
//		if (pParent == _pRoot)
//			_pRoot = pSubL;
//		else
//		{
//			if (pParent == pPParent->_pLeft)
//				pPParent->_pLeft = pSubL;
//			else
//				pPParent->_pRight = pSubL;
//		}
//	}
//
//	void _InOrder(pNode pRoot)
//	{
//		if (pRoot)
//		{
//			_InOrder(pRoot->_pLeft);
//			cout << "<" << pRoot->_key << "," << pRoot->_value << ">" << endl;
//			_InOrder(pRoot->_pRight);
//		}
//	}
//
//	bool _IsCheck(pNode pRoot, int k, int blackCount)
//	{
//		if (pRoot == NULL)
//			return true;
//		if (pRoot->_color == BLACK)
//		{
//			pNode pParent = pRoot->_pParent;
//			if (pParent && pParent->_color == RED && pRoot->_color == RED)//��������4
//			{
//				cout << "����һ��ĺ�ɫ���" << endl;
//				return false;
//			}
//		}
//		if (pRoot->_color == BLACK)
//			k++;
//		if (pRoot->_pLeft == NULL && pRoot->_pRight == NULL)
//		{
//			if (k != blackCount)//��������3
//			{
//				cout << "ÿ��·���Ϻ�ɫ���ĸ��������" << endl;
//				return false;
//			}
//		}
//		return _IsCheck(pRoot->_pLeft, k, blackCount) &&
//			_IsCheck(pRoot->_pRight, k, blackCount);
//	}
//private:
//	pNode _pRoot;
//};

#pragma once
#include <iostream>
using namespace std;
enum COLOR { RED, BLACK };

template <class V>
struct RBNode
{
	RBNode(const V& value, const COLOR color = RED)
	: _pLeft(NULL)
	, _pRight(NULL)
	, _pParent(NULL)
	, _value(value)
	, _color(color)
	{}
	RBNode<V>* _pLeft;
	RBNode<V>* _pRight;
	RBNode<V>* _pParent;
	V _value;
	COLOR _color;
};

template <class V>
class RBTree
{
	typedef RBNode<V> Node;
	typedef Node* pNode;
public:
	RBTree()
		: _pRoot(NULL)
	{}

	bool Insert(const V& value)
	{
		if (NULL == _pRoot)//������ֱ�Ӳ���
		{
			_pRoot = new Node(value, BLACK);
			return true;
		}

		pNode pCur = _pRoot;//�ǿ�����(1)���Ҵ�����Ľ���λ��
		pNode pParent = NULL;
		while (pCur)
		{
			if (value.first < (pCur->_value).first)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
		}
		pCur = new Node(value);//(2)������
		if (value.first < (pParent->_value).first)
			pParent->_pLeft = pCur;
		else if (value.first > (pParent->_value).first)
			pParent->_pRight = pCur;
		else
			return false;
		pCur->_pParent = pParent;

		while (_pRoot != pCur && pParent->_color == RED)//(3)����
		{
			pNode grandFather = pParent->_pParent;
			if (pParent == grandFather->_pLeft)
			{
				pNode uncle = grandFather->_pRight;

				if (uncle && uncle->_color == RED)//�����
				{
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;
					pCur = grandFather;
					pParent = pCur->_pParent;
				}
				else
				{
					if (pCur == pParent->_pRight)//�������Ժϲ��������
					{
						RotateL(pParent);
						swap(pCur, pParent);
					}
					pParent->_color = BLACK;//�����
					grandFather->_color = RED;
					RotateR(grandFather);
				}
			}
			else
			{
				pNode uncle = grandFather->_pLeft;

				if (uncle && uncle->_color == RED)//�����
				{
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;
					pCur = grandFather;
					grandFather = pCur->_pParent;
				}
				else
				{
					if (pCur == pParent->_pLeft)
					{
						RotateR(pParent);
						swap(pCur, pParent);
					}
					pParent->_color = BLACK;
					grandFather->_color = RED;
					RotateL(grandFather);
				}
			}
		}
		_pRoot->_color = BLACK;
		return true;
	}

	void InOrder()
	{
		return _InOrder(_pRoot);
	}

	bool IsCheck()//���ں�����ļ��飬���ǿ���ͨ�����������еĺ��������м���
	{
		if (NULL == _pRoot)
			return true;

		if (_pRoot->_color == RED)//��������2
		{
			cout << "�������ɫ���Ǻ�ɫ" << endl;
			return false;
		}

		pNode pCur = _pRoot;
		int blackCount = 0;//��¼����ߵ�һ��·����ɫ���ĸ���
		int k = 0;
		while (pCur)
		{
			if (pCur->_color == BLACK)
				blackCount++;
			pCur = pCur->_pLeft;
		}
		return _IsCheck(_pRoot, k, blackCount);
	}

private:
	void RotateL(pNode pParent)//����
	{
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

	void RotateR(pNode pParent)//�ҵ���
	{
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

	void _InOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << (pRoot->_value).first << endl;
			_InOrder(pRoot->_pRight);
		}
	}

	bool _IsCheck(pNode pRoot, int k, int blackCount)
	{
		if (pRoot == NULL)
			return true;
		if (pRoot->_color == BLACK)
		{
			pNode pParent = pRoot->_pParent;
			if (pParent && pParent->_color == RED && pRoot->_color == RED)//��������4
			{
				cout << "����һ��ĺ�ɫ���" << endl;
				return false;
			}
		}
		if (pRoot->_color == BLACK)
			k++;
		if (pRoot->_pLeft == NULL && pRoot->_pRight == NULL)
		{
			if (k != blackCount)//��������3
			{
				cout << "ÿ��·���Ϻ�ɫ���ĸ��������" << endl;
				return false;
			}
		}
		return _IsCheck(pRoot->_pLeft, k, blackCount) &&
			_IsCheck(pRoot->_pRight, k, blackCount);
	}
private:
	pNode _pRoot;
};