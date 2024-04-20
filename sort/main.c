#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *data;
  size_t begin;
  size_t end;
} Args;

int cmp(const void *a, const void *b) { //
  return *(int *)a - *(int *)b;
}

void *worker(void *data) {
  Args *args = (Args *)data;

  qsort(&args->data[args->begin], args->end - args->begin, sizeof(int), cmp);

  pthread_exit(NULL);
}

void merge(int a1[], size_t n1, int a2[], size_t n2, int result[]) {
  size_t i1 = 0;
  size_t i2 = 0;

  size_t ir = 0;

  while (i1 < n1 && i2 < n2) {
    if (a1[i1] <= a2[i2]) {
      result[ir] = a1[i1];
      i1++;
    } else {
      result[ir] = a2[i2];
      i2++;
    }

    ir++;
  }

  while (i1 < n1) {
    result[ir] = a1[i1];
    i1++;
    ir++;
  }

  while (i2 < n2) {
    result[ir] = a2[i2];
    i2++;
    ir++;
  }
}

int main(void) {
  int data[10] = {7, 0, 9, 3, 6, 5, 1, 4, 2, 8};
  size_t size = sizeof(data) / sizeof(*data);

  pthread_t p1, p2;

  Args args1 = {
      data,
      0,
      size / 2,
  };

  Args args2 = {
      data,
      size / 2,
      size,
  };

  int err;

  err = pthread_create(&p1, NULL, worker, &args1);
  if (err != 0) {
    errno = err;
    perror("create thread 1 failed");
    exit(EXIT_FAILURE);
  }

  err = pthread_create(&p2, NULL, worker, &args2);
  if (err != 0) {
    errno = err;
    perror("create thread 2 failed");
    exit(EXIT_FAILURE);
  }

  err = pthread_join(p1, NULL);
  if (err != 0) {
    errno = err;
    perror("join thread 1 failed");
  }

  err = pthread_join(p2, NULL);
  if (err != 0) {
    errno = err;
    perror("join thread 2 failed");
  }

  for (size_t i = args1.begin; i < args1.end; ++i) {
    printf("%d ", data[i]);
  }
  printf("\n");

  for (size_t i = args2.begin; i < args2.end; ++i) {
    printf("%d ", data[i]);
  }
  printf("\n");

  int result[10];

  merge(&data[args1.begin], args1.end - args1.begin, &data[args2.begin],
        args2.end - args2.begin, result);

  for (size_t i = 0; i < size; ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
}
