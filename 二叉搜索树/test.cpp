#if 1
#include "BSTree.hpp"
void Test()
{
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int, int> bt;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		bt.Insert_N(arr[i], arr[i]);
	bt.InOrder();
	cout << endl;
	bt.Delete_N(4);
	bt.InOrder();
}

void Test2()
{
	int arr[] = { 5, 3, 4, 1, 2, 0 };
	BSTree<int, int> bt;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		bt.Insert(arr[i], arr[i]);
	BSTreeNode<int, int>* pNode = bt.BSTreeToList();
	BSTreeNode<int, int>* pCur = pNode;
	while (pCur)//正向打印
	{
		cout << pCur->_key << " ";
		pCur = pCur->_pRight;
	}
	cout << endl;

	pCur = pNode;//逆向打印
	while (pCur->_pRight)
		pCur = pCur->_pRight;
	while (pCur)
	{
		cout << pCur->_key << " ";
		pCur = pCur->_pLeft;
	}
}
#else
#include "BSTree_Iterator.hpp"
void Test()
{
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int, int> bt;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		bt.Insert(arr[i], arr[i]);
	BSTree<int, int>::Iterator it = bt.Begin();
	while (it != NULL && it != bt.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	bt.Delete(2);
	bt.Delete(5);
	it = bt.Begin();
	while (it != NULL && it != bt.End())
	{
		cout << *it << " ";
		it++;
	}
}
#endif
int main()
{
	Test();
}
