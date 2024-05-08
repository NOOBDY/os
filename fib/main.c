#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t sem;

typedef struct {
  int *arr;
  size_t n;
} Args;

void *worker(void *data) {
  Args *args = (Args *)data;
  int *arr = args->arr;

  arr[0] = 0;
  sleep(1);
  sem_post(&sem);

  arr[1] = 1;
  sleep(1);
  sem_post(&sem);

  for (int i = 2; i < args->n; ++i) {
    arr[i] = arr[i - 1] + arr[i - 2];
    sleep(1);
    sem_post(&sem);
  }

  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "input number\n");
    exit(EXIT_FAILURE);
  }

  sem_init(&sem, 0, 0);

  int count = atoi(argv[1]);

  int *arr = malloc(count * sizeof(int));

  Args args = {
      arr,
      count,
  };

  pthread_t child;

  pthread_create(&child, NULL, worker, &args);

  for (int i = 0; i < count; ++i) {
    sem_wait(&sem);
    printf("%d ", arr[i]);
    fflush(stdout);
  }

  pthread_join(child, NULL);

  free(arr);

  printf("\n");

  sem_destroy(&sem);
}
