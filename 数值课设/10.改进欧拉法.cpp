10 �Ľ�ŷ��������΢�ַ���
#include<iostream>
#include<cmath>
using namespace std;
void main()
{
	double x, y = 1, h = 0.2, yb, ya;//ybΪԤ����yaΪУ��
	for (x = 0; x <= 1;)
	{
		yb = y + h*(2 * x + 3 * y);
		ya = y + h / 2 * ((2 * x + 3 * y) + (2 * (x + h) + 3 * yb));
		cout << "x=" << x << "  yn=" << y << "  yn+1=" << ya << endl;
		x += 0.2;
		y = ya;
	}
}
