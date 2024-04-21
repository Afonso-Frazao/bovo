int evaluateposition(int **board) {
  int eval; // The 'X' will get a positive eval while the 'O' will get a
            // negative one and then they will add
  int streak, spaces, symbol;
  int i, j;

  for (streak = 0, spaces = 3, symbol = 'X', i = 1; i < 23;
       i++) { // verify lines
    for (j = 1; j < 23; j++) {
      if (board[i][j] == symbol) {
        streak++;
      } else if (board[i][j] != 0) {
        streak = 1;
        spaces = 3;
        symbol = board[i][j];
      } else {
        spaces--;
        if (spaces < 0) {
          streak = 0;
          spaces = 3;
        }
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
