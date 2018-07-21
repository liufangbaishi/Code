#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

void menu()  //菜单打印
{
	printf("***************************\n");
	printf("****  1.play   0.exit  ****\n");
	printf("***************************\n");
}

void game()  //游戏函数
{
	char board[ROWS][COLS] = { 0 };
	char ret = 0;
	init_board(board, ROWS, COLS);      //初始化棋盘
	while (1)
	{
		printf("玩家移动,");
		player_move(board, ROWS, COLS);  //玩家下棋
		//display(board, ROWS, COLS);      //打印棋盘
		ret = check_win(board, ROWS, COLS);  //判断是否赢
		if (ret != ' ')
		{
			break;
		}
		system("cls");
		//printf("电脑移动\n");
		computer_move(board, ROWS, COLS);
		display(board, ROWS, COLS);
		ret = check_win(board, ROWS, COLS);
		if (ret != ' ')
		{
			break;
		}
	}
	if (ret == 'X')
	{
		printf("玩家赢\n");
	}
	else if (ret == '$')
	{
		printf("电脑赢\n");
	}
	else if (ret == 'q')
	{
		printf("平局\n");
	}
}

void test()   //测试函数
{
	int input = 0;
	srand((unsigned int)time(NULL));   
	do
	{
		menu();
		printf("请输入你的选择:> ");    //选择是否开始游戏
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf("输入有误\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}