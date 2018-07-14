#pragma once
#include "construct.h"
#include "dafault_alloc.h"
#include "Type_Traits.h"
#include "Iterator_Traits.h"
#include <string>
template <class T>
struct Node
{
	T _data;
	Node<T>* _pNext;
	Node<T>* _pPre;
};

template <class T, class Ref, class Ptr>
struct Iterator
{
	typedef Node<T> ListNode;
	typedef Iterator<T, Ref, Ptr> Self;
	typedef T ValueType;
	typedef Ref Reference;
	typedef Ptr Pointer;
	typedef int DifferenceType;
	typedef BidirectionalIteratorTag IteratorCategory;
	Iterator()
		: _pNode(NULL)
	{}
	Iterator(ListNode* p)
		: _pNode(p)
	{}
	Iterator(Self& s)
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
	Ref operator*()
	{
		return _pNode->_data;
	}
	Ptr operator->()
	{
		return &(operator*());
	}
	Self& operator++()
	{
		_pNode = _pNode->_pNext;
		return *this;
	}
	Self operator++(int)
	{
		Self tmp(*this);
		++(*this);
		return tmp;
	}
	Self& operator--()
	{
		_pNode = _pNode->_pPre;
		return *this;
	}
	Self operator--(int)
	{
		Self tmp(*this);
		--(*this);
		return tmp;
	}

	ListNode* _pNode;
};

template <class T, class Alloc = _Alloc>
class List
{
	typedef Node<T> ListNode;
	typedef SimpleAlloc<ListNode, Alloc> ListAlloc;
public:
	typedef Iterator<T, T&, T*> Iterator;
	typedef ReverseIterator<Iterator> ReverseIterator;
public:
	ReverseIterator RBegin()
	{
		return ReverseIterator(End());
	}
	ReverseIterator REnd()
	{
		return ReverseIterator(Begin());
	}

	List()
	{
		_pHead = CreateNode();
		_pHead->_pNext = _pHead;
		_pHead->_pPre = _pHead;
	}
	Iterator Insert(Iterator pos, const T& data)
	{
		ListNode* pnewNode = CreateNode(data);
		pnewNode->_pNext = pos._pNode;
		pnewNode->_pPre = pos._pNode->_pPre;
		pos._pNode->_pPre->_pNext = pnewNode;
		pos._pNode->_pPre = pnewNode;
		return pnewNode;
	}
	Iterator Erase(Iterator pos)
	{
		ListNode* posnext = (pos._pNode)->_pNext;
		ListNode* pospre = (pos._pNode)->_pPre;
		pospre->_pNext = posnext;
		posnext->_pPre = pospre;

		DestoryNode(pos._pNode);
		return posnext;
	}
	void PushBack(const T& data)
	{
		Insert(End(), data);
	}
	void PushFront(const T& data)
	{
		Insert(Begin(), data);
	}
	void PopBack()
	{
		Erase(--End());
	}
	void PopFront()
	{
		Erase(Begin());
	}
	Iterator Begin()
	{
		return Iterator(_pHead->_pNext);
	}
	Iterator End()
	{
		return Iterator(_pHead);
	}
	void Clear()
	{
		ListNode* cur = _pHead->_pNext;
		while (cur != _pHead)
		{
			ListNode* tmp = cur;
			cur = cur->_pNext;
			DestoryNode(tmp);
		}
		_pHead->_pNext = _pHead;
		_pHead->_pPre = _pHead;
	}
	~List()
	{
		Clear();
		DestoryNode(_pHead);
		_pHead = NULL;
	}
protected:
	ListNode* GetNode()
	{
		return ListAlloc::Allocate();
	}
	void PutNode(ListNode* p)
	{
		ListAlloc::DeAllocate(p);
	}
	ListNode* CreateNode(const T& data = T())
	{
		ListNode* p = GetNode();
		Construct(&p->_data, data);
		return p;
	}
	void DestoryNode(ListNode* p)
	{
		Destory(&p->_data);
		PutNode(p);
	}
private:
	ListNode* _pHead;
};

void test()
{
	List<int> li;
	li.PushBack(111);
	li.PushBack(222);
	li.PushBack(333);
	li.PushFront(000);
	li.PushFront(-111);
	li.PushFront(-222);
	List<int>::Iterator it = li.Begin();
	while (it != li.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	List<int>::ReverseIterator rIt = li.RBegin();
	while (rIt != li.REnd())
	{
		cout << *rIt << " ";
		++rIt;
	}
	cout << endl;
	//cout << Difference(li.Begin(), li.End()) << endl;
	//li.PopBack();
	//li.PopBack();
	//li.PopBack();
	//li.PopFront();
	//li.PopFront();
	//li.PopFront();
	//List<string> ls;
	//ls.PushBack("111");
	//ls.PopBack();
}