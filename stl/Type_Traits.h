#pragma once

struct Truetype
{};

struct Falsetype
{};

template <class T>  //truetype是自定义类型 falsetype是基本类型
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
