#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "input address\n");
    exit(EXIT_FAILURE);
  }

  unsigned int addr;
  sscanf(argv[1], "%u", &addr);

  printf("The address %u contains:\n", addr);
  printf("page number = %u\n", addr / PAGE_SIZE);
  printf("offset = %u\n", addr % PAGE_SIZE);
}
