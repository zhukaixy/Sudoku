#include <string.h>

#include <sudoku.h>
#include <sudostep.h>
#include <methods.h>

void calculate_step_by_step(Sudoku* sudo) {
  first_remove_posibility(sudo);
  for (;;) {
    int tmpImproveCount = sudo->improveCount;
    check_all_posibility(sudo);
    if (tmpImproveCount == sudo->improveCount) {
      break;
    }
  }
  if (VerifySudoku(sudo)) {
    sudo->ansCount++;
    if (sudo->ansCallback != NULL) {
      char tmp[RESULT_BUFFER_SIZE];
      MakeResultString(sudo, tmp, RESULT_BUFFER_SIZE);
      sudo->ansCallback(sudo->data, tmp);
    }
  }
}
