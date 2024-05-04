#include "head.h"

struct numbers {
  plays play;
  long occurences;
};

void afonsosort(plays *arr, int N, int size, int increment, int increasing) {
  int i, j, k, aux, hashtablesize;
  FILE *fp;
  struct numbers *arr2, *arr3, tmp;

  arr2 = (struct numbers *)calloc(size, sizeof(struct numbers));

  // is afonso sorting time

  hashtablesize = 0;
  for (i = 0; i < size; i++) { // hashing time
    aux = arr[i].score % N;
    if (arr2[aux].play.score == arr[i].score) {
      arr2[aux].occurences++;
    } else if (arr2[aux].occurences == 0) {
      arr2[aux].play.score = arr[i].score;
      arr2[aux].occurences = 1;
      hashtablesize++;
    } else {
      for (;
           arr2[aux].play.score != arr[i].score && arr2[aux].play.score != 0;) {
        aux += increment;
        if (aux >= N) {
          aux -= N;
        }
      }

      if (arr2[aux].play.score == arr[i].score) {
        arr2[aux].occurences++;
      } else {
        arr2[aux].play.score = arr[i].score;
        arr2[aux].occurences = 1;
        hashtablesize++;
      }
    }
  }

  arr3 = (struct numbers *)malloc(hashtablesize * sizeof(struct numbers));

  for (i = 0, j = 0; j < hashtablesize;
       i++) { // create a copy of the arr2 without the empty array values
    if (arr2[i].occurences != 0) {
      arr3[j].play.score = arr2[i].play.score;
      arr3[j].occurences = arr2[i].occurences;
      j++;
    }
  }

  free(arr2);

  if (increasing == 1) {
    for (i = 1; i < hashtablesize; i++) { // insertion sort
      for (j = i - 1, k = i, tmp = arr3[i]; j >= 0; k = j, j--) {
        if (arr3[j].play.score < tmp.play.score) {
          arr3[k] = arr3[j];
        } else {
          break;
        }
      }
      arr3[k] = tmp;
    }
  } else {
    for (i = 1; i < hashtablesize; i++) { // insertion sort
      for (j = i - 1, k = i, tmp = arr3[i]; j >= 0; k = j, j--) {
        if (arr3[j].play.score > tmp.play.score) {
          arr3[k] = arr3[j];
        } else {
          break;
        }
      }
      arr3[k] = tmp;
    }
  }

  for (i = 0, k = 0; i < hashtablesize; i++) { // write back the sorted array
    for (j = arr3[i].occurences; j != 0; j--) {
      arr[k] = arr3[i].play;
      k++;
    }
  }

  free(arr3);

  return;
}
