////2 ţ�ٷ�������Է�����Դ�������
//#include<iostream>
//#include<iomanip>
//#include<cmath>
//#define N 2
//using namespace std;
//int main()
//{
//	void ff(double xx[N], double yy[N]);
//	void ffjacobi(double xx[N], double ja[N][N]);
//	void inv_ffjacobi(double ja[N][N], double inv_ja[N][N]);
//	double x0[N], y0[N], ja[N][N], inv_ja[N][N], x1[N], sum, a, b;
//	int i, j, k = 0;
//	cout << "�������ʼֵ��" << endl;
//	for (i = 0; i<N; i++)
//		cin >> x0[i];
//	cout << endl;
//	do
//	{
//		k++;  //��������Ϊk
//		cout << "��" << k << "�ε���:" << endl;
//		ff(x0, y0);
//		ffjacobi(x0, ja);
//		inv_ffjacobi(ja, inv_ja);
//		for (i = 0; i<N; i++)
//		{
//			sum = 0;
//			for (j = 0; j<N; j++)
//				sum = sum + inv_ja[i][j] * y0[j];
//			x1[i] = x0[i] - sum;
//		}
//		a = fabs(x1[0] - x0[0]); b = fabs(x1[1] - x0[1]);
//		if (b>a)a = b;
//		for (i = 0; i<N; i++)
//		{
//			x0[i] = x1[i];
//			cout << "x(" << i + 1 << ")=" << x1[i] << endl;
//		}
//		cout << endl;
//	} while (a>0.000001);
//	cout << "������Ľ��ƽ�Ϊ��" << endl;
//	for (i = 0; i<N; i++)
//		cout << "x(" << i + 1 << ")=" << x1[i] << endl;
//	return 0;
//}
//void ff(double xx[N], double yy[N])  //���㺯��ֵ(yy)
//{
//	double x, y;
//	x = xx[0]; y = xx[1];
//	yy[0] = x*x + y*y - 4;
//	yy[1] = x*x - y*y - 1;
//}
//void ffjacobi(double xx[N], double ja[N][N])  //�����ſ˱Ⱦ���ja
//{
//	double x, y;
//	x = xx[0]; y = xx[1];
//	ja[0][0] = 2 * x; ja[0][1] = 2 * y;
//	ja[1][0] = 2 * x; ja[1][1] = 2 * y;
//}
//void inv_ffjacobi(double ja[N][N], double inv_ja[N][N])  //���������
//{
//	double inv[N][2*N], m;
//	int i, j, k;
//	//�����������
//	for (i = 0; i<N; i++)
//	{
//		for (j = 0; j<N; j++)
//			inv[i][j] = ja[i][j];
//		for (j = N; j<2*N; j++)
//		if (j == (i + N))inv[i][j] = 1;
//		else inv[i][j] = 0;
//	}
//	//�����б任
//	//ja��Ϊ�������;���
//	for (k = 0; k<N - 1; k++)  //�Ե�k��Ϊ������ʵ���б任
//	for (i = k + 1; i<N; i++)
//	{
//		m = inv[i][k] / inv[k][k]; //mΪ����ϵ��
//		for (j = k; j<2*N; j++)
//			inv[i][j] = inv[i][j] - m*inv[k][j];
//	}
//	//ja��Ϊ�Խ��;���
//	for (k = N - 1; k>0; k--)  //�Ե�k��Ϊ������ʵ���б任
//	for (i = k - 1; i >= 0; i--)
//	{
//		m = inv[i][k] / inv[k][k]; //mΪ����ϵ��
//		for (j = 2*N - 1; j >= k; j--)
//			inv[i][j] = inv[i][j] - m*inv[k][j];
//	}
//	//ja��Ϊ��λ����
//	for (i = N - 1; i >= 0; i--)
//	for (j = 2*N - 1; j >= 0; j--)
//		inv[i][j] = inv[i][j] / inv[i][i];
//	//��ja�������inv_ja[N][N]
//	for (i = 0; i<N; i++)
//	for (j = 0; j<N; j++)
//		inv_ja[i][j] = inv[i][j + N];
//}
//
