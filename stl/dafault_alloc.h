#pragma once
#include <iostream>
#include "Alloc.hpp"
#include <string>
using namespace std;

#include <stdarg.h>
// #define _DEBUG_ // ����ҪDebug
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

// ���ڵ���׷�ٵ�trace log 
inline static void _trace_debug(const char * funcName, const char * fileName, int line, char* format, ...)
{
#ifdef _DEBUG_       
	fprintf(stdout, "[%s:%d]%s", GetFileName(fileName).c_str(), line, funcName);
// ����û���Ϣ       
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
		return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1));// ���ϵ�����8�ı���
	}
	static size_t FREELIST_INDEX(size_t bytes)
	{
		return ((bytes + __ALIGN - 1) / __ALIGN - 1);// ������Ӧ���±�
	}

public:
	static void* Allocate(size_t n)
	{
		if (n > __MAX_BYTES)
		{
			__TRACE_DEBUG("һ���ռ���������%d�ֽ��ڴ�\n", n);
			return MallocAllocTemplate<0>::Allocate(n);
		}
		int index = FREELIST_INDEX(n);
		OBJ* result = free_list[index];
		if (result == 0)
		{
			__TRACE_DEBUG("����������û��%d�Ŀռ䣬ȥ�ڴ�������ڴ�\n", n);
			void* r = ReFill(ROUND_UP(n));
			__TRACE_DEBUG("�ڴ�������ڴ�ɹ������ظ��û�%d�ֽڵ��ڴ�\n", n);
			return r;
		}
		__TRACE_DEBUG("�����ռ����������ڴ棬���뵽��%d�ڴ�\n", n);
		free_list[index] = result->free_list_link;
		return result;
	}
	static void DeAllocate(void* p, size_t n)
	{
		if (n > __MAX_BYTES)
		{
			__TRACE_DEBUG("һ���ռ��������ͷ��ڴ�%d\n", n);
			MallocAllocTemplate<0>::DeAllocate(p, n);
			return;
		}
		int index = FREELIST_INDEX(n);
		__TRACE_DEBUG("�����ռ��������ͷ��ڴ�%d\n", n);
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
void* Default_Alloc_Template<inst>::ReFill(size_t n)// ���ڴ��Ҫ�ڴ�
{
	int nobjs = 20;
	__TRACE_DEBUG("���ڴ������20��%d��С���ڴ�\n", n);
	char* chunk = ChunkAlloc(n, nobjs);// ���ڴ��Ҫ20��n���ֽڵ��ڴ棬����1�����û���19�����������

	if (nobjs == 1)
	{
		__TRACE_DEBUG("���ڴ��ֻ���뵽��1��%d���ڴ�\n", n);
		return chunk;
	}
	int index = FREELIST_INDEX(n);
	OBJ* cur = (OBJ*)(chunk + n);
	OBJ* next = (OBJ*)((char*)cur + n);
	__TRACE_DEBUG("���ڴ�����뵽��%d��%d��С���ڴ棬��һ�����ظ��û�������%d���ҵ�����������\n", nobjs, n, nobjs-1);
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
	size_t total_bytes = size * nobjs;  // ��Ҫnobjs��size��С���ڴ�
	size_t bytes_left = end_free - start_free; // �ڴ��ʣ���ڴ�

	if (bytes_left >= total_bytes)// �ڴ�ص��ڴ��㹻
	{
		result = start_free;
		start_free += total_bytes;
		__TRACE_DEBUG("�ڴ�����㹻���ڴ�:%d\n", total_bytes);
		return result;
	}
	else if (bytes_left >= size)// �ڴ��ֻ��һ�������ϸ�size��С���ڴ�
	{
		result = start_free;
		nobjs = bytes_left / size;
		total_bytes = nobjs * size;
		start_free += total_bytes;
		__TRACE_DEBUG("�ڴ����%d��%d��С���ڴ�:��%d�ֽ�\n", nobjs, size, total_bytes);
		return result;
	}
	else // �ڴ��һ��size��С���ڴ涼û��
	{
		size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4); //�ڴ�ص��ڴ治������Ҫ��ϵͳҪ��ô���ڴ�
		// �Ƚ��ڴ�ص�ʣ���ڴ����������
		if (bytes_left > 0)
		{
			__TRACE_DEBUG("�ڴ��һ��%d�Ŀռ䶼û�У��Ƚ��ڴ��ʣ���ڴ������������\n", size);
			((OBJ*)start_free)->free_list_link = free_list[bytes_left];
			free_list[bytes_left] = (OBJ*)start_free;
		}
		start_free = (char*)malloc(bytes_to_get); // ��ϵͳҪ�ڴ�
		__TRACE_DEBUG("�ڴ����ϵͳҪ%d�ڴ�\n", bytes_to_get);
		if (start_free == 0)// ϵͳ�ڴ治��
		{
			// ȥ�����������õ��ڴ�
			for (int i = size; i < __MAX_BYTES; i += __ALIGN)
			{
				if (free_list[i] != NULL)
				{
					start_free = (char*)free_list[i];
					end_free = start_free + i;
					free_list[i] = free_list[i]->free_list_link;
				}
				__TRACE_DEBUG("ϵͳû���㹻�ڴ棬�������������ڴ�\n");
			}
			end_free = 0; // ������µĵ����׳��쳣��start_free����0��end_free����0�ͻ������
			__TRACE_DEBUG("ϵͳû���㹻�ڴ棬��������û���㹻�ڴ棬ȥ�Լ��ռ����������ڴ�\n");
			start_free = (char*)MallocAllocTemplate<0>::Allocate(bytes_to_get); // ɽ��ˮ��������һ���ռ�������
		}
		heap_size += bytes_to_get; // ����heap_size
		end_free = start_free + bytes_to_get; // һ�����ˣ��ڴ���Ѿ����ڴ��ˣ��ݹ���ã����ڴ�ط����ڴ棬����nobjs
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
	static T* Allocate(size_t n)// ����n����СΪT�Ŀռ�
	{
		return (0 == n) ? 0 : (T*)Alloc::Allocate(sizeof(T)*n);
	}
	static T* Allocate(void)// ����n����СΪT�Ŀռ�
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