#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
void PrintArr(int *arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void InsertSort(int *arr, size_t size)//插入排序 
{
	if (NULL == arr || size == 1)
		return;
	for (size_t i = 0; i < size; i++)
	{
		int key = arr[i];
		int end = i - 1;
		while (end >= 0 && key < arr[end])
		{
			arr[end + 1] = arr[end];
			end--;
		}
		arr[end + 1] = key;
	}
}

void InsertSort_B(int *arr, size_t size)
{//插入排序2 使用二分查找的思想
	if (NULL == arr || size == 1)
		return;
	for (size_t i = 0; i < size; i++)
	{
		int key = arr[i];
		int left = 0;
		int right = i - 1;
		while (left <= right)//二分查找的思想
		{
			int mid = left + ((right - left) >> 1);
			if (key < arr[mid])
				right = mid - 1;
			else
				left = mid + 1;
		}
		int end = i - 1;
		while (end >= left)//将left到end之间的元素全部搬移
		{
			arr[end + 1] = arr[end];
			end--;
		}
		arr[left] = key;
	}
}

void ShellSort(int *arr, size_t size)
{//希尔排序，分组插入排序，间隔为gap=gap/4+1
	if (NULL == arr || size == 1)
		return;
	int gap = size;
	while (gap > 1)
	{
		gap = gap/4 + 1;
		for (size_t i = gap; i < size; i++)
		{
			int key = arr[i];
			int end = i - gap;
			while (end >= 0 && key < arr[end])
			{
				arr[end + gap] = arr[end];
				end -= gap;
			}
			arr[end + gap] = key;
		}
	}
}

void SelectSort(int *arr, size_t size)//选择排序 将关键字最大的找出来，与最后的关键字交换
{
	for (size_t i = 0; i < size - 1; i++)
	{
		size_t maxPos = 0;
		for (size_t j = 0; j < size - i; j++)
		{
			if (arr[j] > arr[maxPos])
				maxPos = j;
		}
		if (arr[maxPos] != size - i)
			swap(arr[maxPos], arr[size-i-1]);
	}
}

void SelectSort_B(int *arr, size_t size)
{//选择排序2 两边同时交换，将一轮中最小的放前面，最大的放后面
	size_t begin = 0;
	size_t end = size - 1;
	while (begin <= end)
	{
		size_t maxPos = begin;
		size_t minPos = begin;
		for (size_t j = begin + 1; j <= end; j++)
		{
			if (arr[j] > arr[maxPos])
				maxPos = j;
			if (arr[j] < arr[minPos])
				minPos = j;
		}
		if (maxPos != end)
			swap(arr[maxPos], arr[end]);
		if (minPos == end)
			minPos = maxPos;
		if (minPos != begin)
			swap(arr[minPos], arr[begin]);
		begin++;
		end--;
	}
}

void Adjust(int *arr, size_t size, size_t parent)
{
	size_t child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1<size && arr[child]<arr[child + 1])
			child = child + 1;
		if (arr[parent] < arr[child])
		{
			swap(arr[parent], arr[child]);
			parent = child;
			child = child * 2 + 1;
		}
		else
			return;
	}
}
void HeapSort(int *arr, size_t size)
{
	//创建堆--大堆
	int root = (size - 2) >> 1;
	for (; root >= 0; root--)
		Adjust(arr, size, root);
	//调整排序
	for (size_t i = 0; i < size; i++)
	{
		swap(arr[0], arr[size-1-i]);
		Adjust(arr, size-1-i, 0);
	}
}

