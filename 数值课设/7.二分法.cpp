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
//	//aΪ��˵�,bΪ�Ҷ˵�,xΪ���Ƹ�
//	int k = 0;
//	cout << "������������˵�: ";
//	cin >> a;
//	cout << endl;
//	cout << "�����������Ҷ˵�: ";
//	cin >> b;
//	cout << endl;
//	x = (a + b) / 2.0;
//	while (fabs(f(x))>ep || (b - a)>ep)
//	{
//		if (k>max)
//		{
//			cout << "��֪��ô�������̫���������������룡" << endl;
//			break;
//		}
//		if (f(x)*f(a)<0)b = x;
//		else a = x;
//		x = (a + b) / 2.0;
//		k = k + 1;
//	}
//	cout << "��������Ϊ: " << k << endl;
//	cout << endl;
//	cout << " ���Ƹ�Ϊ :" << setprecision(15) << x << endl;
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
