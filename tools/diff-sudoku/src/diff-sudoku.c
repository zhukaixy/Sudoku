#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BOARD_SIZE (9 * 9)

typedef enum CharColor { None = 0, Red, Green } CharColor;

void usage(const char* exec) {
  fprintf(stderr, "Usage: %s <file1> <file2>\n", exec);
  fprintf(stderr, "\t<file1>: The first sudoku file path\n");
  fprintf(stderr, "\t<file2>: The second sudoku file path\n");
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

void display_check(bool allZero, bool allNotZero) {
  if (allZero && allNotZero) {
    printf("\033[36;1mThe same, no diff!\033[0m\n");
    return;
  }
  if (!allZero && !allNotZero) {
    printf("\n");
    return;
  }
  if (allZero) {
    printf("\033[36;1mAll diff are zero!\033[0m\n");
  }
  if (allNotZero) {
    printf("\033[36;1mAll diff are non zero!\033[0m\n");
  }
}

void get_display_int_string(char* buffer, int size, int value, CharColor col) {
  assert(buffer != NULL && size >= 14 && value >= 0 && value <= 9);
  memset(buffer, 0, sizeof(char) * size);
  switch (col) {
    case None:
      snprintf(buffer, size, "%d ", value);
      break;
    case Red:
      snprintf(buffer, size, "\033[31;1m%d\033[0m ", value);
      break;
    case Green:
      snprintf(buffer, size, "\033[32;1m%d\033[0m ", value);
      break;
    default:
      break;
  }
}

void display_sudoku_with_mask(int* sudo, bool* mask, CharColor col) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int index = i * 9 + j;
      char buffer[32];
      get_display_int_string(buffer, 32, sudo[index], mask[index] ? col : None);
      printf("%s", buffer);
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
  if (argc != 3) {
    usage(argv[0]);
    return -1;
  }

  FILE* file1 = open_file_for_read(argv[1]);
  if (file1 == NULL) {
    usage(argv[0]);
    return -1;
  }
  FILE* file2 = open_file_for_read(argv[2]);
  if (file2 == NULL) {
    usage(argv[0]);
    fclose(file1);
    return -1;
  }

  int sudo1[BOARD_SIZE];
  int sudo2[BOARD_SIZE];
  if (get_sudoku_from_file(sudo1, BOARD_SIZE, file1) == false) {
    fprintf(stderr, "Read sudoku from %s failed\n", argv[1]);
    usage(argv[0]);
    fclose(file1);
    fclose(file2);
    return -1;
  }
  if (get_sudoku_from_file(sudo2, BOARD_SIZE, file2) == false) {
    fprintf(stderr, "Read sudoku from %s failed\n", argv[2]);
    usage(argv[0]);
    fclose(file1);
    fclose(file2);
    return -1;
  }
  fclose(file1);
  fclose(file2);

  bool mask[BOARD_SIZE];
  bool allZero1 = true, allZero2 = true, allNotZero1 = true, allNotZero2 = true;
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (sudo1[i] != sudo2[i]) {
      allZero1 = allZero1 && sudo1[i] == 0;
      allZero2 = allZero2 && sudo2[i] == 0;
      allNotZero1 = allNotZero1 && sudo1[i] != 0;
      allNotZero2 = allNotZero2 && sudo2[i] != 0;
      mask[i] = true;
    } else {
      mask[i] = false;
    }
  }

  printf("First Sudoku: ");
  display_check(allZero1, allNotZero1);
  display_sudoku_with_mask(sudo1, mask, Green);
  printf("Second Sudoku: ");
  display_check(allZero2, allNotZero2);
  display_sudoku_with_mask(sudo2, mask, Red);

  return 0;
}