size_t GetMid(int *arr, size_t left, size_t right)
{
	size_t mid = left + ((right - left) >> 1);
	if (arr[left] < arr[right])
	{
		if (arr[mid] > arr[right])
			return right;
		else
			return left;
	}
	else
	{
		if (arr[mid] < arr[right])
			return right;
		else
			return left;
	}
}
int Pation1(int *arr, size_t left, size_t right)
{
	size_t begin = left;
	size_t tmp = GetMid(arr, left, right);

	if (arr[tmp] != arr[right-1])
		swap(arr[tmp], arr[right-1]);
	size_t end = right - 1;
	int key = arr[end];
	while (begin < end)
	{
		while (begin < end && arr[begin] <= key)
			begin++;
		while (begin < end && arr[end] >= key)
			end--;
		if (begin < end)
			swap(arr[begin], arr[end]);
	}
	swap(arr[begin], arr[right - 1]);
	return begin;
}
int Pation2(int *arr, size_t left, size_t right)
{
	size_t begin = 0;
	size_t end = right - 1;
	int key = arr[end];
	while (begin < end)
	{
		while (begin < end && arr[begin] <= key)
			begin++;
		if (begin < end)
			arr[end--] = arr[begin];
		while (begin < end && arr[end] >= key)
			end--;
		if (begin < end)
			arr[begin++] = arr[end];
	}
	arr[begin] = key;
	return begin;
}
int Pation3(int *arr, size_t left, size_t right)
{
	int cur = 0;
	int pre = cur - 1;
	int size = right - left;
	int key = arr[right - 1];
	while (cur < size)
	{
		if (arr[cur] < key && ++pre != cur)
			swap(arr[pre], arr[cur]);
		else 
			cur++;
	}
	if (pre < cur)
		swap(arr[pre+1], arr[right-1]);
	return pre+1;
}
void QuickSort(int *arr, int left, int right)
{
	/*if (right - left < 16)
		InsertSort(arr, right - left);*/
	if (left < right)
	{
		//int div = Pation1(arr, left, right);
		int div = Pation3(arr, left, right);
		QuickSort(arr, left, div);
		QuickSort(arr, div + 1, right);
	}
}

void Merge(int *arr, int left, int mid, int right, int *temp)
{
	int index1 = left;
	int index2 = mid;
	int index = left;
	while (index1<mid && index2<right)
	{
		if (arr[index1] < arr[index2])
			temp[index++] = arr[index1++];
		else
			temp[index++] = arr[index2++];
	}
	while (index1 < mid)
		temp[index++] = arr[index1++];
	while (index2 < right)
		temp[index++] = arr[index2++];
	memcpy(arr+left, temp+left, (right-left)*sizeof(int));
}
void _MergeSort(int *arr, int left, int right, int *temp)
{
	if (left+1 < right)
	{
		int mid = left + ((right - left) >> 1);
		_MergeSort(arr, left, mid, temp);
		_MergeSort(arr, mid, right, temp);
		Merge(arr, left, mid, right, temp);
	}
}
void MergeSort(int *arr, size_t size)//归并排序
{
	int *temp = new int[size];
	_MergeSort(arr, 0, size, temp);
	delete[] temp;
}
void MergeSortN(int *arr, int size)//非递归的归并排序
{
	int *temp = new int[size];
	int gap = 1;
	while (gap < size)
	{
		for (int i = 0; i < size; i += 2*gap)
		{
			int left = i;
			int mid = left + gap;
			int right = mid + gap;
			if (mid > size)
				mid = size;
			if (right > size)
				right = size;
			Merge(arr, left, mid, right, temp);
		}
		gap *= 2;
	}
}

void CountSort(int *arr, int size)
{
	//找范围
	int minData = arr[0];
	int maxData = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (arr[i] < minData)
			minData = arr[i];
		if (arr[i]> maxData)
			maxData = arr[i];
	}
	//辅助空间
	int range = maxData - minData + 1;
	int *pCount = new int[range];
	memset(pCount, 0, sizeof(int)*range);
	//统计出现次数
	for (int i = 0; i < size; i++)
		pCount[arr[i]-minData]++;
	//回收
	int index = 0;
	for (int i = 0; i < range; i++)
	{
		while (pCount[i]--)
			arr[index++] = i + minData;
	}
}

//void RadixSort(int *arr, int size)
//{
//
//}

void Test()
{
	//int arr[5] = { 1, 7, 5, 3, 9 };
	int arr[10] = { 2, 0, 4, 9, 3, 6, 8, 7, 1, 5 };
	//int arr[] = { 998, 997, 998, 999, 999, 956, 954, 956, 954, 888 };
	int size = sizeof(arr) / sizeof(arr[0]);
	PrintArr(arr, size);
	//CountSort(arr, size);
	//MergeSortN(arr, size);
	//MergeSort(arr, size);
	QuickSort(arr, 0, size);
	//HeapSort(arr, size);
	//SelectSort_B(arr, size);
	//SelectSort(arr, size);
	//InsertSort_B(arr, size);
	//InsertSort(arr, size);
	//ShellSort(arr, size);
	PrintArr(arr, size);
}

int main()
{
	Test();
	return 0;
}