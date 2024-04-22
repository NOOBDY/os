#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define POINT_COUNT 1e8

int in_circle = 0;

float rand_float(void) { return 2 * ((float)rand() / RAND_MAX) - 1; }

void *worker(void *data) {
  for (int i = 0; i < POINT_COUNT; ++i) {
    float x = rand_float();
    float y = rand_float();

    if (x * x + y * y < 1) {
      in_circle++;
    }
  }

  pthread_exit(NULL);
}

int main(void) {
  pthread_t p;
  pthread_create(&p, NULL, worker, NULL);

  pthread_join(p, NULL);

  printf("%f\n", (float)(4 * in_circle) / POINT_COUNT);
}
