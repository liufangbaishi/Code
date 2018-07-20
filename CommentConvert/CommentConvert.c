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
					*s = CPP_STATE;//����//ת����C++״̬
					fputc(first, pfOut);
					fputc(second, pfOut);
					break;
				case '*'://��/*ת����//��ת����C״̬
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
		*s = END_STATE;//�ļ�������ת��������״̬
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
				case '/'://����*/ת������״̬����*/ȥ������
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
	case '\n'://����ע�͵Ĵ���
		fputc(first, pfOut);
		fputc('/', pfOut);
		fputc('/', pfOut);
		break;
	case EOF://�ļ�������ת������״̬
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
		*s = NUL_STATE;//C++״̬ע��һ�н�����ת������״̬
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
