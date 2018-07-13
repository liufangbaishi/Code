10 改进欧拉方法解微分方程
#include<iostream>
#include<cmath>
using namespace std;
void main()
{
	double x, y = 1, h = 0.2, yb, ya;//yb为预报，ya为校正
	for (x = 0; x <= 1;)
	{
		yb = y + h*(2 * x + 3 * y);
		ya = y + h / 2 * ((2 * x + 3 * y) + (2 * (x + h) + 3 * yb));
		cout << "x=" << x << "  yn=" << y << "  yn+1=" << ya << endl;
		x += 0.2;
		y = ya;
	}
}
