////1 高斯列主元解线性方程组源程序代码
//#include<iostream>
//#include<cmath>
//using namespace std;
//int main()
//{
//	const int n = 5;
//	float A[n][n], X[n], b[n], s, m, u, t;
//	int i, j, k, l;
//	for (i = 0; i<n; i++)
//	{
//		cout << "请输入系数矩阵的第" << i + 1 << "行元素：" << endl;
//		for (j = 0; j<n; j++)
//			cin >> A[i][j];
//		cin >> b[i];
//	}
//	k = 0;
//	while (k != n - 1)
//	{
//		//选主元
//		l = k;
//		m = fabs(A[k][k]);
//		for (i = k + 1; i<n; i++)
//		{
//			u = fabs(A[i][k]);
//			if (m<u)l = i;
//		}
//		for (j = k; j<n; j++)
//		{
//			t = A[k][j]; A[k][j] = A[l][j]; A[l][j] = t;
//		}
//
//		t = b[k]; b[k] = b[l]; b[l] = t;
//		//消元
//		for (i = k + 1; i<n; i++)
//		{
//			t = A[i][k] / A[k][k];
//			for (j = k; j<n; j++)
//				A[i][j] = A[i][j] - t*A[k][j];
//			b[i] = b[i] - t*b[k];
//		}
//		k++;
//	}
//	//求根
//	X[n - 1] = b[n - 1] / A[n - 1][n - 1];
//
//	for (i = n - 2; i >= 0; i--)
//	{
//		s = 0;
//		for (j = i + 1; j<n; j++)
//			s = s + A[i][j] * X[j];
//		X[i] = (b[i] - s) / A[i][i];
//	}
//	cout << endl << "方程的解为：" << endl;
//	for (i = 0; i<n; i++)
//		cout << X[i] << "  ";
//	cout << endl;
//	return 0;
//}
//
//
