#include "head.h"

long spacesscore(int size) { // I could return the values
                             // inside the cases of the switch
  long score;

  switch (size) {

  case 1:
    score = 200;
    break;
  case 2:
    score = 360;
    break;
  case 3:
    score = 500;
    break;
  case 4:
    score = 600;
    break;
  case 5:
    score = 680;
    break;
  case 6:
    score = 740;
    break;
  case 7:
    score = 780;
    break;
  default:
    score = 800;
  }

  return score;
}

long streakscore(int size) {
  long score;

  switch (size) {

  case 1:
    score = 1000;
    break;
  case 2:
    score = 3000;
    break;
  case 3:
    score = 7000;
    break;
  case 4:
    score = 15000;
    break;
  case 5:
    score = 10000000000;
    break;
  }

  return score;
}

double scoremultiplier(int samesymbolstreaks, int spacesbetween,
                       int onetoplay) {
  double factor;

  switch (spacesbetween) {
  case 0:
    factor = 1;
    break;
  case 1:
    factor = 1.1;
    break;
  case 2:
    factor = 1.3;
    break;
  case 3:
    factor = 1.6;
    break;
  case 4:
    factor = 1.9;
    break;
  case 5:
    factor = 2.2;
    break;
  default:
    factor = 2.5;
  }

  switch (samesymbolstreaks) {
  case 1:
    break;
  case 2:
    factor *= 3;
    break;
  case 3:
    factor *= 8;
    break;
  default:
    factor *= 10;
  }

  if (onetoplay == 1) {
    factor *= 1.3;
  }

  return factor;
}

long evaluatescore(int *streak, int streaknumber, int *streaksymbol,
                   int symboltoplay) {
  int currentstreak, symbol;
  int samesymbolstreaks, spacesbetween, onetoplay;
  long score, partialscore;
  double factor;

  /*for (currentstreak = 0; currentstreak <= streaknumber; currentstreak++) {
    printf("symbol: %c\nstreak: %d\n\n", streaksymbol[currentstreak],
           streak[currentstreak]);
  }*/
  score = 0;
  if (streaknumber >= 1) { // I'm assuming that if there is only one streak
                           // (streaknumber=0) it means that it is all 0's
    if (streaksymbol[0] !=
        0) { // initialise the symbol with the first non zero symbol
      symbol = streaksymbol[0];
    } else {
      symbol = streaksymbol[1];
    }
    if (symbol == symboltoplay) {
      onetoplay = 1;
    } else {
      onetoplay = 0;
    }
    for (currentstreak = 0, samesymbolstreaks = 0, spacesbetween = 0,
        partialscore = 0;
         currentstreak <= streaknumber; currentstreak++) {
      if (streaksymbol[currentstreak] == 0) {
        spacesbetween++;
        partialscore += spacesscore(streak[currentstreak]);
      } else if (streaksymbol[currentstreak] == symbol) {
        samesymbolstreaks++;
        partialscore += streakscore(streak[currentstreak]);
      } else {
        factor = scoremultiplier(samesymbolstreaks, spacesbetween, onetoplay);
        partialscore *= factor;
        if (symbol == 'X') { // for 'X' the score is positive
          score += partialscore;
        } else { // for 'O' the score is negative
          score -= partialscore;
        }
        symbol = streaksymbol[currentstreak];
        if (symbol ==
            symboltoplay) { // check if the current symbol is the one to play
          onetoplay = 1;
        } else {
          onetoplay = 0;
        }
        partialscore = streakscore(streak[currentstreak]);
        spacesbetween = 0;
        samesymbolstreaks = 1;
        if ((currentstreak > 0) && (streaksymbol[currentstreak - 1] ==
                                    0)) { // verify if there are spaces before
          spacesbetween++;
        }
      }
    }
    factor = scoremultiplier(samesymbolstreaks, spacesbetween, onetoplay);
    partialscore *= factor;
    if (symbol == 'X') {
      score += partialscore;
    } else {
      score -= partialscore;
    }
  }
  return score;
}

