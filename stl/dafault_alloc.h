#pragma once
#include <iostream>
#include "Alloc.hpp"
#include <string>
using namespace std;

#include <stdarg.h>
// #define _DEBUG_ // 不需要Debug
static string GetFileName(const string& path)
{
	char ch = '/' ;
#ifdef _WIN32   
	ch = '\\';
#endif
	size_t pos = path.rfind(ch);        
	if (pos == string::npos)               
		return path;        
	else
		return path.substr(pos + 1); 
}

// 用于调试追踪的trace log 
inline static void _trace_debug(const char * funcName, const char * fileName, int line, char* format, ...)
{
#ifdef _DEBUG_       
	fprintf(stdout, "[%s:%d]%s", GetFileName(fileName).c_str(), line, funcName);
// 输出用户信息       
	va_list args;     
	va_start(args, format);     
	vfprintf(stdout, format, args);      
	va_end(args); 
#endif 
}
#define __TRACE_DEBUG(...) _trace_debug(__FUNCDNAME__, __FILE__, __LINE__, __VA_ARGS__);


template <int inst>
class Default_Alloc_Template
{
private:
	enum { __ALIGN = 8 };
	enum { __MAX_BYTES = 128 };
	enum { __NFREE_LISTS = __MAX_BYTES / __ALIGN };
	union OBJ
	{
		union OBJ* free_list_link;
		char client[1];
	};
	static OBJ* free_list[__NFREE_LISTS];
	static char* start_free;
	static char* end_free;
	static size_t heap_size;
	static size_t ROUND_UP(size_t bytes)
	{
		return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1));// 向上调整至8的倍数
	}
	static size_t FREELIST_INDEX(size_t bytes)
	{
		return ((bytes + __ALIGN - 1) / __ALIGN - 1);// 计算相应的下标
	}

public:
	static void* Allocate(size_t n)
	{
		if (n > __MAX_BYTES)
		{
			__TRACE_DEBUG("一级空间配置申请%d字节内存\n", n);
			return MallocAllocTemplate<0>::Allocate(n);
		}
		int index = FREELIST_INDEX(n);
		OBJ* result = free_list[index];
		if (result == 0)
		{
			__TRACE_DEBUG("自由链表中没有%d的空间，去内存池申请内存\n", n);
			void* r = ReFill(ROUND_UP(n));
			__TRACE_DEBUG("内存池申请内存成功，返回给用户%d字节的内存\n", n);
			return r;
		}
		__TRACE_DEBUG("二级空间配置器有内存，申请到了%d内存\n", n);
		free_list[index] = result->free_list_link;
		return result;
	}
	static void DeAllocate(void* p, size_t n)
	{
		if (n > __MAX_BYTES)
		{
			__TRACE_DEBUG("一级空间配置器释放内存%d\n", n);
			MallocAllocTemplate<0>::DeAllocate(p, n);
			return;
		}
		int index = FREELIST_INDEX(n);
		__TRACE_DEBUG("二级空间配置器释放内存%d\n", n);
		((OBJ*)p)->free_list_link = free_list[index];
		free_list[index] = ((OBJ*)p);
	}

	static void* ReFill(size_t n);
	static char* ChunkAlloc(size_t size, int &nonjs);
};

template <int inst>
char* Default_Alloc_Template<inst>::start_free = NULL;
template <int inst>
char* Default_Alloc_Template<inst>::end_free = NULL;
template <int inst>
size_t Default_Alloc_Template<inst>::heap_size = 0;
template <int inst>
typename Default_Alloc_Template<inst>::OBJ* Default_Alloc_Template<inst>::free_list[
	Default_Alloc_Template<inst>::__NFREE_LISTS] = { 0 };

