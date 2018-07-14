#pragma once
#include <malloc.h>
#include <iostream>
using namespace std;

typedef void(*pMallocHandle)();
template <int inst>
class MallocAllocTemplate
{
public:
	static void* Allocate(size_t size)
	{
		void* result = malloc(size);
		if (result == NULL)
			result = OOM_Malloc(size);
		return result;
	}

	static void DeAllocate(void* p, size_t size)
	{
		free(p);
	}

	static void* ReAllocate(void* p, size_t oldSize, size_t newSize)
	{
		void* result = realloc(p, newSize);
		if (NULL == result)
			result = OOM_Realloc(p, newSize);
		return result;
	}

	static pMallocHandle setMallocHandle(pMallocHandle mallocHandle)
	{
		pMallocHandle old = _mallocHandle;
		_mallocHandle = mallocHandle;
		return old;
	}
private:
	
	static void* OOM_Malloc(size_t size)
	{
		pMallocHandle mallocHandle;
		for (;;)
		{
			mallocHandle = _mallocHandle;
			if (mallocHandle == NULL)
				throw std::bad_alloc();
			mallocHandle();
			void* res = malloc(size);
			if (res)
				return res;
		}
	}

	static void* OOM_Realloc(void* p, size_t size)
	{
		pMallocHandle mallocHandle;
		for (;;)
		{
			mallocHandle = _mallocHandle;
			if (mallocHandle == NULL)
				throw std::bad_alloc();
			mallocHandle();
			void* res = realloc(p, size);
			if (res)
				return res;
		}
	}
private:
	static pMallocHandle _mallocHandle;
};
pMallocHandle MallocAllocTemplate<0>::_mallocHandle = NULL;

void Handle()
{
	cout << "¿Õ¼ä²»×ã" << endl;
}

typedef MallocAllocTemplate<0> MallocAlloc;
//void test()
//{
//	int* p = (int*)MallocAlloc::Allocate(sizeof(int)* 5);
//	for (int i = 0; i < 5; i++)
//		p[i] = i;
//	int* tmp = (int*)MallocAlloc::ReAllocate(p, sizeof(int)* 10);
//	p = tmp;
//	for (int i = 0; i < 10; i++)
//		p[i] = i;
//	MallocAlloc::DeAllocate(p);
//
//	MallocAlloc::setMallocHandle(Handle);
//	p = (int*)MallocAlloc::Allocate(191234456789);
//	MallocAlloc::DeAllocate(p);
//}
