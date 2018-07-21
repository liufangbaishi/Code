//bool IsPOD(const char* TypeName)
//{
//	static char* p[] = { "int", "double", "char" };
//	for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
//	{
//		if (strcmp(p[i], TypeName) == 0)
//			return true;
//	}
//	return false;
//}
//template <class T>
//void Copy(T* dst, T* src, size_t size)
//{
//	if (IsPOD("int"))
//		memcpy(dst, src, size*sizeof(T));
//	else
//	{
//		for (size_t i = 0; i < size; i++)
//			dst[i] = src[i];
//	}
//}

/////////////////////////////////////////////////
//类型萃取
struct TrueType//内置类型设置为true
{
	static bool IsPODType()
	{
		return true;
	}
};
struct FalseType//自定义类型设置为false
{
	static bool IsPODType()
	{
		return false;
	}
};
template<class T>//模板类
struct TypeTraits//自定义类型为一般的，内置类型为特化的
{
	typedef FalseType PODType;
};
template<>
struct TypeTraits<int>//特化int
{
	typedef TrueType PODType;
};
template<>
struct TypeTraits<double>//特化double
{
	typedef TrueType PODType;
};
template<>
struct TypeTraits<char>//特化char
{
	typedef TrueType PODType;
};
template<>
struct TypeTraits<float>//特化float
{
	typedef TrueType PODType;
};
template <class T>
void Copy(T* dst, T* src, size_t size)
{
	if (TypeTraits<T>::PODType::IsPODType())
		memcpy(dst, src, size*sizeof(T));
	else
	{
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	}
}
void FunTest()
{
	int arr1[5] = { 1, 2, 3, 4, 5 };
	int arr2[5];
	Copy<int>(arr2, arr1, sizeof(arr1) / sizeof(arr1[0]));
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
		cout << arr2[i] << " ";
	cout << endl;

	string arr3[3] = { "aaa", "bbb", "ccc" };
	string arr4[3];
	Copy<string>(arr4, arr3, sizeof(arr3) / sizeof(arr3[0]));
	for (int i = 0; i < sizeof(arr3) / sizeof(arr3[0]); i++)
		cout << arr4[i] << " ";
	cout << endl;
}
int main()
{
	FunTest();
	return 0;
}

////////////////////////////////////////////////////
//另一种
struct TrueType
{};
struct FalseType
{};
template<class T>
struct TypeTraits//自定义类型
{
	typedef FalseType PODType;
};
template<>
struct TypeTraits<int>
{
	typedef TrueType PODType;
};

template<class T>
void _Copy(T* dst, T* src, size_t size, TrueType)
{
	memcpy(dst, src, sizeof(T)*size);
}
template<class T>
void _Copy(T* dst, T* src, size_t size, FalseType)
{
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
}
template <class T>
void Copy(T* dst, T* src, size_t size)
{
	_Copy(dst, src, size, TypeTraits<T>::PODType());
}
void FunTest()
{
	int arr1[] = { 1, 2, 3, 4, 5 };
	int arr2[5];
	Copy<int>(arr2, arr1, sizeof(arr1) / sizeof(arr1[0]));

	string s1[] = { "aaa", "bbb" };
	string s2[2];
	Copy<string>(s2, s1, sizeof(s1) / sizeof(s1[0]));
}
int main()
{
	FunTest();
	return 0;
}