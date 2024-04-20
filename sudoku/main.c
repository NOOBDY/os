#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Sudoku[9][9];

typedef struct {
  Sudoku *board;
  bool success;
} Args;

void *check_row(void *data) {
  Args *args = (Args *)data;
  Sudoku *board = args->board;

  for (int i = 0; i < 9; ++i) {
    bool nums[9] = {false};
    for (int j = 0; j < 9; ++j) {
      int num = (*board)[i][j];
      nums[num - 1] = true;
    }

    for (int j = 0; j < 9; ++j) {
      if (!nums[j]) {
        args->success = false;
        pthread_exit(NULL);
      }
    }
  }

  args->success = true;
  pthread_exit(NULL);
}

void *check_col(void *data) {
  Args *args = (Args *)data;
  Sudoku *board = args->board;

  for (int i = 0; i < 9; ++i) {
    bool nums[9] = {false};
    for (int j = 0; j < 9; ++j) {
      int num = (*board)[j][i];
      nums[num - 1] = true;
    }

    for (int j = 0; j < 9; ++j) {
      if (!nums[j]) {
        args->success = false;
        pthread_exit(NULL);
      }
    }
  }

  args->success = true;
  pthread_exit(NULL);
}

void *check_grid(void *data) {
  Args *args = (Args *)data;
  Sudoku *board = args->board;

  for (int i = 0; i < 9; ++i) {
    bool nums[9] = {false};
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; ++k) {
        int num = (*board)[(i / 3) * 3 + j][(i % 3) * 3 + k];
        nums[num - 1] = true;
      }
    }

    for (int j = 0; j < 9; ++j) {
      if (!nums[j]) {
        args->success = false;
        pthread_exit(NULL);
      }
    }
  }

  args->success = true;
  pthread_exit(NULL);
}

int main(void) {
  Sudoku board = {{7, 9, 2, 1, 5, 4, 3, 8, 6}, //
                  {6, 4, 3, 8, 2, 7, 1, 5, 9}, //
                  {8, 5, 1, 3, 9, 6, 7, 2, 4}, //
                  {2, 6, 5, 9, 7, 3, 8, 4, 1}, //
                  {4, 8, 9, 5, 6, 1, 2, 7, 3}, //
                  {3, 1, 7, 4, 8, 2, 9, 6, 5}, //
                  {1, 3, 6, 7, 4, 8, 5, 9, 2}, //
                  {9, 7, 4, 2, 1, 5, 6, 3, 8}, //
                  {5, 2, 8, 6, 3, 9, 4, 1, 7}};

  pthread_t row, col, grid;

  Args row_arg = {
      &board,
      false,
  };
  Args col_arg = {
      &board,
      false,
  };
  Args grid_arg = {
      &board,
      false,
  };

  int err;

  err = pthread_create(&row, NULL, check_row, &row_arg);
  if (err != 0) {
    errno = err;
    perror("create thread row failed");
    exit(EXIT_FAILURE);
  }

  err = pthread_create(&col, NULL, check_col, &col_arg);
  if (err != 0) {
    errno = err;
    perror("create thread col failed");
    exit(EXIT_FAILURE);
  }

  err = pthread_create(&grid, NULL, check_grid, &grid_arg);
  if (err != 0) {
    errno = err;
    perror("create thread grid failed");
    exit(EXIT_FAILURE);
  }

  err = pthread_join(row, NULL);
  if (err != 0) {
    errno = err;
    perror("join thread row failed");
  }

  err = pthread_join(col, NULL);
  if (err != 0) {
    errno = err;
    perror("join thread col failed");
  }

  err = pthread_join(grid, NULL);
  if (err != 0) {
    errno = err;
    perror("join thread grid failed");
  }

  if (err != 0) {
    exit(EXIT_FAILURE);
  }

  if (!row_arg.success) {
    fprintf(stderr, "row check invalid\n");
    exit(EXIT_FAILURE);
  }
  if (!col_arg.success) {
    fprintf(stderr, "col check invalid\n");
    exit(EXIT_FAILURE);
  }
  if (!grid_arg.success) {
    fprintf(stderr, "grid check invalid\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
