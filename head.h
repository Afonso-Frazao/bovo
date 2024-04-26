#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>

long spacesscore(int size);

long streakscore(int size);

double scoremultiplier(int samesymbolstreaks, int spacesbetween, int onetoplay);

long evaluatescore(int *streak, int streaknumber, int *streaksymbol,
                   int symboltoplay);

int gamealreadyover(int **board, int symboltoplay);

long evaluateposition(int **board, int symboltoplay);

int verifygameover(int **board);

#endif
