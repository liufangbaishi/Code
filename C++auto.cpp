#include <iostream>
using namespace std;
////auto�����ı����������const��volatile����,���ú�ָ�����
int main()
{
	//const int x = 10;
	//const auto a = x;
	//// a = 20;  //a��const���� ���ܱ���
	//auto m = a; // m��������int��û��const����
	//m = 30;
	//cout << m << " " << typeid(m).name() << endl;

	int a = 10;
	const int* p = &a;
	auto pp = p;
	//*pp = 30;  //pp��������int const*��������const����
	cout << *pp << " " << typeid(pp).name() << endl;
}

//int main() 
//{ 
//	volatile const int a = 20;  
//	int* p = (int*)&a;
//	*p = 10;
//	cout << a << endl;
//
//	auto pp = (int*)&a;  //pp��������int*��������volatile����
//	*pp = 50;
//	cout << a << " " << typeid(a).name() << endl;
//	return 0; 
//}

