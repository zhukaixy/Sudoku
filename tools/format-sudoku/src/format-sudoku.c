#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BOARD_SIZE (9 * 9)

void usage(const char* exec) {
  fprintf(stderr, "Usage: %s <file>\n", exec);
  fprintf(stderr, "\t<file>: The sudoku file path\n");
  fprintf(stderr, "\tor using %s with stdin\n", exec);
}

FILE* open_file_for_read(const char* path) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "Error: open file %s failed\n", path);
  }
  return file;
}

bool get_sudoku_from_file(int* sudo, int size, FILE* file) {
  assert(sudo != NULL && size >= BOARD_SIZE && file != NULL);
  memset(sudo, 0, sizeof(int) * size);
  int count = 0;
  for (; count < BOARD_SIZE;) {
    int c = fgetc(file);
    if (c == EOF) {
      return false;
    }
    if (c >= '0' && c <= '9') {
      sudo[count] = c - '0';
      count++;
    }
  }
  return true;
}

void display_sudoku(int* sudo) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int index = i * 9 + j;
      printf("%d ", sudo[index]);
      if (j == 2 || j == 5)
        printf(" ");
    }
    printf("\n");
    if (i == 2 || i == 5) {
      printf("\n");
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 1 && argc != 2) {
    usage(argv[0]);
    return -1;
  }

  FILE* file = stdin;
  if (argc == 2) {
    file = open_file_for_read(argv[1]);
    if (file == NULL) {
      usage(argv[0]);
      return -1;
    }
  }

  int sudo[BOARD_SIZE];
  if (get_sudoku_from_file(sudo, BOARD_SIZE, file) == false) {
    fprintf(stderr, "Read sudoku from %s failed\n", argv[1]);
    usage(argv[0]);
    fclose(file);
    return -1;
  }
  fclose(file);

  display_sudoku(sudo);

  return 0;
}
