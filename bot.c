#include "head.h"

// #define SEARCHDEPTH 7
#define SEARCHDEPTH 2
// #define PLAYSPERDEPTH 20
#define PLAYSPERDEPTH 5

typedef struct _node {
  int size;
  int currentplay;
  plays *evalarr;
  plays bestplay;
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

long numberofoutcomes(int validplaysnumber) {
  int i, outcomes;

  for (i = SEARCHDEPTH, outcomes = validplaysnumber, validplaysnumber--;
       validplaysnumber > 0; validplaysnumber--) {
    outcomes *= validplaysnumber;
  }

  return outcomes;
}

long evaluateline(int **board, int symboltoplay, int line, int col) {
  long eval;
  int *streak, currentstreak, symbol;
  int *streaksymbol;
  int l, c, diag;

  eval = 0;

  streak = (int *)malloc(22 * sizeof(int));
  streaksymbol = (int *)malloc(22 * sizeof(int));

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
  eval += evaluatescore(streak, currentstreak, streaksymbol,
                        symboltoplay); // TODO error here
  // printf("%ld, ", eval);

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

  if ((line + col - 1) <= 22) { // score the diagonal 2
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

int calculateplayseval(int **board, plays *allplaysscore, long eval,
                       int symboltoplay) {
  int validplaysnumber;
  int l, c;
  long lineevalbefore, lineevalafter;

  validplaysnumber = 0;
  for (l = 1; l < 23; l++) {
    for (c = 1; c < 23; c++) {
      if (board[l][c] == 0) {
        lineevalbefore = evaluateline(board, symboltoplay, l, c);
        board[l][c] = symboltoplay;
        symboltoplay = opositesymbol(symboltoplay);
        lineevalafter =
            evaluateline(board, symboltoplay, l,
                         c); // some uninitilialised value comes from here
        allplaysscore[validplaysnumber].score =
            eval + lineevalafter - lineevalbefore;
        validplaysnumber++;
      }
    }
  }

  if (validplaysnumber == 0) {
    return 0;
  }

  if (((validplaysnumber % 7) != 0) &&
      (validplaysnumber > 7)) { // sort the valid plays
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
      PLAYSPERDEPTH) { // the array that will be processed can't be bigger than
                       // the number of plays per depth
    validplaysnumber = PLAYSPERDEPTH;
  }

  return validplaysnumber;
}

void createnode(plays *allplaysscore, int validplaysnumber, node *currentnode) {
  int i;

  currentnode->currentplay = 0;
  currentnode->size = validplaysnumber;
  currentnode->evalarr = (plays *)malloc(validplaysnumber * sizeof(plays));
  for (i = 0; i < validplaysnumber; i++) {
    currentnode->evalarr[i] = allplaysscore[i];
  }
  currentnode->ptr = (node *)malloc(validplaysnumber * sizeof(node));

  return;
}

plays highetorlowestscore(node *currentnode, int symboltoplay) {
  plays bestplay;
  int i;

  if (symboltoplay == 'X') {
    for (i = 1, bestplay = currentnode->evalarr[0]; i < currentnode->size;
         i++) { // the size shouldn't be smaller than 1 ever
      if (currentnode->evalarr[i].score > bestplay.score) {
        bestplay = currentnode->evalarr[i];
      }
    }
  } else {
    for (i = 1, bestplay = currentnode->evalarr[0]; i < currentnode->size;
         i++) { // the size shouldn't be smaller than 1 ever
      if (currentnode->evalarr[i].score < bestplay.score) {
        bestplay = currentnode->evalarr[i];
      }
    }
  }

  return bestplay;
}

plays bestbranch(node *currentnode, int symboltoplay) {
  plays bestplay;
  int i;

  if (symboltoplay == 'X') {
    for (i = 1, bestplay = currentnode->ptr[0].bestplay; i < currentnode->size;
         i++) { // the size shouldn't be smaller than 1 ever
      if (currentnode->ptr[0].bestplay.score > bestplay.score) {
        bestplay = currentnode->ptr[0].bestplay;
      }
    }
  } else {
    for (i = 1, bestplay = currentnode->ptr[0].bestplay; i < currentnode->size;
         i++) { // the size shouldn't be smaller than 1 ever
      if (currentnode->ptr[0].bestplay.score < bestplay.score) {
        bestplay = currentnode->ptr[0].bestplay;
      }
    }
  }

  return bestplay;
}

long verifyallplays(int **board, int symboltoplay) {
  long eval;
  int i, l, c;
  plays *allplaysscore;
  int validplaysnumber;
  int maxstackheight;
  node *currentnode;
  node **playsstack;
  int stackheight;
  long outcomes, endofsearch;

  allplaysscore = (plays *)malloc(484 * sizeof(plays));

  eval = evaluateposition(board, symboltoplay);

  validplaysnumber =
      calculateplayseval(board, allplaysscore, eval, symboltoplay);

  if (validplaysnumber == 0) {
    return eval;
  }

  // caculate the number of outcomes with the current search depth and plays
  // per depth

  outcomes = numberofoutcomes(validplaysnumber);

  /*if (currentnode == NULL) {
    printf("what the heeeeee1\n");
  }*/
  currentnode = (node *)malloc(sizeof(node));
  createnode(allplaysscore, validplaysnumber, currentnode);

  maxstackheight = validplaysnumber;

  // currentnode->currentplay++;
  // currentnode = currentnode->ptr;
  // increment the current play before accessing the pointer
  stackheight = 0;
  playsstack = (node **)malloc(SEARCHDEPTH * sizeof(node *));
  playsstack[0] = currentnode; // point to the newlly accessed play

  endofsearch = 0;
  while (endofsearch < outcomes) {
    if (currentnode->currentplay <
        currentnode->size) { // when the search reaches the max search
                             // depth is time to go back
      currentnode->currentplay++;
      currentnode = &(currentnode->ptr[currentnode->currentplay]);
      symboltoplay = opositesymbol(symboltoplay);
    } else if (stackheight >= SEARCHDEPTH) { // time to go back as it reached
                                             // the search depth
      // TODO verify if this situation can even happen
      stackheight--;
      currentnode = playsstack[stackheight]; // go back to the previous play
      board[currentnode->evalarr[currentnode->currentplay - 1].line]
           [currentnode->evalarr[currentnode->currentplay - 1].col] = 0;
      symboltoplay =
          opositesymbol(symboltoplay); // TODO add a free function here
      endofsearch++;
    } else { // time to go back
      if (stackheight == maxstackheight - 1) {
        currentnode->bestplay = highetorlowestscore(currentnode, symboltoplay);
      } else {
        currentnode->bestplay = bestbranch(currentnode, symboltoplay);
        if (stackheight == 0) {
          printf("Score: %ld\n", currentnode->bestplay.score);
        }
      }
      stackheight--;
      currentnode = playsstack[stackheight]; // go back to the previous play
      board[currentnode->evalarr[currentnode->currentplay - 1].line]
           [currentnode->evalarr[currentnode->currentplay - 1].col] = 0;
      symboltoplay =
          opositesymbol(symboltoplay); // TODO add a free function here
    }
    validplaysnumber =
        calculateplayseval(board, allplaysscore, eval, symboltoplay);
    currentnode->size = validplaysnumber;

    if (validplaysnumber == 0) { // time to go back
      if (stackheight != 0) {
        stackheight--;
        currentnode = playsstack[stackheight]; // go back to the previous play
        board[currentnode->evalarr[currentnode->currentplay - 1].line]
             [currentnode->evalarr[currentnode->currentplay - 1].col] = 0;
        symboltoplay = opositesymbol(symboltoplay);
        endofsearch++;
      } else {
        printf("acabou?\n");
        break;
      }
    }

    createnode(allplaysscore, validplaysnumber, currentnode);

    currentnode = currentnode->ptr;
    stackheight++;
    playsstack[stackheight] = currentnode;
  }

  return eval;
}
