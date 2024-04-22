#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *arr;
  size_t n;
} Args;

void *worker(void *data) {
  Args *args = (Args *)data;
  int *arr = args->arr;

  arr[0] = 0;
  arr[1] = 1;

  for (int i = 2; i < args->n; ++i) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }

  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "input number\n");
    exit(EXIT_FAILURE);
  }

  int count = atoi(argv[1]);

  int *arr = malloc(count * sizeof(int));

  Args args = {
      arr,
      count,
  };

  pthread_t child;

  pthread_create(&child, NULL, worker, &args);

  pthread_join(child, NULL);

  for (int i = 0; i < count; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  free(arr);
}
