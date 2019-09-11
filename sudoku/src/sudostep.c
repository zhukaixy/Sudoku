#include <sudoku.h>
#include <sudostep.h>
#include <methods.h>

void calculate_step_by_step(Sudoku* sudo) {
  first_remove_posibility(sudo);
  check_all_posibility(sudo);
}
