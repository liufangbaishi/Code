#ifndef __GAME_H__
#define __GAME_H__

#define ROWS 10   //定义棋盘的行数
#define COLS 10   //定义棋盘的列数

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

 void init_board(char board[ROWS][COLS], int row, int col);   //初始化棋盘
 void display(char board[ROWS][COLS], int row, int col);      //打印10*10的棋盘
 void player_move(char board[ROWS][COLS], int row, int col);  //玩家下棋
 void computer_move(char board[ROWS][COLS], int row, int col);//电脑下棋
 char check_win(char board[ROWS][COLS], int row, int col);    //判断是否赢

#endif //__GAME_H__