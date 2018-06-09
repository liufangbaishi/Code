#pragma once
#include "dafault_alloc.h"
#include "Type_Traits.h"

template <class T>
void Destory(T* p)
{
	p->~T();
}

template <class Iterator>
void Destory(Iterator first, Iterator end)
{
	_Destory(first, end, TypeTraits<Iterator::ValueType>::PODType);
}
template <class Iterator>
void _Destory(Iterator first, Iterator end, Falsetype)
{}
template <class Iterator>
void _Destory(Iterator first, Iterator end, Truetype)
{
	while (first != end)
	{
		Destory(&(*first));
		first++;
	}
}

template <class T1, class T2>
void Construct(T1* p, const T2& value)
{
	new(p) T1(value);
}

