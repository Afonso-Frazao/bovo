#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>

int gamealreadyover(int **board, int symboltoplay);

int evaluateposition(int **board, int symboltoplay);

int verifygameover(int **board);

#endif
