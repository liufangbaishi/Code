#define _CRT_SECURE_NO_WARNINGS
#include "CommentConvert.h"

void CommentConvert(FILE* pfIn, FILE* pfOut)
{
	enum STATE state = NUL_STATE;
	while (state != END_STATE)
	{
		switch (state)
		{
		case NUL_STATE:
			DoNulState(pfIn, pfOut, &state);
			break;
		case C_STATE:
			DoCState(pfIn, pfOut, &state);
			break;
		case CPP_STATE:
			DoCppState(pfIn, pfOut, &state);
			break;
		}
	}
}
void test()
{
	FILE* pfIn = 0;
	FILE* pfOut = 0;
	pfIn = fopen("input.c", "r");
	if (pfIn == NULL)
	{
		perror("open for read");
		exit(EXIT_FAILURE);
	}
	pfOut = fopen("output.c", "w");
	if (pfOut == NULL)
	{
		perror("open for write");
		fclose(pfIn);
		exit(EXIT_FAILURE);
	}
	CommentConvert(pfIn, pfOut);
	fclose(pfIn);
	fclose(pfOut);
}
int main()
{
	test();
	return 0;
}