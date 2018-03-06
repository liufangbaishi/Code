#include <iostream>
using namespace std;
#include <string>
#include <queue>
#include <stack>
template <class T>
struct TreeNode
{
	TreeNode(const T& data)
	: _data(data)
	, _pLeft(NULL)
	, _pRight(NULL)
	{}

	T _data;
	TreeNode<T> *_pLeft;
	TreeNode<T> *_pRight;
};
template <class T>
class BinTree
{
	typedef TreeNode<T> Node;
public:
	BinTree()
		: _pRoot(NULL)
	{}
	BinTree(const T* arr, size_t size, const T& invalid)
	{
		size_t index = 0;
		_CreateTree(_pRoot, arr, size, index, invalid);
	}
	BinTree(const BinTree<T>& bt)
	{
		_pRoot = _CopyTree(bt._pRoot);
	}
	BinTree& operator=(const BinTree<T>& bt)
	{
		if (this != &bt)
		{
			_DestoryTree(_pRoot);
			_pRoot = _CopyTree(bt._pRoot);
		}
		return *this;
	}
	~BinTree()
	{
		_DestoryTree(_pRoot);
	}
	void PreOrder()
	{
		_PreOrder(_pRoot);
		cout << endl;
	}
	void InOrder()
	{
		_InOrder(_pRoot);
		cout << endl;
	}
	void PostOrder()
	{
		_PostOrder(_pRoot);
		cout << endl;
	}
	void LevelOrder()
	{
		_LevelOrder(_pRoot);
		cout << endl;
	}
	size_t Size()//结点个数
	{
		return _Size(_pRoot);
	}
	size_t GetLeafCount()//叶子结点的个数
	{
		return _GetLeafCount(_pRoot);
	}
	size_t GetKLevelCount(size_t K)//第K层结点个数
	{
		return _GetKLevelCount(_pRoot, K);
	}
	size_t Height()//高度
	{
		return _Height(_pRoot);
	}
	Node* Find(const T& data)
	{
		return _Find(_pRoot, data);
	}
	Node* Parent(Node* pNode)
	{
		return _Parent(_pRoot, pNode);
	}
	Node* LeftChild(Node* pNode)
	{
		return (NULL == pNode) ? NULL : pNode->_pLeft;
	}
	Node* RightChild(Node* pNode)
	{
		return (NULL == pNode) ? NULL : pNode->_pRight;
	}
	void Mirror()
	{
		return _Mirror(_pRoot);
	}
	void Mirror_N()
	{
		if (NULL == _pRoot)
			return;
		queue<Node*> q;
		q.push(_pRoot);
		while (!q.empty())
		{
			Node* pCur = q.front();
			swap(pCur->_pLeft, pCur->_pRight);
			q.pop();
			if (pCur->_pLeft)
				q.push(pCur->_pLeft);
			if (pCur->_pRight)
				q.push(pCur->_pRight);
		}
	}
	bool IsCompleteBinTree()
	{
		if (_pRoot == NULL)
			return true;
		bool flag = false;
		queue<Node*> q;
		q.push(_pRoot);
		Node* pCur = NULL;
		while (!q.empty())
		{
			pCur = q.front();
			if (flag && (pCur->_pLeft || pCur->_pRight))
				return false;
			else
			{
				if (pCur->_pLeft && pCur->_pRight)
				{
					q.push(pCur->_pLeft);
					q.push(pCur->_pRight);
				}
				else if (pCur->_pLeft)
				{
					q.push(pCur->_pLeft);
					flag = true;
				}
				else if (pCur->_pRight)
					return false;
				else
					flag = true;
			}
			q.pop();
		}
		return true;
	}
	bool IsCompleteBinTree2()//层序遍历每个结点，遇到NULL结束；队列中如果剩下的全是NULL就是完全，如果有一个不是NULL，就不是完全二叉树
	{
		queue<Node*> q;
		q.push(_pRoot);
		Node* pCur = q.front();
		while (pCur)
		{
			q.push(pCur->_pLeft);
			q.push(pCur->_pRight);
			q.pop();
			pCur = q.front();
		}
		while (!q.empty())
		{
			pCur = q.front();
			if (pCur != NULL)
				return false;
			q.pop();
		}
		return true;
	}
	Node* ReBuildTree(char* preorder, char* inorder)
	{
		size_t size = strlen(inorder);
		return _ReBuildTree(_pRoot, preorder, inorder, inorder + size - 1);
	}
	void PreOrder_N()
	{
		if (NULL == _pRoot)
			return;
		Node* pCur = NULL;
		stack<Node*> s;
		s.push(_pRoot);
		while (!s.empty())
		{
			pCur = s.top();
			cout << pCur->_data << " ";
			s.pop();
			if (pCur->_pRight)
				s.push(pCur->_pRight);
			if (pCur->_pLeft)
				s.push(pCur->_pLeft);
		}
		cout << endl;
	}
	void InOrder_N()
	{
		if (NULL == _pRoot)
			return;
		stack<Node*> s;
		Node* pCur = _pRoot;
		while (pCur || !s.empty())
		{
			while (pCur)
			{
				s.push(pCur);
				pCur = pCur->_pLeft;
			}
			pCur = s.top();
			cout << pCur->_data << " ";
			s.pop();
			pCur = pCur->_pRight;
		}
		cout << endl;
	}
	void PostOrder_N()
	{
		if (_pRoot == NULL)
			return;
		Node* pCur = _pRoot;
		Node* prev = NULL;
		stack<Node*> s;
		while (!s.empty() || pCur)
		{
			while (pCur)
			{
				s.push(pCur);
				pCur = pCur->_pLeft;
			}
			pCur = s.top();
			if (pCur->_pRight == NULL || prev == pCur->_pRight)
			{
				cout << pCur->_data << " ";
				prev = pCur;
				s.pop();
				pCur = NULL;
			}
			else
				pCur = pCur->_pRight;
		}
		cout << endl;
	}
	void PostOrder_N2()
	{
		if (_pRoot == NULL)
			return;
		Node* pCur = _pRoot;
		Node* prev = NULL;
		stack<Node*> s;
		while (!s.empty() || pCur)
		{
			while (pCur)
			{
				s.push(pCur);
				pCur = pCur->_pLeft;
			}
			Node* pTop = s.top();
			if (pTop->_pRight == NULL || prev == pTop->_pRight)
			{
				cout << pTop->_data << " ";
				prev = pTop;
				s.pop();
			}
			else
				pCur = pTop->_pRight;
		}
		cout << endl;
	}
private:
	Node* _ReBuildTree(Node*& pRoot, char*& preorder, char* inbegin, char* inend)
	{
		if (inbegin>inend || *preorder == '\0')
			return NULL;
		pRoot = new Node(*preorder);
		char* cur = inbegin;
		for (cur = inbegin; cur <= inend; cur++)
		{
			if (*cur == *preorder)
			{
				if (inbegin <= cur - 1)
					_ReBuildTree(pRoot->_pLeft, ++preorder, inbegin, cur - 1);
				if (cur + 1 <= inend)
					_ReBuildTree(pRoot->_pRight, ++preorder, cur + 1, inend);
			}
		}
		return pRoot;
	}
	void _Mirror(Node* pRoot)
	{
		if (pRoot == NULL)
			return;
		if (pRoot->_pLeft || pRoot->_pRight)
			swap(pRoot->_pLeft, pRoot->_pRight);
		_Mirror(pRoot->_pLeft);
		_Mirror(pRoot->_pRight);
	}
	Node* _Parent(Node* pRoot, Node* pNode)
	{
		if (NULL == pRoot || NULL==pNode || pRoot==pNode)
			return NULL;
		if (pRoot->_pLeft == pNode || pRoot->_pRight == pNode)
			return pRoot;
		
		Node* tmp = _Parent(pRoot->_pLeft, pNode);
		return (tmp == NULL) ? _Parent(pRoot->_pRight, pNode) : tmp;
	}
	Node* _Find(Node* pRoot, const T& data)
	{
		if (pRoot == NULL)
			return NULL;
		if (pRoot->_data == data)
			return pRoot;

		Node* tmp = _Find(pRoot->_pLeft, data);
		return (tmp == NULL) ? _Find(pRoot->_pRight, data) : tmp;
	}
	size_t _Height(Node* pRoot)
	{
		if (NULL == pRoot)
			return 0;
		if (pRoot->_pLeft == NULL && pRoot->_pRight == NULL)
			return 1;

		size_t left = _Height(pRoot->_pLeft);
		return _Height(pRoot->_pRight) > left ? _Height(pRoot->_pRight)+1 : left+1;
	}
	size_t _GetKLevelCount(Node* pRoot, size_t K)
	{
		if (K == 0 || pRoot == NULL)
			return 0;
		else if (K == 1)
			return 1;
		else
			return _GetKLevelCount(pRoot->_pLeft, K - 1) + _GetKLevelCount(pRoot->_pRight, K - 1);
	}
	size_t _GetLeafCount(Node* pRoot)
	{
		if (NULL == pRoot)
			return 0;
		else if (pRoot->_pLeft == NULL && pRoot->_pRight == NULL)
			return 1;
		else
			return _GetLeafCount(pRoot->_pLeft) + _GetLeafCount(pRoot->_pRight);
	}
	size_t _Size(Node* pRoot)
	{
		if (NULL == pRoot)
			return 0;
		else
			return 1 + _Size(pRoot->_pLeft) + _Size(pRoot->_pRight);
	}
	void _LevelOrder(Node* pRoot)
	{
		if (pRoot == NULL)
			return;
		queue<Node*> q;
		q.push(pRoot);
		while (!q.empty())
		{
			Node* pCur = q.front();
			cout << pCur->_data << " ";
			q.pop();
			if (pCur->_pLeft)
				q.push(pCur->_pLeft);
			if (pCur->_pRight)
				q.push(pCur->_pRight);
		}
	}
	void _PreOrder(const Node* pRoot)
	{
		if (pRoot)
		{
			cout << pRoot->_data << " ";
			_PreOrder(pRoot->_pLeft);
			_PreOrder(pRoot->_pRight);
		}
	}
	void _InOrder(const Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}
	void _PostOrder(const Node* pRoot)
	{
		if (pRoot)
		{
			_PostOrder(pRoot->_pLeft);
			_PostOrder(pRoot->_pRight);
			cout << pRoot->_data << " ";
		}
	}
	void _CreateTree(Node* &pRoot, const T* arr, size_t size, size_t& index, const T& invalid)
	{
		if (index<size && arr[index]!=invalid)
		{
			pRoot = new Node(arr[index]);
			_CreateTree(pRoot->_pLeft, arr, size, ++index, invalid);
			_CreateTree(pRoot->_pRight, arr, size, ++index, invalid);
		}
	}
	Node* _CopyTree(Node* pRoot)
	{
		Node* pNewRoot = NULL;
		if (pRoot)
		{
			pNewRoot = new Node(pRoot->_data);
			if (pRoot->_pLeft)
				pNewRoot->_pLeft = _CopyTree(pRoot->_pLeft);
			if (pRoot->_pRight)
				pNewRoot->_pRight = _CopyTree(pRoot->_pRight);
		}
		return pNewRoot;
	}
	void _DestoryTree(Node* &pRoot)
	{
		if (pRoot)
		{
			_DestoryTree(pRoot->_pLeft);
			_DestoryTree(pRoot->_pRight);
			delete pRoot;
			pRoot = NULL;
		}
	}
private:
	Node* _pRoot;
};