#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _coords {
  int l;
  int c;
} coords;

typedef struct _plays {
  long score;
  int line;
  int col;
} plays;

void afonsosort(plays *arr, int N, int size, int increment, int increasing);

long evaluatescore(int *streak, int streaknumber, int *streaksymbol,
                   int symboltoplay);

long gamealreadyover(int *streak, int streaknumber, int *streaksymbol,
                     int symboltoplay);

long evaluateposition(int **board, int symboltoplay);

int verifygameover(int **board);

long verifyallplays(int **board, int symboltoplay);

#endif
