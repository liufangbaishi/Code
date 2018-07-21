#ifndef __COMMEENT_CONVERT_H__
#define __COMMEENT_CONVERT_H__

#include <stdio.h>
#include <stdlib.h>
enum STATE
{
	NUL_STATE,
	C_STATE,
	CPP_STATE,
	END_STATE
};

void DoNulState(FILE* pfIn, FILE* pfOut, enum STATE* state);
void DoCState(FILE* pfIn, FILE* pfOut, enum STATE* state);
void DoCppState(FILE* pfIn, FILE* pfOut, enum STATE* state);

#endif//__COMMEENT_CONVERT_H__
