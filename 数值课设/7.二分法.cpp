//#include<iostream>
//#include<iomanip>
//#include<cmath>
//#define ep 0.00001
//#define max 100
//using namespace std;
//int main()
//{
//	double f(double x);
//	double x, a, b;
//	//a为左端点,b为右端点,x为近似根
//	int k = 0;
//	cout << "请输入区间左端点: ";
//	cin >> a;
//	cout << endl;
//	cout << "请输入区间右端点: ";
//	cin >> b;
//	cout << endl;
//	x = (a + b) / 2.0;
//	while (fabs(f(x))>ep || (b - a)>ep)
//	{
//		if (k>max)
//		{
//			cout << "已知解得存在区间太大或错误，请重新输入！" << endl;
//			break;
//		}
//		if (f(x)*f(a)<0)b = x;
//		else a = x;
//		x = (a + b) / 2.0;
//		k = k + 1;
//	}
//	cout << "迭代次数为: " << k << endl;
//	cout << endl;
//	cout << " 近似根为 :" << setprecision(15) << x << endl;
//	return 0;
//}
//double f(double x)
//{
//	double y;
//	y = x*pow(2, x) - 1;
//	return y;
//}
//
//
