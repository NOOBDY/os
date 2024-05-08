#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 8

#define POINT_COUNT 1e8

pthread_mutex_t lock;

int in_circle = 0;

float rand_float(void) { return 2 * ((float)rand() / RAND_MAX) - 1; }

void *worker(void *data) {
  unsigned int seed = time(NULL) ^ getpid() ^ pthread_self();
  srand(seed);

  for (int i = 0; i < POINT_COUNT / THREAD_COUNT; ++i) {
    float x = rand_float();
    float y = rand_float();

    if (x * x + y * y < 1) {
      pthread_mutex_lock(&lock);
      in_circle++;
      pthread_mutex_unlock(&lock);
    }
  }

  pthread_exit(NULL);
}

int main(void) {
  pthread_t threads[THREAD_COUNT];

  int err = pthread_mutex_init(&lock, NULL);
  if (err != 0) {
    perror("pthread_mutex_init");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < THREAD_COUNT; ++i) {
    pthread_create(&threads[i], NULL, worker, NULL);
  }

  for (int i = 0; i < THREAD_COUNT; ++i) {
    pthread_join(threads[i], NULL);
  }

  err = pthread_mutex_destroy(&lock);
  if (err != 0) {
    perror("pthread_mutex_destroy");
    exit(EXIT_FAILURE);
  }

  printf("%f\n", (float)(4 * in_circle) / POINT_COUNT);
}
