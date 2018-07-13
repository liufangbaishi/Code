5 龙贝格求积分算法源程序代码
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double f(double x)//被积函数
{
	double y;
	y = 4 / (1 + x*x);
	return y;
}
int f1(int k)//构造二的整型k次方
{
	int y;
	y = pow(2, k);//pow(x,y)是用来计算x的y次方
	return y;
}
double f2(int k)//构造二的双精度型k次方
{
	double y;
	y = pow(2, k);
	return y;
}
int main()
{
	double t[100], R[9][9];
	double a, b, e, epR;
	int i, k, n = 8, j;
	cout << "以y = 4/(1+x*x)的积分为例" << endl;
	cout << "请输入积分的下限、上限：";
	cin >> a >> b;
	cout << "请输入计算精度：";
	cin >> e;
	t[0] = (b - a)*(f(a) + f(b)) / 2;
	R[0][0] = t[0];
	cout << setprecision(13) << R[0][0] << " " << endl;
	for (k = 0; k<n; k++)
	{
		double m = 0;
		for (i = 1; i<f1(k) + 1; i++)
		{
			m = m + f(a + (2 * i - 1)*(b - a) / f2(k + 1));
		}
		m = m*(b - a) / f2(k + 1);
		t[k + 1] = t[k] / 2 + m;
		R[k + 1][0] = t[k + 1];
	}
	j = 1;
	while (j <= n)
	{
		cout << setprecision(13) << R[j][0] << " ";
		for (k = 1; k <= j; k++)
		{
			R[j][k] = R[j][k - 1] + (R[j][k - 1] - R[j - 1][k - 1]) / (pow(4, k) - 1);
			cout << setprecision(13) << R[j][k] << " ";
		}
		cout << endl;
		epR = fabs(R[j - 1][j - 1] - R[j][j]);
		if (epR<e)
		{
			cout << "满足精度要求而结束" << endl;
			cout << "积分近似值是" << setprecision(13) << R[j][j] << endl;
			break;
		}
		j = j + 1;
	}

	return 0;
}



