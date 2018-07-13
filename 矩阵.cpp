#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#if 0
template <class T, size_t N=3>
class SymmetricMatrix//�Գƾ���
{
public:
	SymmetricMatrix(T (&arr)[N][N])
		: _row(N)
		, _col(N)
	{
		_v.resize(((N + 1)*N) >> 1);
		int index = 0;
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j <= i; j++)
				_v[index++] = arr[i][j];
		}
	}
	T& Acess(int row, int col)
	{
		if (row < col)
			swap(row, col);
		size_t index = (1+row)*row/2 + col;
		return _v[index];
	}
	void Display()
	{
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
				cout << Acess(i, j) << " ";
			cout << endl;
		}
	}
	template <class T>
	friend ostream& operator<<(ostream& _cout, const SymmetricMatrix<T>& sm)
	{
		for (int i = 0; i < sm._row; i++)
		{
			for (int j = 0; j < sm._col; j++)
			{
				if (i < j)
					_cout << sm._v[(1 + j)*j / 2 + i ] << " ";
				else
					_cout << sm._v[(1 + i)*i / 2 + j] << " ";
			}
			_cout << endl;
		}
		return _cout;
	}
private:
	vector<T> _v;
	int _row;
	int _col;
};
int main()
{
	int arr[][3]=
	{ { 1, 2, 3 },
	  { 2, 1, 4 },
	  { 3, 4, 1 } };
	SymmetricMatrix<int> sm(arr);
	//sm.Display();
	cout << sm << endl;
	return 0;
}
#endif

