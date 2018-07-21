#ifndef __GAME_H__
#define __GAME_H__

#define ROWS 10   //�������̵�����
#define COLS 10   //�������̵�����

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

 void init_board(char board[ROWS][COLS], int row, int col);   //��ʼ������
 void display(char board[ROWS][COLS], int row, int col);      //��ӡ10*10������
 void player_move(char board[ROWS][COLS], int row, int col);  //�������
 void computer_move(char board[ROWS][COLS], int row, int col);//��������
 char check_win(char board[ROWS][COLS], int row, int col);    //�ж��Ƿ�Ӯ

#endif //__GAME_H__