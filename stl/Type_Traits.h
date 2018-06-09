#pragma once

struct Truetype
{};

struct Falsetype
{};

template <class T>  //truetype���Զ������� falsetype�ǻ�������
struct TypeTraits 
{
	typedef Truetype PODType;
};

template <>
struct TypeTraits<int>
{
	typedef Falsetype PODType;
};

template <>
struct TypeTraits<char>
{
	typedef Falsetype PODType;
};

template <>
struct TypeTraits<char*>
{
	typedef Falsetype PODType;
};
