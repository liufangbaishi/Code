#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

void menu()  //�˵���ӡ
{
	printf("***************************\n");
	printf("****  1.play   0.exit  ****\n");
	printf("***************************\n");
}

void game()  //��Ϸ����
{
	char board[ROWS][COLS] = { 0 };
	char ret = 0;
	init_board(board, ROWS, COLS);      //��ʼ������
	while (1)
	{
		printf("����ƶ�,");
		player_move(board, ROWS, COLS);  //�������
		//display(board, ROWS, COLS);      //��ӡ����
		ret = check_win(board, ROWS, COLS);  //�ж��Ƿ�Ӯ
		if (ret != ' ')
		{
			break;
		}
		system("cls");
		//printf("�����ƶ�\n");
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
		printf("���Ӯ\n");
	}
	else if (ret == '$')
	{
		printf("����Ӯ\n");
	}
	else if (ret == 'q')
	{
		printf("ƽ��\n");
	}
}

void test()   //���Ժ���
{
	int input = 0;
	srand((unsigned int)time(NULL));   
	do
	{
		menu();
		printf("���������ѡ��:> ");    //ѡ���Ƿ�ʼ��Ϸ
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf("��������\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}