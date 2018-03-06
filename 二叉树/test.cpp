#include "Tree.hpp"

int main()
{
	char* preorder = "abdcefg";
	char* inorder = "dbafegc";
	BinTree<char> t;
	t.ReBuildTree(preorder, inorder);
	t.PreOrder_N();
	t.PreOrder();
	t.InOrder_N();
	t.InOrder();
	t.PostOrder();
	t.PostOrder_N();
	t.PostOrder_N2();
	//t.InOrder();
	//int arr[] = { 1, 2, 3, 0, 0, 0, 4, 5, 0, 0, 6 };
	//BinTree<int> t(arr, sizeof(arr) / sizeof(arr[0]), 0);
	//char* pStr = "abd###ce##f";
	//BinTree<char> t(pStr, strlen(pStr), '#');
	//BinTree<char> tt;
	//tt = bt;
	//BinTree<char> btt(bt);
	//t.PreOrder();
	//t.InOrder();
	//t.PostOrder();
	//t.LevelOrder();
	//cout << t.Size() << endl;
	//cout << t.GetLeafCount() << endl;
	//cout << t.GetKLevelCount(1) << endl;
	//cout << t.GetKLevelCount(2) << endl;
	//cout << t.GetKLevelCount(3) << endl;
	//cout << t.Height() << endl;
	//cout << t.Find('c')->_data << endl;
	//cout << t.Parent(t.Find('b'))->_data << endl;
	//cout << t.Parent(t.Find('c'))->_data << endl;
	//cout << t.Parent(t.Find('d'))->_data << endl;
	//cout << t.Parent(t.Find('e'))->_data << endl;
	//cout << t.Parent(t.Find('f'))->_data << endl;
	//cout << t.LeftChild(t.Find('a'))->_data << endl;
	//cout << t.RightChild(t.Find('a'))->_data << endl;
	//t.Mirror();
	//t.Mirror_N();
	//t.PreOrder();
	//if (t.IsCompleteBinTree2())
	//	cout << "是完全二叉树" << endl;
	//else
	//	cout << "不是完全二叉树" << endl;
}
