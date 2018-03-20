
#include <iostream>
using namespace std;
template <class K, int M=3>
struct BTreeNode
{
	BTreeNode()
	: _pParent(NULL)
	, _size(0)
	{
		for (size_t i = 0; i <= M; i++)
			_pSub[i] = NULL;
	}
	K _key[M];
	BTreeNode<K, M>* _pSub[M + 1];
	BTreeNode<K, M>* _pParent;
	size_t _size;
};
template <class K, int M=3>
class BTree
{
	typedef BTreeNode<K, M> Node;
	typedef Node* PNode;
public:
	BTree()
		: _pRoot(NULL)
	{}

	bool Insert(K& key)
	{
		if (_pRoot == NULL)//�����ֱ�Ӳ���
		{
			_pRoot = new Node();
			_pRoot->_key[0] = key;
			_pRoot->_size = 1;
			return true;
		}
		
		pair<PNode, int> ret = Find(key);
		if (ret.second >= 0)//û�ҵ�����Ҫ������
			return false;

		PNode pCur = ret.first;
		PNode pSub = NULL;
		while (1)
		{
			_InsertKey(pCur, key, pSub);//������

			int size = pCur->_size;
			if (size < M)//����ɹ�������Ҫ����
				return true;
			else
			{
				int mid = size >> 1;
				PNode temp = new Node();

				for (size_t i = mid + 1; i < size; i++)//����  ���ƽ���е�key�ͺ��ӽ��
				{
					temp->_key[temp->_size] = pCur->_key[i];
					temp->_pSub[temp->_size] = pCur->_pSub[i];
					if (temp->_pSub[temp->_size])
						temp->_pSub[temp->_size]->_pParent = temp;
					temp->_size++;
				}
				temp->_pSub[temp->_size] = pCur->_pSub[pCur->_size];

				if (temp->_pSub[temp->_size])
					temp->_pSub[temp->_size]->_pParent = temp;
				pCur->_size -= (temp->_size + 1);//����size

				if (pCur == _pRoot)//�����ǰ����Ǹ���㣬����Ҫ�ٴ���
				{
					_pRoot = new Node;
					_pRoot->_key[0] = pCur->_key[mid];
					_pRoot->_pSub[0] = pCur;
					pCur->_pParent = _pRoot;
					_pRoot->_pSub[1] = temp;
					temp->_pParent = _pRoot;
					_pRoot->_size = 1;
					return true;
				}
				else
				{
					key = pCur->_key[mid];
					pCur = pCur->_pParent;
					pSub = temp;
				}
			}
		}
	}

	pair<PNode, int> Find(const K& key)//����ֵΪkey�Ľ�㣬�ҵ����ؽ�㼰�ڽ���е�λ�ã�û�ҵ����ص�ǰ����˫�׽�㼰-1
	{
		PNode pCur = _pRoot;
		PNode pParent = NULL;
		while (pCur)
		{
			int i = 0;
			while (i < pCur->_size)
			{
				if (key == pCur->_key[i])
					return pair<PNode, int>(pCur, i);
				else if (key < pCur->_key[i])
					break;
				else
					i++;
			}
			pParent = pCur;
			pCur = pCur->_pSub[i];
		}
		return make_pair(pParent, -1);//û�ҵ�����-1
	}

	void InOrder()
	{
		_InOrder(_pRoot);
	}
private:
	void _InsertKey(PNode pCur, const K& key, PNode pSub)
	{
		//ֱ�Ӳ����˼��
		int end = pCur->_size - 1;
		while (key < pCur->_key[end] && end >= 0)
		{
			pCur->_key[end + 1] = pCur->_key[end];
			pCur->_pSub[end + 2] = pCur->_pSub[end + 1];
			end--;
		}

		pCur->_key[end + 1] = key;
		pCur->_pSub[end + 2] = pSub;
		if (pSub)
			pSub->_pParent = pCur;
		pCur->_size += 1;
	}

	void _InOrder(PNode pRoot)
	{
		if (pRoot == NULL)
			return;
		for (size_t i = 0; i < pRoot->_size; i++)
		{
			_InOrder(pRoot->_pSub[i]);
			cout << pRoot->_key[i] << " ";
		}
		_InOrder(pRoot->_pSub[pRoot->_size]);
	}
private:
	PNode _pRoot;
};

void test()
{
	int arr[] = { 53, 75, 139, 49, 145, 36, 101 };
	BTree<int> b;
	size_t size = sizeof(arr) / sizeof(arr[0]);
	for (size_t i = 0; i < 7; i++)
	{
		b.Insert(arr[i]);
		b.InOrder();
		cout << endl;
	}
}
