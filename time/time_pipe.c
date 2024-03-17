#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

void child(int pipes[2], char **argv) {
  int err;
  struct timeval start;

  err = close(pipes[READ]);
  if (err < 0) {
    perror("close");
  }

  gettimeofday(&start, NULL);
  err = write(pipes[WRITE], &start, sizeof(struct timeval));
  if (err < 0) {
    perror("write");
    exit(EXIT_FAILURE);
  }

  err = close(pipes[WRITE]);
  if (err < 0) {
    perror("close");
  }

  int status = execvp(argv[0], &argv[1]);
  if (status != 0) {
    perror("exec");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

void parent(int pipes[2]) {
  int stat, err;

  err = close(pipes[WRITE]);
  if (err < 0) {
    perror("close");
  }

  pid_t child = wait(&stat);
  if (stat != EXIT_SUCCESS) {
    fprintf(stderr, "child %d ", child);
    perror("error");
    exit(EXIT_FAILURE);
  }

  struct timeval start;
  err = read(pipes[READ], &start, sizeof(struct timeval));
  if (err < 0) {
    perror("read");
    exit(EXIT_FAILURE);
  }

  err = close(pipes[READ]);
  if (err < 0) {
    perror("close");
    exit(EXIT_FAILURE);
  }

  struct timeval end;
  gettimeofday(&end, NULL);

  long delta = end.tv_usec - start.tv_usec;

  printf("%ldus\n", delta);

  exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
  int err;
  if (argc < 2) {
    fprintf(stderr, "enter argument\n");
    exit(EXIT_FAILURE);
  }

  int pipes[2];

  err = pipe(pipes);
  if (err < 0) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid_t p = fork();

  switch (p) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    child(pipes, &argv[1]);
  default:
    parent(pipes);
  }

  return 0;
}