long gamealreadyover(int *streak, int streaknumber, int *streaksymbol,
                     int symboltoplay) {
  int currentstreak;
  long score;

  score = 0;
  if (streaknumber >= 1) {
    for (currentstreak = 0; currentstreak <= streaknumber; currentstreak++) {
      if ((streak[currentstreak] == 4) &&
          (streaksymbol[currentstreak] !=
           0)) { // check if 4 symbol streaks are forced game over
        if ((currentstreak > 0) && (streaksymbol[currentstreak - 1] == 0) &&
            (currentstreak < streaknumber) &&
            (streaksymbol[currentstreak + 1] ==
             0)) { // if there is a 4 symbol streak between spaces is forced
                   // game over
          if (streaksymbol[currentstreak] == symboltoplay) {
            if (streaksymbol[currentstreak] == 'X') {
              score += 100000000;
            } else {
              score -= 100000000;
            }
          } else {
            if (streaksymbol[currentstreak] == 'X') {
              score += 1000000;
            } else {
              score -= 1000000;
            }
          }
        } else if (((currentstreak > 0) &&
                        (streaksymbol[currentstreak - 1] == 0) ||
                    ((currentstreak < streaknumber) &&
                     (streaksymbol[currentstreak + 1] == 0))) &&
                   (symboltoplay == streaksymbol[currentstreak])) {
          if (streaksymbol[currentstreak] == 'X') {
            score += 100000000;
          } else {
            score -= 100000000;
          }
        }
      } else if ((streak[currentstreak] == 3) && (currentstreak > 0) &&
                 (currentstreak < streaknumber) &&
                 (streaksymbol[currentstreak] != 0) &&
                 (symboltoplay ==
                  streaksymbol[currentstreak])) { // if there is a 3 symbol
                                                  // streak and the valid
                                                  // symbols or spaces on each
                                                  // syde so it is forced game
                                                  // over
        if ((streaksymbol[currentstreak - 1] == 0) &&
            ((streak[currentstreak - 1] >= 2) ||
             (streak[currentstreak - 1] == 1 && (currentstreak > 1) &&
              streaksymbol[currentstreak - 2] ==
                  streaksymbol[currentstreak]))) { // check if there is two
                                                   // spaces or a space and one
                                                   // or more symbols on each
                                                   // side

          if ((streaksymbol[currentstreak + 1] == 0) &&
              ((streak[currentstreak + 1] >= 2) ||
               (streak[currentstreak + 1] == 1 &&
                (currentstreak < streaknumber - 1) &&
                streaksymbol[currentstreak + 2] ==
                    streaksymbol[currentstreak]))) {
            if (streaksymbol[currentstreak] == 'X') {
              score += 1000000;
            } else {
              score -= 1000000;
            }
          }
        }
      }
    }
  }

  return score;
}

long evaluateposition(int **board, int symboltoplay) {
  long eval; // The 'X' will get a positive eval while the 'O' will get a
             // negative onel and then they will add
  int *streak, currentstreak, symbol; // lastwassymbol for when the last board
                                      // square verified was a symbol
  int *streaksymbol;
  int l, c, diag;

  streak = (int *)malloc(22 * sizeof(int));
  streaksymbol = (int *)malloc(22 * sizeof(int));

  eval = 0;

  for (l = 1; l < 23; l++) { // score lines
    for (c = 2, symbol = board[l][1], streaksymbol[0] = board[l][1],
        streak[0] = 1, currentstreak = 0;
         c < 23; c++) {
      if (board[l][c] == symbol) {
        streak[currentstreak]++;
      } else {
        currentstreak++;
        symbol = board[l][c];
        streaksymbol[currentstreak] = symbol;
        streak[currentstreak] = 1;
      }
    }
    eval += gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
    eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);
  }

  for (l = 1; l < 23; l++) { // score rows
    for (c = 2, symbol = board[1][l], streaksymbol[0] = board[1][l],
        streak[0] = 1, currentstreak = 0;
         c < 23; c++) {
      if (board[c][l] == symbol) {
        streak[currentstreak]++;
      } else {
        currentstreak++;
        symbol = board[c][l];
        streaksymbol[currentstreak] = symbol;
        streak[currentstreak] = 1;
      }
    }
    eval += gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
    eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);
  }

  for (diag = 18; diag >= 1; diag--) { // score diagonal 1
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
    eval += gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
    eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);
  }

  for (diag = 2; diag < 19; diag++) { // score diagonal 1
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
    eval += gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
    eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);
  }

  for (diag = 5; diag < 23; diag++) { // score diagonal 2
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
    eval += gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
    eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);
  }

  for (diag = 2; diag < 19; diag++) { // score diagonal 2
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
    eval += gamealreadyover(streak, currentstreak, streaksymbol, symboltoplay);
    eval += evaluatescore(streak, currentstreak, streaksymbol, symboltoplay);
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

  for (streak = 0, symbol = 'X', diag = 18; diag >= 1;
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
