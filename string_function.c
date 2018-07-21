#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
//strlen
int my_strlen(const char *str)//count计数
{
	int count = 0;
	while (*str++ != '\0')
		count++;
	return count;
}
int my_strlen(const char *str)//递归，不创建临时变量
{
	if (*str != '\0')
		return 1 + my_strlen(str + 1);
	else
		return 0;
}
int my_strlen(const char *str)//指针相减，库函数
{
	const char*end = str;
	while (*end++)
		;
	return end - str - 1;
}

//strcpy
char *my_strcpy(char *dst, const char *src)
{
	char *ret = dst;
	while (*dst++ = *src++)
		;
	return ret;
}

//strcat
char *my_strcat(char *dst, const char *src)
{
	char *ret = dst;
	while (*dst != '\0')
		dst++;
	while (*dst++ = *src++)
		;
	return ret;
}

//strcmp
int my_strcmp(const char*s1, const char*s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return 0;
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

//strstr
//"abcdef" ""
//"abcdef" "bcd"
//"abbbcdef" "bbc"
//"abcdef" "bce"
char *my_strstr(const char*str, const char*substr)
{
	const char *s1 = str;
	const char *s2 = substr;
	const char *cur = str;
	if (*substr == '\0')
		return (char*)str;
	while (*cur)
	{
		s1 = cur;
		s2 = substr;
		while (*s1 == *s2)
		{
			s1++;
			s2++;
		}
		if (*s2 == '\0')
			return (char*)cur;
		cur++;
	}
	return NULL;
}
int main()
{
	char str1[10] = "abbbcdef";
	char str2[10] = "bc";
	char *ret = my_strstr(str1, str2);
	printf("%s\n", ret);
	return 0;
}

void *my_memcpy(void* dst, const void* src, size_t count)
{
	void *ret = dst;
	while (count--)
	{
		*(char*)dst = *(char*)src;
		dst = (char*)dst + 1;
		src = (char*)src + 1;
		//++(char*)dst;
		//++(char*)src;
		((char*)dst)++;
		((char*)src)++;
	}
	return ret;
}
int main()
{
	int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int arr2[20];
	my_memcpy(arr2, arr1, 20);
	return 0;
}

void *my_memmove(void* dst, const void* src, size_t count)
{
	void *ret = dst;
	if (dst < src)
	{//前--后
		while (count--)
		{
			*(char*)dst = *(char*)src;
			dst = (char*)dst + 1;
			src = (char*)src + 1;
		}
	}
	else
	{//后--前
		while (count--)
		{
			*((char*)dst + count) = *((char*)src + count);
		}
	}
	return ret;
}
int main()
{
	int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	my_memmove(arr1+8, arr1, 20);
	return 0;
}