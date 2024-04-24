#include "head.h"

int evaluatescore(int *streak, int *spaces, int symbol, int symboltoplay,
                  int currentstreak, int currentspace) {
  return 0;
}

int gamealreadyover(int **board, int symboltoplay) { return 0; }

int evaluateposition(int **board, int symboltoplay) {
  int eval; // The 'X' will get a positive eval while the 'O' will get a
            // negative onel and then they will add
  int *streak, currentstreak, *spaces, currentspace, symbol,
      lastwassymbol; // lastwassymbol for when the last board square verified
                     // was a symbol
  int lastwasspace, firstwasspace;
  long score;
  int l, c;

  /*for (l = 1,symbol = 0, currentspace = 0, lastwassymbol = 0, score = 0;
       l < 23; l++) {
    for (c = 1; c < 23; c++) {
      if (board[l][c] == 0) {
        if (lastwassymbol == 1) {
          if (currentspace ==
              0) { // change the currentspace from 0 to 1 or from 1 to 0
            currentspace++;
          } else {
            currentspace = 0;
          }
          lastwassymbol = 0;
          lastwasspace = 1;
          symbol = 0;
          spaces[currentspace] = 1;
        } else {
          spaces[currentspace]++;
        }
      } else if (board[l][c] == symbol) {
        streak++;
      } else if (board[l][c] == 'X') {
        if (lastwasspace == 1) {
          score += evaluatescore(streak, spaces, symbol, symboltoplay,
                                 currentstreak, currentspace);
        }
        symbol = 'X';
        streak = 1;
        lastwassymbol = 1;
        lastwasspace = 0;
      } else if (board[l][c] == 'O') {
        symbol = 'O';
        streak = 1;
        lastwassymbol = 1;
      }
    }
  }*/

  for (l = 1; l < 23; l++) {
    for (c = 1, symbol = 0, currentspace = 0, currentstreak = 0, symbol = 0;
         c < 23; c++) {
    }
  }

  return eval;
}

int verifygameover(int **board) {
  int i, j, diag;
  int streak, symbol;

  for (streak = 0, symbol = 'X', i = 1; i < 23; i++) { // verify lines
    for (j = 1; j < 23; j++) {
      if (board[i][j] == symbol) {
        streak++;
      } else if (board[i][j] != 0) {
        streak = 1;
        symbol = board[i][j];
      } else {
        streak = 0;
      }
      if (streak == 5) {
        board[i][j] = -symbol;
        board[i][j - 1] = -symbol;
        board[i][j - 2] = -symbol;
        board[i][j - 3] = -symbol;
        board[i][j - 4] = -symbol;

        return 1;
      }
    }
  }

  for (streak = 0, symbol = 'X', i = 1; i < 23; i++) { // verify rows
    for (j = 1; j < 23; j++) {
      if (board[j][i] == symbol) {
        streak++;
      } else if (board[j][i] != 0) {
        streak = 1;
        symbol = board[j][i];
      } else {
        streak = 0;
      }
      if (streak == 5) {
        board[j][i] = -symbol;
        board[j - 1][i] = -symbol;
        board[j - 2][i] = -symbol;
        board[j - 3][i] = -symbol;
        board[j - 4][i] = -symbol;

        return 1;
      }
    }
  }

  for (streak = 0, symbol = 'X', diag = 18;
       diag >= 1; // TODO verify diag initialization value
       diag--) {  // verify diagonal 1
    for (i = 1, j = diag; j < 23; i++, j++) {
      if (board[i][j] == symbol) {
        streak++;
      } else if (board[i][j] != 0) {
        streak = 1;
        symbol = board[i][j];
      } else {
        streak = 0;
      }
      if (streak == 5) {
        board[i][j] = -symbol;
        board[i - 1][j - 1] = -symbol;
        board[i - 2][j - 2] = -symbol;
        board[i - 3][j - 3] = -symbol;
        board[i - 4][j - 4] = -symbol;

        return 1;
      }
    }
  }

  for (streak = 0, symbol = 'X', diag = 2; diag < 19;
       diag++) { // verify diagonal 1
    for (i = diag, j = 1; i < 23; i++, j++) {
      if (board[i][j] == symbol) {
        streak++;
      } else if (board[i][j] != 0) {
        streak = 1;
        symbol = board[i][j];
      } else {
        streak = 0;
      }
      if (streak == 5) {
        board[i][j] = -symbol;
        board[i - 1][j - 1] = -symbol;
        board[i - 2][j - 2] = -symbol;
        board[i - 3][j - 3] = -symbol;
        board[i - 4][j - 4] = -symbol;

        return 1;
      }
    }
  }

  for (streak = 0, symbol = 'X', diag = 5; diag < 23;
       diag++) { // verify diagonal 2
    for (i = diag, j = 1; i >= 1; i--, j++) {
      if (board[i][j] == symbol) {
        streak++;
      } else if (board[i][j] != 0) {
        streak = 1;
        symbol = board[i][j];
      } else {
        streak = 0;
      }
      if (streak == 5) {
        board[i][j] = -symbol;
        board[i + 1][j - 1] = -symbol;
        board[i + 2][j - 2] = -symbol;
        board[i + 3][j - 3] = -symbol;
        board[i + 4][j - 4] = -symbol;

        return 1;
      }
    }
  }

  for (streak = 0, symbol = 'X', diag = 2; diag < 19;
       diag++) { // verify diagonal 2
    for (i = 22, j = diag; j < 23; i--, j++) {
      if (board[i][j] == symbol) {
        streak++;
      } else if (board[i][j] != 0) {
        streak = 1;
        symbol = board[i][j];
      } else {
        streak = 0;
      }
      if (streak == 5) {
        board[i][j] = -symbol;
        board[i + 1][j - 1] = -symbol;
        board[i + 2][j - 2] = -symbol;
        board[i + 3][j - 3] = -symbol;
        board[i + 4][j - 4] = -symbol;

        return 1;
      }
    }
  }

  return 0;
}
