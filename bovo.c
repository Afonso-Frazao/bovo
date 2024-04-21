#include <stdio.h>
#include <stdlib.h>

float evaluateposition(int **board) {
  float eval; // The 'X' will get a positive eval while the 'O' will get a
              // negative one and then they will add
  int streak, spaces, symbol;
  int i, j;

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
        return 1;
      }
    }
  }

  return eval;
}

// TODO change board type to char and symbol variable to char

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
        return 1;
      }
    }
  }

  for (streak = 0, symbol = 'X', diag = 22; diag >= 1;
       diag--) { // verify diagonal 1
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
        return 1;
      }
    }
  }

  for (streak = 0, symbol = 'X', diag = 1; diag < 23;
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
        return 1;
      }
    }
  }

  for (streak = 0, symbol = 'X', diag = 1; diag < 23;
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
        return 1;
      }
    }
  }

  for (streak = 0, symbol = 'X', diag = 1; diag < 23;
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
        return 1;
      }
    }
  }

  return 0;
}

int printingtime(int **board) {
  int i, j;

  for (i = 0; i < 23; i++) {
    for (j = 0; j < 23; j++) {
      if (board[i][j] != 0) {
        if ((j % 2) == 0) {
          if (board[i][j] == 'O') {
            printf("\033[38;5;39mO\033[0m|\033[0m"); // Color code 39 for orange
          } else if (board[i][j] == 'X') {
            printf("\033[38;5;208mX\033[0m|\033[0m"); // Color code 208 for cyan
          } else {
            printf("%c|", board[i][j]);
          }
        } else {
          if (board[i][j] == 'O') {
            printf("\033[38;5;39mO\033[38;5;240m|\033[0m"); // Color code 39 for
                                                            // cyan
          } else if (board[i][j] == 'X') {
            printf("\033[38;5;208mX\033[38;5;240m|\033[0m"); // Color code 208
                                                             // for orange
          } else {
            printf("%c\033[38;5;240m|\033[0m", board[i][j]);
          }
        }
      } else {
        if ((j % 2) == 0) {
          printf(" |");
        } else {
          printf(" \033[38;5;240m|\033[0m");
        }
      }
    }
    printf("\n");
  }
  printf("\n");

  return 0;
}

int main() {
  int **board;
  int i;
  char l, c;
  int gameover = 0;

  board = (int **)malloc(23 * sizeof(int *));
  for (i = 0; i < 23; i++) {
    board[i] = (int *)calloc(23, sizeof(int));
  }

  for (i = 1; i < 23; i++) {
    board[i][0] = i + 'a' - 1;
    board[0][i] = i + 'a' - 1;
  }

  while (gameover == 0) {
    for (i = 0; i < 2; i++) {
      if (printingtime(board) != 0) {
        return 1;
      }
      // fflush(stdout);

      scanf(" %c %c", &l, &c);
      l = l - 'a' + 1;
      c = c - 'a' + 1;

      if (i == 0) {
        if (board[l][c] == 0) {
          board[l][c] = 'X';
        } else {
          printf("Invalid move\n");
          i--;
        }
      } else {
        if (board[l][c] == 0) {
          board[l][c] = 'O';
        } else {
          printf("Invalid move\n");
          i--;
        }
      }

      gameover = verifygameover(board);
      if (gameover == 1) {
        if (i == 0) {
          if (printingtime(board) != 0) {
            return 1;
          }
          printf("\n\033[38;5;208mX\033[0m wins!\n\n");
          break;
        } else {
          if (printingtime(board) != 0) {
            return 1;
          }
          printf("\n\033[38;5;39mO\033[0m wins!\n\n");
        }
      }
    }
  }
  return 0;
}
