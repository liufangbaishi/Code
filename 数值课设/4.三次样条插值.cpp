////4 ����������ֵ�㷨Դ�������
//#include<iostream>
//#include<cmath>
//using namespace std;
//const int N = 4;
//int main()
//{
//	double czhs(double a, double b, double m0, double m1, double x2, double h1);
//	double x0[N], y0[N], m[N], xx[5], yy[5], h[N - 1], lambda[N - 2], theta[N - 2], mu[N - 2], x1[5], sum, A[N - 2][N - 2], b[N - 2], L;
//	int i, j, k;
//	cout << "������Ա���Ϊ:" << endl;
//	for (i = 0; i<N; i++)
//		cin >> x0[i];
//	cout << "����������Ϊ:" << endl;
//	for (i = 0; i<N; i++)
//		cin >> y0[i];
//	cout << "������֪�ĵ���Ϊ:" << endl;
//	cin >> m[0];
//	cin >> m[N - 1];
//	//���h[i]
//	for (i = 0; i<N - 1; i++)
//		h[i] = x0[i + 1] - x0[i];
//	//���lambda[i]
//	for (i = 0; i<N - 2; i++)
//		lambda[i] = h[i + 1] / (h[i] + h[i + 1]);
//	//���mu[i]
//	for (i = 0; i<N - 2; i++)
//		mu[i] = 1 - lambda[i];
//	//���theta[i]
//	cout << "�����Ӧ��thetaֵ:" << endl;
//	for (i = 0; i<N - 2; i++)
//	{
//		theta[i] = 3 * lambda[i] * (y0[i + 1] - y0[i]) / h[i] + 3 * mu[i] * (y0[i + 2] - y0[i + 1]) / h[i + 1];
//		cout << theta[i] << endl;
//	}
//	//д��ϵ������A[N-2][N-2]
//	for (i = 0; i<N - 2; i++)
//		A[i][i] = 2;
//	for (i = 1; i<N - 1; i++)
//	{
//		A[i][i - 1] = lambda[i];
//		A[i - 1][i] = mu[i - 1];
//	}
//	cout << "���ϵ������:" << endl;
//	for (i = 0; i<N - 2; i++)
//	for (j = 0; j<N - 2; j++)
//		cout << A[i][j] << " ";
//	cout << endl;
//	//д����������b[N-2]
//
//	b[0] = theta[0] - lambda[0] * m[0];
//	b[N - 3] = theta[N - 3] - mu[N - 3] * m[N - 1];
//	for (i = 1; i<N - 2; i++)
//	if (i != N - 3) b[i] = theta[i];
//	cout << "���b����:" << endl;
//	for (i = 0; i<N - 2; i++)
//		cout << b[i] << " ";
//	cout << endl;
//	//���m[i]
//	//��˹��Ԫ
//	for (i = 0; i<N - 3; i++)
//	{
//		for (k = i + 1; k<N - 2; k++)
//		{
//			L = A[k][i] / A[i][i];
//			b[k] = b[k] - L*b[i];
//			for (j = 0; j<N - 2; j++)
//				A[k][j] = A[k][j] - L*A[i][j];
//		}
//	}
//	cout << "��˹��Ԫ��õ���ϵ������:" << endl;
//	for (i = 0; i<N - 2; i++)
//	for (j = 0; j<N - 2; j++)
//		cout << A[i][j] << " ";
//	cout << endl;
//	cout << "��˹��Ԫ��ĵõ���b����:" << endl;
//	for (j = 0; j<N - 2; j++)
//		cout << b[j] << endl;
//	cout << endl;
//	//�ش�
//	m[N - 2] = b[N - 3] / A[N - 3][N - 3];
//	for (i = N - 3; i >= 1; i--)
//	{
//		sum = 0;
//		for (j = i + 1; j <= N - 2; j++)
//			sum = sum + A[i - 1][j - 1] * m[j];
//		m[i] = (b[i - 1] - sum) / A[i - 1][i - 1];
//	}
//	cout << "������ֵΪ:" << endl;
//	for (i = 0; i<N; i++)
//		cout << m[i] << " ";
//	cout << endl;
//	//����ֵ����s[i]
//	cout << "�������ֵ�ڵ�:" << endl;
//	for (j = 0; j<5; j++)
//		cin >> xx[j];
//	cout << endl;
//	cout << "��ֵ���Ӧ��x1��ֵ:" << endl;
//	for (j = 0; j<5; j++)
//	{
//		for (i = 0; i<N - 1; i++)
//		if (xx[j]>x0[i] && xx[j] <= x0[i + 1])
//			x1[j] = (xx[j] - x0[i]) / h[i];
//		cout << x1[j] << "      ";
//	}
//	cout << endl;
//	cout << "��ֵ��ĺ���ֵ:" << endl;
//	for (j = 0; j<5; j++)
//	{
//		for (i = 0; i<N - 1; i++)
//		if (xx[j]>x0[i] && xx[j] <= x0[i + 1])
//			yy[j] = czhs(y0[i], y0[i + 1], m[i], m[i + 1], x1[j], h[i]);
//		cout << yy[j] << "     ";
//	}
//	cout << endl;
//	return 0;
//}
////���alpha0
//double alpha0(double x)
//{
//	double y1;
//	y1 = 2 * x*x*x - 3 * x*x + 1;
//	return (y1);
//}
////���alpha1
//double alpha1(double x)
//{
//	double y2;
//	y2 = -2 * x*x*x + 3 * x*x;
//	return (y2);
//}
////���beta0
//double beta0(double x)
//{
//	double y3;
//	y3 = x*x*x - 2 * x*x + x;
//	return (y3);
//}
////���beta1
//double beta1(double x)
//{
//	double y4;
//	y4 = x*x*x - x*x;
//	return (y4);
//}
////����ֵ����
//double czhs(double a, double b, double m0, double m1, double x2, double h1)
//{
//	double s, p1, p2, p3, p4;
//	p1 = alpha0(x2);
//	p2 = alpha1(x2);
//	p3 = beta0(x2);
//	p4 = beta1(x2);
//	s = p1*a + p2*b + h1*p3*m0 + h1*p4*m1;
//	return(s);
//}
//
//
