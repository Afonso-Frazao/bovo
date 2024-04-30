#include "head.h"

typedef struct _node {
  int size;
  long evalarr[30];
  struct _node *ptr;
} node;

int module(int num) {
  if (num >= 0) {
    return num;
  } else {
    return -num;
  }
}

int opositesymbol(int symbol) {
  if (symbol == 'X') {
    return 'O';
  } else {
    return 'X';
  }
}

long evaluateline(int **board, int symboltoplay, int line, int col) {
  long eval;
  int *streak, currentstreak, symbol;
  int *streaksymbol;
  int l, c, diag;

  eval = 0;

  for (c = 2, symbol = board[line][1], streaksymbol[0] = board[line][0],
      streak[0] = 1, currentstreak = 0;
       c < 23; c++) { // score the line
    if (board[l][c] == symbol) {
      streak[currentstreak]++;
    } else {
      currentstreak++;
      symbol = board[line][c];
      streaksymbol[currentstreak] = symbol;
      streak[currentstreak] = 1;
    }
  }
  eval += gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
  eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);

  for (l = 2, symbol = board[1][col], streaksymbol[0] = board[1][col],
      streak[0] = 1, currentstreak = 0;
       l < 23; l++) { // score the row
    if (board[l][col] == symbol) {
      streak[currentstreak]++;
    } else {
      currentstreak++;
      symbol = board[l][col];
      streaksymbol[currentstreak] = symbol;
      streak[currentstreak] = 1;
    }
  }
  eval += gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
  eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);

  if ((col - line + 1) > 0) { // score the diagonal 1
    diag = col - line + 1;
    if (diag <= 18) { // skip the unecessary diagonals
      for (l = 2, c = diag + 1, symbol = board[diag][1],
          streaksymbol[0] = board[diag][1], streak[0] = 1, currentstreak = 0;
           c < 23; l++, c++) {
        if (board[c][l] == symbol) {
          streak[currentstreak]++;
        } else {
          currentstreak++;
          symbol = board[c][l];
          streaksymbol[currentstreak] = symbol;
          streak[currentstreak] = 1;
        }
      }
      eval +=
          gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
      eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);
    }
  } else {
    diag = line - col + 1;
    if (diag <= 18) {
      for (l = diag + 1, c = 2, symbol = board[diag][1],
          streaksymbol[0] = board[diag][1], streak[0] = 1, currentstreak = 0;
           l < 23; l++, c++) {
        if (board[c][l] == symbol) {
          streak[currentstreak]++;
        } else {
          currentstreak++;
          symbol = board[c][l];
          streaksymbol[currentstreak] = symbol;
          streak[currentstreak] = 1;
        }
      }
      eval +=
          gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
      eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);
    }
  }

  if ((line + col - 1) <= 24) { // score the diagonal 2
    diag = line + col - 1;
    if (diag >= 5) {
      for (l = diag - 1, c = 2, symbol = board[diag][1],
          streaksymbol[0] = board[diag][1], streak[0] = 1, currentstreak = 0;
           l >= 1; l--, c++) {
        if (board[c][l] == symbol) {
          streak[currentstreak]++;
        } else {
          currentstreak++;
          symbol = board[c][l];
          streaksymbol[currentstreak] = symbol;
          streak[currentstreak] = 1;
        }
      }
      eval +=
          gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
      eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);
    }
  } else {
    diag = module(line - col) + 1;
    if (diag < 19) {
      for (l = 21, c = diag + 1, symbol = board[22][diag],
          streaksymbol[0] = board[22][diag], streak[0] = 1, currentstreak = 0;
           c < 23; l--, c++) {
        if (board[c][l] == symbol) {
          streak[currentstreak]++;
        } else {
          currentstreak++;
          symbol = board[c][l];
          streaksymbol[currentstreak] = symbol;
          streak[currentstreak] = 1;
        }
      }
      eval +=
          gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
      eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);
    }
  }

  return eval;
}

long verifyallplays(int **board, int symboltoplay) {
  long eval;
  long lineevalbefore, lineevalafter;
  int i, l, c;
  long *allplaysscore;
  int validplaysnumber;
  coords *playsstack;
  node *currentnode;

  allplaysscore = (long *)malloc(484 * sizeof(long));

  eval = evaluateposition(board, symboltoplay);
  validplaysnumber = 0;
  for (l = 1; l < 23; l++) {
    for (c = 1; c < 23; c++) {
      if (board[l][c] == 0) {
        lineevalbefore = evaluateline(board, symboltoplay, l, c);
        board[l][c] = symboltoplay;
        symboltoplay = opositesymbol(symboltoplay);
        lineevalafter = evaluateline(board, symboltoplay, l, c);
        allplaysscore[validplaysnumber] = eval + lineevalafter - lineevalafter;
        validplaysnumber++;
      }
    }
  }

  if (validplaysnumber == 0) { // TODO condition here
  }

  if (((validplaysnumber % 7) != 0) && (validplaysnumber > 7)) {
    if (symboltoplay == 'X') {
      afonsosort(allplaysscore, validplaysnumber, validplaysnumber, 7,
                 0); // when the symbol to play is X the array should be sorted
                     // from highest to lowest score
    } else {
      afonsosort(allplaysscore, validplaysnumber, validplaysnumber, 7, 1);
    }
  } else {
    if (symboltoplay == 'X') {
      afonsosort(allplaysscore, validplaysnumber, validplaysnumber, 1, 0);
    } else {
      afonsosort(allplaysscore, validplaysnumber, validplaysnumber, 1, 1);
    }
  }
  if (validplaysnumber >
      30) { // the array that will be processed can't be bigger than 30
    validplaysnumber = 30;
  }
  currentnode->size = validplaysnumber;
  for (i = 0; i < validplaysnumber; i++) {
    currentnode->evalarr[i] = allplaysscore[i];
  }
  currentnode->ptr = (node *)malloc(validplaysnumber * sizeof(node));
  currentnode = currentnode->ptr;
  for (i = 0; i < validplaysnumber; i++) {
    currentnode->size = 0;
  }

  return eval;
}
