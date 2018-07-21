#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
#include <string.h>


void init_board(char board[ROWS][COLS], int row, int col)  //��ʼ������
{
	memset(board, ' ', sizeof(board[0][0])*row*col);
}

void display(char board[ROWS][COLS], int row, int col)     //��ӡ����
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		printf(" %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", 
			board[i][0], board[i][1], board[i][2], board[i][3], board[i][4], board[i][5],
			board[i][6], board[i][7], board[i][8], board[i][9]);
		if (i < row - 1)
		{
			printf("---|---|---|---|---|---|---|---|---|---\n");
		}
	}
}

void player_move(char board[ROWS][COLS], int row, int col)   //�������
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("����������:> ");
		scanf("%d%d", &x, &y);
		if (((x>=1)&&(x<=row)) && ((y>=1) && (y<=col)))  
		{
			if (board[x-1][y-1] == ' ')
			{
				board[x-1][y-1] = 'X';
				break;
			}
			else
			{
				printf("�������ѱ��ã�����������\n");
			}
		}
		else
		{
			printf("������������\n");
		}
	}
}

void computer_move(char board[ROWS][COLS], int row, int col)   //��������
{
	while (1)
	{
		int x = rand() % 10;
		int y = rand() % 10;
		if (board[x][y] == ' ')
		{
			board[x][y] = '$';
			break;
		}
	}
}

int is_full(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < row; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;
			}
		}
	}
	return 1;
}

char check_win(char board[ROWS][COLS], int row, int col)    //�ж���Ӯ
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++) //����ͬ
	{
		for (j = 0; j < col-4; j++)
		{
			if ((board[i][j] == board[i][j+1]) && (board[i][j+1] == board[i][j+2]) && 
				(board[i][j+2] == board[i][j+3]) && (board[i][j+3] == board[i][j+4]) 
				&& (board[i][j+1] != ' '))
			{
				return board[i][j];
			}
		}
	}
	for (i = 0; i < row; i++) //����ͬ
	{
		for (j = 0; j < col-4; j++)
		{
			if ((board[j][i] == board[j+1][i]) && (board[j+1][i] == board[j+2][i]) &&
				(board[j+2][i] == board[j+3][i]) && (board[j+3][i] == board[j+4][i]) &&
				(board[j+1][i] != ' '))
			{
				return board[j][i];
			}
		}
	}
	for (i = 0; i < row-4; i++)
	{
		for (j = 0; j < col-4; j++)
		{
			if ((board[i][j] == board[i+1][j+1]) && (board[i+1][j+1] == board[i+2][j+2]) && 
				(board[i+2][j+2] == board[i+3][j+3]) && (board[i+3][j+3] == board[i+4][j+4]) &&
				(board[i+1][j+1] != ' '))//б��ͬ
			{
				return board[i][j];
			}
		}
	}
	for (i = 0; i < row-4; i++)
	{
		for (j = 0; j < col-4; j++)
		{
			if ((board[i][j+4] == board[i+1][j+3]) && (board[i+1][j+3] == board[i+2][j+2]) && 
				(board[i+2][j+2] == board[i+3][j+1]) && (board[i+3][j+1] == board[i+4][j]) &&
				(board[i+1][j+1] != ' '))
			{
				return board[i][j+4];
			}
		}
	}
	if (is_full(board, row, col) == 1)   //�������û�пգ�����q
	{
		return 'q';
	}
	return ' ';  //û��ûӮ�����ؿո񣬼�������
	
}