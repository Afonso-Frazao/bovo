#include "head.h"

int evaluatescore(int *streak, int *spaces, int currentstreak,
                  int *streaksymbol, int firstisspace, int symboltoplay,
                  int lastisspace) {
  int i;

  printf("streak\n");
  if (firstisspace == 0) { // first is a space
    for (i = 0; i < currentstreak; i++) {
      printf("spaces, number %d\n", spaces[i]);
      printf("char %c, ", (char)(streaksymbol[i]));
      printf("streak %d\n", streak[i]);
    }
    if (lastisspace == 1) { // last is a space
      printf("spaces, number %d\n", spaces[i]);
    }
  } else { // first is not a space
    for (i = 0; i < currentstreak - 1; i++) {
      printf("char %c, streak %d\n", (char)(streaksymbol[i]), streak[i]);
      printf(
          "spaces, number %d\n",
          spaces[i - 1]); // spaces[i-1] is the same as spaces[i-firstisspace]
    }
    if (lastisspace == 1) { // last is a space
      printf("spaces, number %d\n", spaces[i]);
    }
  }

  return 0;
}

int gamealreadyover(int **board, int symboltoplay) { return 0; }

int evaluateposition(int **board, int symboltoplay) {
  int eval; // The 'X' will get a positive eval while the 'O' will get a
            // negative onel and then they will add
  int *streak, currentstreak, *spaces, symbol,
      lastwassymbol; // lastwassymbol for when the last board square verified
                     // was a symbol
  int *streaksymbol, firstisspace, lastisspace;
  long score;
  int l, c, currentsymbol;

  streak = (int *)malloc(22 * sizeof(int));
  spaces = (int *)malloc(22 * sizeof(int));
  streaksymbol = (int *)malloc(22 * sizeof(int));

  for (l = 1; l < 23; l++) {
    if (board[l][1] == 0) { // 0 if first is a space and -1 if not
      firstisspace = 0;
    } else {
      firstisspace = -1;
    }
    if (board[l][22] == 0) { // 1 if last is a space and 0 if not
      lastisspace = 1;
    } else {
      lastisspace = 0;
    }
    for (c = 1, symbol = 0, currentstreak = -1, lastwassymbol = 0,
        spaces[0] = 0;
         c < 23; c++) {
      if (board[l][c] == 0) {
        if (lastwassymbol == 1) {
          lastwassymbol = 0;
          spaces[currentstreak + firstisspace] = 1;
        } else {
          /*printf("currentstreak=%d\n", currentstreak);
          printf("firstisspace=%d\n", firstisspace);*/
          printf("space: %d\n", currentstreak + firstisspace);
          spaces[currentstreak + firstisspace]++;
        }
      } else if (board[l][c] == symbol) {
        if (lastwassymbol == 1) {
          streak[currentstreak]++;
        } else {
          streaksymbol[currentstreak] = symbol;
          streak[currentstreak] = 1;
          lastwassymbol = 1;
          currentstreak++;
        }
      } else {
        currentsymbol = board[l][c];
        streaksymbol[currentstreak] = currentsymbol;
        streak[currentstreak] = 1;
        lastwassymbol = 1;
        symbol = currentsymbol;
        currentstreak++;
      }
    }
    evaluatescore(streak, spaces, currentstreak, streaksymbol, firstisspace,
                  lastisspace, symboltoplay);
    exit(0);
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
