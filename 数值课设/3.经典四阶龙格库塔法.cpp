////3 经典四阶龙格库塔法解一阶微分方程组源程序代码
//#include<iostream>
//#include<cmath>
//#include<iomanip>
//#define nn 2
//using namespace std;
//int main()
//{
//	double dyfun0(double x, double y, double z);
//	double dyfun1(double x, double y, double z);
//	double k1[nn], k2[nn], k3[nn], k4[nn], a, b, h, y0[nn], x0;
//	//a为求解区间的左端点,b为求解区间的右端点
//	//y0为初值向量,h为步长,x为节点,y为节点出的函数值
//	int i, n;
//	double x, y, z, x1, y1, z1;
//	cout << "请输入区间左端点 a: ";
//	cin >> a;
//	cout << "请输入区间右端点 b: ";
//	cin >> b;
//	cout << "请输入初值点 x0: ";
//	cin >> x0;
//	cout << "请输入初始值 y0: ";
//	for (i = 0; i<nn; i++)
//		cin >> y0[i];
//	cout << "请输入区间步长 h: ";
//	cin >> h;
//	n = (b - a) / h;
//	cout << n << endl;
//	y = y0[0]; z = y0[1];
//	x = x0;
//	for (n; n>0; n--)
//	{
//		x1 = x + h;
//		k1[0] = dyfun0(x, y, z);
//		k1[1] = dyfun1(x, y, z);
//		k2[0] = dyfun0(x + h / 2, y + h / 2 * k1[0], z + h / 2 * k1[1]);
//		k2[1] = dyfun1(x + h / 2, y + h / 2 * k1[0], z + h / 2 * k1[1]);
//		k3[0] = dyfun0(x + h / 2, y + h / 2 * k2[0], z + h / 2 * k2[1]);
//		k3[1] = dyfun1(x + h / 2, y + h / 2 * k2[0], z + h / 2 * k2[1]);
//		k4[0] = dyfun0(x + h, y + h*k3[0], z + h*k3[1]);
//		k4[1] = dyfun1(x + h, y + h*k3[0], z + h*k3[1]);
//		y1 = y + h*(k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]) / 6;
//		z1 = z + h*(k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]) / 6;
//		cout << "x=  " << x1 << setw(10) << "y=  " << y1 << setw(10) << "z=" << z1 << endl;
//		x = x1; y = y1; z = z1;
//	}
//	system("pause");
//	return 0;
//}
//double dyfun0(double x, double y, double z)
//{
//	double dy0;
//	dy0 = -0.01*y - 99.99*z;
//	return (dy0);
//}
//double dyfun1(double x, double y, double z)
//{
//	double dy1;
//	dy1 = -100 * z;
//	return (dy1);
//}
//
//
//
//