template <int inst>
void* Default_Alloc_Template<inst>::ReFill(size_t n)// 向内存池要内存
{
	int nobjs = 20;
	__TRACE_DEBUG("向内存池申请20个%d大小的内存\n", n);
	char* chunk = ChunkAlloc(n, nobjs);// 向内存池要20个n个字节的内存，其中1个给用户，19个给链表挂上

	if (nobjs == 1)
	{
		__TRACE_DEBUG("向内存池只申请到了1个%d的内存\n", n);
		return chunk;
	}
	int index = FREELIST_INDEX(n);
	OBJ* cur = (OBJ*)(chunk + n);
	OBJ* next = (OBJ*)((char*)cur + n);
	__TRACE_DEBUG("向内存池申请到了%d个%d大小的内存，将一个返回给用户，其余%d个挂到自由链表中\n", nobjs, n, nobjs-1);
	while (--nobjs)
	{
		cur->free_list_link = free_list[index];
		free_list[index] = cur;
		cur = next;
		next = (OBJ*)((char*)next + n);
	}
	return chunk;
}
template <int inst>
char* Default_Alloc_Template<inst>::ChunkAlloc(size_t size , int &nobjs)
{
	char* result = NULL;
	size_t total_bytes = size * nobjs;  // 需要nobjs个size大小的内存
	size_t bytes_left = end_free - start_free; // 内存池剩余内存

	if (bytes_left >= total_bytes)// 内存池的内存足够
	{
		result = start_free;
		start_free += total_bytes;
		__TRACE_DEBUG("内存池有足够的内存:%d\n", total_bytes);
		return result;
	}
	else if (bytes_left >= size)// 内存池只够一个或以上个size大小的内存
	{
		result = start_free;
		nobjs = bytes_left / size;
		total_bytes = nobjs * size;
		start_free += total_bytes;
		__TRACE_DEBUG("内存池有%d个%d大小的内存:共%d字节\n", nobjs, size, total_bytes);
		return result;
	}
	else // 内存池一个size大小的内存都没有
	{
		size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4); //内存池的内存不够，需要向系统要这么多内存
		// 先将内存池的剩余内存放置链表中
		if (bytes_left > 0)
		{
			__TRACE_DEBUG("内存池一个%d的空间都没有，先将内存池剩余内存放置自由链表\n", size);
			((OBJ*)start_free)->free_list_link = free_list[bytes_left];
			free_list[bytes_left] = (OBJ*)start_free;
		}
		start_free = (char*)malloc(bytes_to_get); // 向系统要内存
		__TRACE_DEBUG("内存池向系统要%d内存\n", bytes_to_get);
		if (start_free == 0)// 系统内存不够
		{
			// 去链表里找能用的内存
			for (int i = size; i < __MAX_BYTES; i += __ALIGN)
			{
				if (free_list[i] != NULL)
				{
					start_free = (char*)free_list[i];
					end_free = start_free + i;
					free_list[i] = free_list[i]->free_list_link;
				}
				__TRACE_DEBUG("系统没有足够内存，在自由链表找内存\n");
			}
			end_free = 0; // 如果底下的调用抛出异常，start_free返回0，end_free不置0就会出问题
			__TRACE_DEBUG("系统没有足够内存，自由链表没有足够内存，去以及空间配置器找内存\n");
			start_free = (char*)MallocAllocTemplate<0>::Allocate(bytes_to_get); // 山穷水尽，采用一级空间配置器
		}
		heap_size += bytes_to_get; // 调整heap_size
		end_free = start_free + bytes_to_get; // 一般至此，内存池已经有内存了，递归调用，给内存池分配内存，更新nobjs
		return ChunkAlloc(size, nobjs);
	}
}

typedef Default_Alloc_Template<0> DefaultAllocTemplate;

#ifdef USE_MALLOC
typedef MallocAlloc _Alloc;
#else
typedef DefaultAllocTemplate _Alloc;
#endif


template <class T, class Alloc = _Alloc>
class SimpleAlloc
{
public:
	static T* Allocate(size_t n)// 开辟n个大小为T的空间
	{
		return (0 == n) ? 0 : (T*)Alloc::Allocate(sizeof(T)*n);
	}
	static T* Allocate(void)// 开辟n个大小为T的空间
	{
		return (T*)Alloc::Allocate(sizeof(T));
	}
	static void DeAllocate(void* p, size_t n)
	{
		if(n != 0)
			Alloc::DeAllocate(p, n*sizeof(T));
	}
	static void DeAllocate(void* p)
	{
		return Alloc::DeAllocate(p, sizeof(T));
	}
};



//void test()
//{
//	int *p1 = (int*)SimpleAlloc<int, _Alloc>::Allocate(100);
//	SimpleAlloc<int, _Alloc>::DeAllocate(p1, 100);
//	int *p2 = (int*)SimpleAlloc<int, _Alloc>::Allocate(2);
//	SimpleAlloc<int, _Alloc>::DeAllocate(p2, 2);
//	int *p3 = (int*)SimpleAlloc<int, _Alloc>::Allocate(5);
//	int *p4 = (int*)SimpleAlloc<int, _Alloc>::Allocate(3);
//	SimpleAlloc<int, _Alloc>::DeAllocate(p3, 5);
//	SimpleAlloc<int, _Alloc>::DeAllocate(p4, 3);
//}