#include "head.h"
#include <stdio.h>

typedef struct {
  int l;
  int c;
} coords;

int printingtime(int **board, int lastl, int lastc) {
  int i, j;

  printf("\n");
  for (i = 0; i < 23; i++) {
    for (j = 0; j < 23; j++) {
      if (board[i][j] != 0) {
        if ((j % 2) == 0) {
          if (board[i][j] == 'X') {
            printf("\033[38;5;208mX\033[0m|"); // Color code 208 for orange
          } else if (board[i][j] == 'O') {
            printf("\033[38;5;39mO\033[0m|"); // Color code 39 for cyan
          } else if (board[i][j] == -'X') {
            printf("\033[38;5;34mX\033[0m|");
          } else if (board[i][j] == -'O') {
            printf("\033[38;5;34mO\033[0m|");
          } else {
            printf("%c|", board[i][j]);
          }
        } else {
          if (board[i][j] == 'X') {
            printf("\033[38;5;208mX\033[38;5;240m|\033[0m");
          } else if (board[i][j] == 'O') {
            printf("\033[38;5;39mO\033[38;5;240m|\033[0m");
          } else if (board[i][j] == -'X') {
            printf("\033[38;5;34mX\033[38;5;240m|\033[0m");
          } else if (board[i][j] == -'O') {
            printf("\033[38;5;34mO\033[38;5;240m|\033[0m");
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
  coords *moves;
  int playsN;

  board = (int **)malloc(23 * sizeof(int *));
  for (i = 0; i < 23; i++) {
    board[i] = (int *)calloc(23, sizeof(int));
  }

  for (i = 1; i < 23; i++) {
    board[i][0] = i + 'a' - 1;
    board[0][i] = i + 'a' - 1;
  }

  moves = (coords *)calloc(484, sizeof(int));

  playsN = 0;
  while (gameover == 0) {
    for (i = 0; i < 2; i++) {
      if (playsN != 0) {
        if (printingtime(board, moves[playsN - 1].l, moves[playsN - 1].c) !=
            0) {
          return 1;
        }
      } else {
        if (printingtime(board, 0, 0) != 0) {
          return 1;
        }
      }
      // fflush(stdout);

      scanf(" %c %c", &l, &c);
      l = l - 'a' + 1;
      c = c - 'a' + 1;

      if ((l < 1 || l > 22 || c < 1 || c > 22) && (l != 'z' - 'a' + 1) &&
          (l != 'y' - 'a' + 1)) {
        printf("\nInvalid move!\n");
        i--;
        continue;
      }

      if (l == 'z' - 'a' + 1) {
        if (playsN == 0) {
          printf("\nAlready at empty board!\n");
          i--;
          continue;
        }
        playsN--;
        board[moves[playsN].l][moves[playsN].c] = 0;
        if (printingtime(board, moves[playsN - 1].l, moves[playsN - 1].c) !=
            0) {
          return 1;
        }
      } else if (l == 'y' - 'a' + 1) {
        if (moves[playsN].l == 0) {
          printf("\nAlready at last play!\n");
          i--;
          continue;
        }
        if (i == 0) {
          board[moves[playsN].l][moves[playsN].c] = 'X';
        } else {
          board[moves[playsN].l][moves[playsN].c] = 'O';
        }
        if (printingtime(board, moves[playsN].l, moves[playsN].c) != 0) {
          return 1;
        }
        playsN++;
      } else {
        if (i == 0) {
          if (board[l][c] == 0) {
            board[l][c] = 'X';
            moves[playsN].l = l;
            moves[playsN].c = c;
            playsN++;
          } else {
            printf("\nInvalid move\n");
            i--;
            continue;
          }
        } else {
          if (board[l][c] == 0) {
            board[l][c] = 'O';
            moves[playsN].l = l;
            moves[playsN].c = c;
            playsN++;
          } else {
            printf("\nInvalid move\n");
            i--;
            continue;
          }
        }

        gameover = verifygameover(board);
        if (gameover == 1) {
          if (i == 0) {
            if (printingtime(board, l, c) != 0) {
              return 1;
            }
            printf("\n\033[38;5;208mX\033[0m wins!\n\n");
            break;
          } else {
            if (printingtime(board, l, c) != 0) {
              return 1;
            }
            printf("\n\033[38;5;39mO\033[0m wins!\n\n");
          }
        }
      }
    }
  }
  return 0;
}
