#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FARMER_COUNT 25

#define town_string(x) x == North ? "North" : "South"

pthread_mutex_t mutex;

typedef enum {
  North,
  South,
} Town;

typedef struct {
  Town from;
  unsigned int id;
} Farmer;

void *cross(void *data) {
  Farmer *f = data;
  pthread_mutex_lock(&mutex);
  printf("Farmer %d crossing bridge from %s\n", f->id, town_string(f->from));
  sleep(1);
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

int main(void) {
  pthread_mutex_init(&mutex, NULL);

  pthread_t threads[FARMER_COUNT];
  Farmer farmers[FARMER_COUNT];

  for (int i = 0; i < FARMER_COUNT; ++i) {
    farmers[i].id = i;
    farmers[i].from = (double)rand() / (double)RAND_MAX > 0.5 ? North : South;
    pthread_create(&threads[i], NULL, cross, &farmers[i]);
  }

  for (int i = 0; i < FARMER_COUNT; ++i) {
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
}
