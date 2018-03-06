#include "map.hpp"
#include <string>
int main()
{
	Map<string, string> m;
	m.Insert(make_pair("111", "aaa"));
	m.Insert(make_pair("222", "bbb"));
	Map<string, string>::Iterator it = m.Begin();
	while (it != m.End())
	{
		cout << (*it).first << " ";
		it++;
	}
	cout << endl;
	cout << m["111"] << endl;
}

//#include "set.hpp"
//#include <iostream>
//using namespace std;
//int main()
//{
//	Set<int> s;
//	int arr[] = { 4, 8, 9, 6, 5, 7, 1, 2, 3 };
//	for (int i = 0; i < 9; i++)
//		s.Insert(arr[i]);
//	Set<int>::Iterator it = s.Begin();
//	while (it != s.End())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//}

