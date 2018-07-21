#define _CRT_SECURE_NO_WARNINGS
#include "CommentConvert.h"
void DoNulState(FILE* pfIn, FILE* pfOut, enum STATE* s)
{
	int first = fgetc(pfIn);
	switch (first)
	{
	case '/':
	{
				int second = fgetc(pfIn);
				switch (second)
				{
				case '/':
					*s = CPP_STATE;//遇到//转换至C++状态
					fputc(first, pfOut);
					fputc(second, pfOut);
					break;
				case '*'://将/*转换成//，转换至C状态
					*s = C_STATE;
					fputc('/', pfOut);
					fputc('/', pfOut);
					break;
				default:
					//fputc(first, pfOut);
					fputc(second, pfOut);
				}
	}
		break;
	case EOF:
		*s = END_STATE;//文件结束，转换至结束状态
		break;
	default:
		fputc(first, pfOut);
		break;
	}
}
void DoCState(FILE* pfIn, FILE* pfOut, enum STATE* s)
{
	int first = fgetc(pfIn);
	switch (first)
	{
	case '*':
	{
				int second = fgetc(pfIn);
				switch (second)
				{
				case '/'://遇到*/转换至无状态，将*/去除或换行
				{
							*s = NUL_STATE;
							int third = fgetc(pfIn);
							if (third != '\n')
							{
								fputc('\n', pfOut);
								ungetc(third, pfIn);
							}
							else
							{
								fputc(third, pfOut);
							}
				}
					break;
				case '*':
					fputc(first, pfOut);
					ungetc(second, pfIn);
					break;
				default:
					fputc(first, pfOut);
					fputc(second, pfOut);
					break;
				}
	}
		break;
	case '\n'://多行注释的处理
		fputc(first, pfOut);
		fputc('/', pfOut);
		fputc('/', pfOut);
		break;
	case EOF://文件结束，转换至无状态
		*s = END_STATE;
		break;
	default:
		fputc(first, pfOut);
		break;
	}
}
void DoCppState(FILE* pfIn, FILE* pfOut, enum STATE* s)
{
	int first = fgetc(pfIn);
	switch (first)
	{
	case '\n':
		*s = NUL_STATE;//C++状态注释一行结束，转换至无状态
		fputc(first, pfOut);
		break;
	case EOF:
		*s = END_STATE;
		break;
	default:
		fputc(first, pfOut);
		break;
	}
}