#include <assert.h>
template <class T>
class SparseMatrix
{
public:
	template <class T>
	struct Trituple
	{
		Trituple(int row = 0, int col = 0, const T& data = T())
		: _row(row)
		, _col(col)
		, _data(data)
		{}
		int _row;
		int _col;
		T _data;
	};
	SparseMatrix()
	{}
	SparseMatrix(T *arr, int row, int col, T invalid)
		: _row(row)
		, _col(col)
		, _invalid(invalid)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (_invalid != arr[i*_col + j])
					_v.push_back(Trituple<T>(i, j, arr[i*col + j]));
			}
		}
	}
	T& Acess(size_t row, size_t col)
	{
		for (size_t i = 0; i < _v.size(); i++)
		{
			Trituple<T>& cur = _v[i];
			if (cur._row == row && cur._col == col)
				return cur._data;
		}
		return _invalid;
	}
	//T& Acess(size_t row, size_t col)
	//{
	//	vector<Trituple<T>>::iterator it = _v.begin();
	//	while (it != _v.end())
	//	{
	//		if (it->_row == row && it->_col == col)
	//			return it->_data;
	//		it++;
	//	}
	//	return _invalid;
	//}
	void Display()
	{
		for (size_t i = 0; i < _row; i++)
		{
			for (size_t j = 0; j < _col; j++)
				cout << Acess(i, j) << " ";
			cout << endl;
		}
	}
	template <class T>
	friend ostream& operator<<(ostream& _cout, const SparseMatrix<T>& sm)
	{
		size_t index = 0;
		for (int i = 0; i < sm._row; i++)
		{
			for (int j = 0; j < sm._col; j++)
			{
				if (index < sm._v.size() && sm._v[index]._row == i && sm._v[index]._col == j)
				{
					_cout << sm._v[index]._data << " ";
					index++;
				}
				else
					_cout << sm._invalid << " ";
			}
			_cout << endl;
		}
		return _cout;
	}
	SparseMatrix<T> operator+(const SparseMatrix<T>& sp)
	{
		assert(_row == sp._row&&_col == sp._col);//��ӵ���������������ͬ
		SparseMatrix<T> ret;//��Ӻ�Ľ��
		ret._row = _row;
		ret._col = _col;
		ret._invalid = _invalid;
		size_t leftIndex = 0, rightIndex = 0;//����
		size_t addrL = 0, addrR = 0;//��ַƫ��
		while (leftIndex < _v.size() && rightIndex < sp._v.size())
		{
			Trituple<T>& left = _v[leftIndex];
			const Trituple<T>& right = sp._v[rightIndex];
			addrL = left._row*_col + left._row;
			addrR = right._row*_col + right._row;
			if (addrL < addrR)//
			{
				ret._v.push_back(left);
				leftIndex++;
			}
			else if (addrL > addrR)
			{
				ret._v.push_back(right);
				rightIndex++;
			}
			else//��Ӧλ�ö���Ϊ0
			{
				Trituple<T> t(left);
				t._data += right._data;
				if (t._data != _invalid)//�������������Ϊ0����push_back
					ret._v.push_back(t);
				leftIndex++;
				rightIndex++;
			}
		}
		while (leftIndex < _v.size())//����������ʣ���Ԫ��
			ret._v.push_back(_v[leftIndex++]);
		while (rightIndex < _v.size())//�Ҿ��������ʣ���Ԫ��
			ret._v.push_back(_v[rightIndex++]);
		return ret;
	}
	SparseMatrix<T> Transport()//ʱ�临�Ӷ�N*Q  �ռ临�Ӷ�O(1)
	{
		SparseMatrix<T> sm;
		sm._row = _col;
		sm._col = _row;
		sm._invalid = _invalid;
		for (size_t i = 0; i < _col; i++)//N�У���һ�ֽ���Ϊ0����ЧԪ��push���ڶ��ֽ���ЧԪ����Ϊ1��push......
		{					
			for (size_t index = 0; index < _v.size(); index++)//Q����ЧԪ�ر���
			{
				Trituple<T>& cur = _v[index];
				if (cur._col == i)//��ȡ��i�е�����Ԫ��
					sm._v.push_back(Trituple<T>(cur._col, cur._row, cur._data));				
			}
		}
		//sm._v.resize(_v.size());//�ڶ������� Ĭ�Ϲ��캯��
		//for (size_t i = 0; i < _v.size(); i++)//ֻ�ǽ���ЧԪ�ص����л�������λ��û�б䣬��ת�ú��Ϊ�������ȷ���
		//{
		//	sm._v[i] = _v[i];
		//	//sm._v.push_back(_v[i]);
		//	swap(sm._v[i]._row, sm._v[i]._col);
		//}
		return sm;
	}

	SparseMatrix<T> Transport_F()//ʱ�临�Ӷ� M��N��Q��Ԫ��  N+Q �ռ临�Ӷ�O(N)
	{
		SparseMatrix<T> newSm;
		newSm._row = _col;
		newSm._col = _row;
		newSm._invalid = _invalid;
		newSm._v.resize(_v.size());

		int* count = new int[_col];//��¼ת�óɹ���ÿһ����ЧԪ�ظ���������ת��ǰÿһ��Ԫ�ظ���
		memset(count, 0, _col*sizeof(int));
		for (size_t i = 0; i < _v.size(); i++)
			count[_v[i]._col]++;//������к���Ϊ�±�

		int* addr = new int[_col];//ת�ú�ÿһ�е���ʼ��ַ���׵�ַ+����ÿһ�и���
		memset(addr, 0, _col*sizeof(int));
		for (size_t i = 1; i < _col; i++)
			addr[i] = addr[i - 1] + count[i - 1];

		for (size_t i = 0; i < _v.size(); i++)//ֱ�ӷ���Ԫ��
		{
			int& rowAddr = addr[_v[i]._col];//iԪ��Ӧ���ڵ��� 
			newSm._v[rowAddr] = _v[i];//����i��Ԫ�ش���
			swap(newSm._v[rowAddr]._row, newSm._v[rowAddr]._col);
			rowAddr++;
		}
		return newSm;
	}
private:
	vector<Trituple<T>> _v;
	size_t _row;
	size_t _col;
	T _invalid;
};
int main()
{
	int arr[6][5] = { 
		{ 1, 0, 3, 0, 5 }, 
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 1, 0, 3, 0, 5 }, 
		{ 0, 0, 0, 0, 0 }, 
		{ 0, 0, 0, 0, 0 }, };
	SparseMatrix<int> sm((int*)arr, sizeof(arr)/sizeof(arr[0]), sizeof(arr[0])/sizeof(arr[0][0]), 0);
	SparseMatrix<int> sm1;
	sm.Display();
	cout << endl;
	//sm1 = sm.Transport();
	sm1 = sm.Transport_F();
	sm1.Display();
	cout << endl;

	//int arr1[3][3] = {
	//	{ 1, 0, 0 },
	//	{ 0, 2, 0 },
	//	{ 0, 0, 0 } };
	//SparseMatrix<int> sm1((int*)arr1, sizeof(arr1)/sizeof(arr1[0]), sizeof(arr1[0])/sizeof(arr1[0][0]), 0);
	//sm1.Display();
	//cout << endl;
	//SparseMatrix<int> sm2;
	//sm2 = sm + sm1;
	//cout << sm2 << endl;
	//cout << sm << endl;
	return 0;
}