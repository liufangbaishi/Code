#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
#if 0
template<class T>
struct Less//降序
{
	bool operator()(const T& left, const T& right)
	{
		if (left < right)
			return true;
		return false;
	}
};
template<>
struct Less<char*>
{
	bool operator()(const char* left, const char* right)
	{
		if (strcmp(left,right)<0)
			return true;
		return false;
	}
};
template<class T>
struct Greater//升序
{
	bool operator()(const T& left, const T& right)
	{
		if (left > right)
			return true;
		return false;
	}
};
template<>
struct Greater<char*>
{
	bool operator()(const char* left, const char* right)
	{
		if (strcmp(left, right)>0)
			return true;
		return false;
	}
};
template <typename T, class Compare>
void BubbleSort(T* arr, int size)
{
	if (arr == NULL)
		return;
	bool IsChange = false;//定义一个布尔变量，如果一轮当中没有交换时，说明顺序已将是排好的，直接跳出去
	for (int i = 0; i < size - 1; i++)
	{
		IsChange = false;
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (Compare()(arr[j], arr[j+1]))//升序
			{
				IsChange = true;
				swap(arr[j], arr[j + 1]);
			}
		}
		if (!IsChange)
			return;
	}
}
//template<>
//void BubbleSort<char*, Less<char*>>(char* arr[], int size)
//{
//	if (arr == NULL)
//		return;
//	char* tmp = 0;
//	bool IsChange = false;
//	for (int i = 0; i < size - 1; i++)
//	{
//		IsChange = false;
//		for (int j = 0; j < size - 1 - i; j++)
//		{
//			if (strcmp(arr[j], arr[j + 1]) < 0)
//			{
//				IsChange = true;
//				swap(arr[j], arr[j + 1]);
//			}
//		}
//		if (!IsChange)
//			return;
//	}
//}
//template<>
//void BubbleSort<char*, Greater<char*>>(char* arr[], int size)
//{
//	if (arr == NULL)
//		return;
//	char* tmp = 0;
//	bool IsChange = false;
//	for (int i = 0; i < size - 1; i++)
//	{
//		IsChange = false;
//		for (int j = 0; j < size - 1 - i; j++)
//		{
//			if (strcmp(arr[j], arr[j + 1]) > 0)
//			{
//				IsChange = true;
//				swap(arr[j], arr[j + 1]);
//			}
//		}
//		if (!IsChange)
//			return;
//	}
//}
void FunTest()
{
	//string arr1[] = { "aaa", "bbb", "ccc" };
	//BubbleSort<string, Less<string>>(arr1, 3);
	//for (int i = 0; i < 3; i++)
	//	cout << arr1[i] << " ";
	//cout << endl;

	char* arr2[] = { "aaa", "zzz", "ccc" };
	BubbleSort<char*, Greater<char*>>(arr2, 3);
	for (int i = 0; i < 3; i++)
		cout << arr2[i] << " ";
	cout << endl;

	//double arr3[] = { 7, 4, 1, 8, 5, 2, 9, 6, 3 };
	//BubbleSort<double, Greater<double>>(arr3, 9);
	//for (int i = 0; i < 9; i++)
	//	cout << arr3[i] << " ";
	//cout << endl;
}
int main()
{
	FunTest();
	return 0;
}

#endif