9 �������η�����ֵĽ��ƽ�Դ�������
#include<iostream>
#include<cmath>
#include<iomanip>
#define a 0
#define b 1
#define h 0.1
using namespace std;
const int n = (b - a) / h + 1;
int main()
{
	double f(double x);
	double x[n], y[n], s = 0;
	//sΪ���ƽ�
	int i;
	for (i = 0; i<n; i++)
	{
		x[i] = a + h*i;
		y[i] = f(x[i]);
	}
	for (i = 0; i<n - 1; i++)
		s = s + (y[i] + y[i + 1])*h / 2;
	cout << endl;
	cout << "   " << "���ƽ�Ϊ: " << setprecision(15) << s << endl;
	return 0;
}
double f(double x)
{
	double y;
	y = 4 / (1 + x*x);
	return y;
}
