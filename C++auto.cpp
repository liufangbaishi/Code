#include <iostream>
using namespace std;
////auto声明的变量不会带走const和volatile特性,引用和指针可以
int main()
{
	//const int x = 10;
	//const auto a = x;
	//// a = 20;  //a有const修饰 不能被改
	//auto m = a; // m的类型是int，没有const属性
	//m = 30;
	//cout << m << " " << typeid(m).name() << endl;

	int a = 10;
	const int* p = &a;
	auto pp = p;
	//*pp = 30;  //pp的类型是int const*，保留了const属性
	cout << *pp << " " << typeid(pp).name() << endl;
}

//int main() 
//{ 
//	volatile const int a = 20;  
//	int* p = (int*)&a;
//	*p = 10;
//	cout << a << endl;
//
//	auto pp = (int*)&a;  //pp的类型是int*，保留着volatile特性
//	*pp = 50;
//	cout << a << " " << typeid(a).name() << endl;
//	return 0; 
//}

