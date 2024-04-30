#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _coords {
  int l;
  int c;
} coords;

void afonsosort(long *arr, int N, int size, int increment, int increasing);

long spacesscore(int size);

long streakscore(int size);

double scoremultiplier(int samesymbolstreaks, int spacesbetween, int onetoplay);

long evaluatescore(int *streak, int streaknumber, int *streaksymbol,
                   int symboltoplay);

long gamealreadyover(int *streak, int streaknumber, int *streaksymbol,
                     int symboltoplay);

long evaluateposition(int **board, int symboltoplay);

int verifygameover(int **board);

long verifyallplays(int **board, int symboltoplay);

#endif
