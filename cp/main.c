#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_file_length(FILE *f, size_t *size) {
  int err = fseek(f, 0, SEEK_END);
  if (err != 0) {
    return err;
  }
  *size = ftell(f);
  rewind(f);

  return 0;
}

int main(int argc, char **argv) {
  int err;

  if (argc < 3) {
    fprintf(stderr, "Enter filename\n");
    return 1;
  }

  FILE *src = fopen(argv[1], "r");
  FILE *dst = fopen(argv[2], "w+");

  if (src == NULL || dst == NULL) {
    perror("error opening file");
    return 1;
  }

  size_t size;
  err = get_file_length(src, &size);
  if (err != 0) {
    perror("error getting file length");
    return 1;
  }

  char *buf = malloc(size);

  size_t r = fread(buf, sizeof(char), size, src);
  if (r != size) {
    perror("error reading from file");
    return 1;
  }

  size_t w = fwrite(buf, sizeof(char), size, dst);
  if (w != size) {
    perror("error writing to file");
    return 1;
  }

  err = fclose(src);
  if (err != 0) {
    perror("error closing file");
    return 1;
  }

  err = fclose(dst);
  if (err != 0) {
    perror("error closing file");
    return 1;
  }

  return 0;
}
