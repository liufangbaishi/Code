#define _CRT_SECURE_NO_WARNING
#if 1
#include "Stack.h"
//void TestStack1()
//{
//	Stack<int, List<int>> s;
//	cout << s.Empty() << endl;
//	s.Push(1);
//	s.Push(2);
//	s.Push(3);
//	cout << s.Size() << endl;
//	cout << s.Top() << endl;
//	cout << s.Empty() << endl;
//	s.Pop();
//	s.Pop();
//	s.Pop();
//	cout << s.Size() << endl;
//}
//void TestStack2()
//{
//	Stack<int, List> s;
//	cout << s.Empty() << endl;
//	s.Push(1);
//	s.Push(2);
//	s.Push(3);
//	cout << s.Size() << endl;
//	cout << s.Top() << endl;
//	cout << s.Empty() << endl;
//	s.Pop();
//	s.Pop();
//	s.Pop();
//	cout << s.Size() << endl;
//}
#include "Queue.h"
void TestQueue1()
{
	Queue<int, Vector<int>> q;
	q.Push(1);
	q.Push(2);
	q.Push(4);
	q.Push(10);
	cout << q.Size() << endl;
	cout << q.Front() << endl;
	cout << q.Back() << endl;
	cout << q.Empty() << endl;
	q.Pop();
	q.Pop();
	q.Pop();
	cout << q.Size() << endl;
	cout << q.Front() << endl;
	cout << q.Back() << endl;
	cout << q.Empty() << endl;
	q.Pop();
	cout << q.Size() << endl;
	cout << q.Front() << endl;
	cout << q.Back() << endl;
	cout << q.Empty() << endl;
}
//void TestQueue2()
//{
//	Queue<int, Vector> q;
//	q.Push(1);
//	q.Push(2);
//	q.Push(4);
//	q.Push(10);
//	cout << q.Size() << endl;
//	cout << q.Top() << endl;
//	cout << q.Empty() << endl;
//	q.Pop();
//	q.Pop();
//	q.Pop();
//	cout << q.Size() << endl;
//	cout << q.Top() << endl;
//	cout << q.Empty() << endl;
//	q.Pop();
//	cout << q.Size() << endl;
//	cout << q.Top() << endl;
//	cout << q.Empty() << endl;
//}
int main()
{
	//TestStack2();
	//TestStack1();
	TestQueue1();
	return 0;
}
#endif
