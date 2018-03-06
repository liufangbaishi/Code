//#if 0
//#include "RBTree.hpp"
//
//void Test2()
//{
//	int arr[] = { 10, 7, 8, 15, 5, 6, 11, 13, 12 };
//	RBTree<int, int> rbt;
//
//	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
//		rbt.Insert(arr[i], arr[i]);
//	cout << "中序遍历结果：" << endl;
//	rbt.InOrder();
//	if (rbt.IsCheck())
//		cout << "是红黑树" << endl;
//	else
//		cout << "不是红黑树" << endl;
//}
//#else
//#include "RBTree_Iterator.hpp"
//
//
//void Test1()
//{
//	int arr[] = { 5, 4, 6, 1, 2, 3, 7, 8, 9, 0 };
//	RBTree<int, int> rbt;
//	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
//		rbt.Insert(arr[i], arr[i]);
//
//	RBTree<int, int>::Iterator it = rbt.Begin();
//	while (it != rbt.End())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//	cout << rbt.Size() << endl;
//}
//#endif
//
//int main()
//{
//#if 1
//	Test1();
//#else
//	Test2();
//#endif
//}

#include "RBTree.hpp"
#include <map>
int main()
{
	map<int, int> m;
	m.insert(make_pair(1,1));
	m.insert(make_pair(2, 2));
	/*RBTree<pair<string, string>> t;
	t.Insert(pair<string, string>("111","aaa"));
	t.Insert(make_pair("222", "bbb"));
	t.Insert(make_pair("333", "ccc"));
	t.Insert(make_pair("444", "ddd"));*/
}

