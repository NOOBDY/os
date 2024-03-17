#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_NAME "/shm"

void child(char **argv) {
  int err;
  struct timeval start;

  int shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0600);
  if (shm_fd < 0) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }

  gettimeofday(&start, NULL);
  err = write(shm_fd, &start, sizeof(struct timeval));
  if (err < 0) {
    perror("write");
    exit(EXIT_FAILURE);
  }

  int status = execvp(argv[0], &argv[1]);
  if (status != 0) {
    perror("exec");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

void parent(void) {
  int stat, err;
  pid_t child = wait(&stat);
  if (stat != EXIT_SUCCESS) {
    fprintf(stderr, "child %d ", child);
    perror("error");
    exit(EXIT_FAILURE);
  }

  int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0600);
  if (shm_fd < 0) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }

  struct timeval start;
  err = read(shm_fd, &start, sizeof(struct timeval));
  if (err < 0) {
    perror("read");
    exit(EXIT_FAILURE);
  }

  err = shm_unlink(SHM_NAME);
  if (err < 0) {
    perror("shm_unlink");
    exit(EXIT_FAILURE);
  }

  struct timeval end;
  gettimeofday(&end, NULL);

  long delta = end.tv_usec - start.tv_usec;

  printf("%ldus\n", delta);

  exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "enter argument\n");
    exit(EXIT_FAILURE);
  }

  pid_t p = fork();

  switch (p) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    child(&argv[1]);
  default:
    parent();
  }

  return 0;
}
