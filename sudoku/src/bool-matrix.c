#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> // for memset

#include <sudoku.h>

typedef struct Node Node;
typedef Node Column;
struct Node {
  Node* left;
  Node* right;
  Node* up;
  Node* down;
  Column* col;
  union {
    int size; // for column is size, the size of that doubly link list
    int rnum; // for row is row number
  } u;
};

struct BoolMatrix {
  int rows_; // matrix property
  int cols_;

  Node* nodes_; // node array
  int size_nodes_;
  int cur_node_; // point to the next empty node

  Column** columns_; // map column index to column head node
  int size_columns_;

  int* stack_; // answer array
  int size_stack_;
  int top_stack_; // point to the next empty slot

  Column* root_; // root node for head node
  int data_rows_; // how many rows has been set

  bool just_one_;
  AnswerCallback cb_;
  int ans_cnt_; // answer count
  void* data_; // for user
};

// Full Graph:
// =>Root<==>   Column0    <==>   Column1    <=...=>   Column(cols_-1)   <=
//         =>   Row0_0     <==>   Row0_0     <=...=>   Row0_(cols-1)     <=
//         =>   Row1_0     <==>   Row1_0     <=...=>   Row1_(cols-1)     <=
//              ...               ...          ...     ...
//         =>Row(rows_-1)_0<==>Row(rows_-1)_0<=...=>Row(rows_-1)_(cols-1)<=
// Root is a doubly link list(with left and right),
// and each node of it is the head of it's doubly link list(with up and down)
// Each Node of the Row below the head line are link to two doubly link list

// Get a column Node for Root Line (The head line, not the first line of the matrix)
Column* new_column(BoolMatrix* matrix) {
  assert(matrix->cur_node_ < matrix->size_nodes_);

  Column* c = &matrix->nodes_[matrix->cur_node_++];
  // memZero(c, sizeof(Column));
  c->left = c;
  c->right = c;
  c->up = c;
  c->down = c;
  c->col = c;
  c->u.size = 0;
  return c;
}

// When old is a doubly link list, treat old as list header,
// then put nnew to the left of old means put nnew to the end of the list
void put_left(Column* old, Column* nnew) {
  nnew->left = old->left;
  nnew->right = old;
  old->left->right = nnew;
  old->left = nnew;
}

// Create a new Node for head line and add to the end of the root list
void append_column(BoolMatrix* matrix, int n) {
  assert(matrix->columns_[n] == NULL);
  assert(matrix->root_ != NULL);

  Column* c = new_column(matrix);
  put_left(matrix->root_, c);
  matrix->columns_[n] = c;
}

// old is a Node from head line
// nnew is a Node from one normal row
// old is the head of the doubly link list, put nnew to the up of old means
// append nnew to the end of the doubly link list
void put_up(Column* old, Node* nnew) {
  nnew->up = old->up;
  nnew->down = old;
  old->up->down = nnew;
  old->up = nnew;
  old->u.size++;
  nnew->col = old;
}

// Create a new Node and append to the list of that col
Node* new_row(BoolMatrix* matrix, int col) {
  assert(matrix->columns_[col] != NULL);
  assert(matrix->cur_node_ < matrix->size_nodes_);

  Node* r = &matrix->nodes_[matrix->cur_node_++];
  // memZero(r, sizeof(Node));
  r->left = r;
  r->right = r;
  r->up = r;
  r->down = r;
  r->col = matrix->columns_[col];
  put_up(r->col, r);
  return r;
}

// Find the mini size Column in the Root doubly link list
Column* get_min_column(BoolMatrix* matrix) {
  Column* c = matrix->root_->right;
  int min_size = c->u.size;
  if (min_size > 1) {
    for (Column* cc = c->right; cc != matrix->root_; cc = cc->right) {
      if (min_size > cc->u.size) {
        c = cc;
        min_size = cc->u.size;
        if (min_size <= 1)
          break;
      }
    }
  }
  return c;
}

// Unlink the Column and it's Rows from Root doubly loop
void cover(Column* c) {
  c->right->left = c->left;
  c->left->right = c->right;
  for (Node* row = c->down; row != c; row = row->down) {
    for (Node* j = row->right; j != row; j = j->right) {
      j->down->up = j->up;
      j->up->down = j->down;
      j->col->u.size--;
    }
  }
}

// Link back the Column and it's Rows to Root doubly loop
void uncover(Column* c) {
  for (Node* row = c->up; row != c; row = row->up) {
    for (Node* j = row->left; j != row; j = j->left) {
      j->col->u.size++;
      j->down->up = j;
      j->up->down = j;
    }
  }
  c->right->left = c;
  c->left->right = c;
}

// Fire the dance, Algorithm X
bool dancing(BoolMatrix* matrix) {
  if (matrix->root_->left == matrix->root_) { // Matrix is empty, find an answer now
    matrix->ans_cnt_++;
    if (matrix->cb_ != NULL) {
      matrix->cb_(matrix->data_, matrix->stack_, matrix->top_stack_);
    }
    if (matrix->just_one_) {
      return true;
    }
    return false;
  }
  Column* const col = get_min_column(matrix);
  cover(col);
  for (Node* row = col->down; row != col; row = row->down) {
    matrix->stack_[matrix->top_stack_++] = row->u.rnum;
    for (Node* j = row->right; j != row; j = j->right) {
      cover(j->col);
    }
    if (dancing(matrix)) {
      return true;
    }
    matrix->top_stack_--;
    matrix->stack_[matrix->top_stack_] = 0;
    for (Node* j = row->left; j != row; j = j->left) {
      uncover(j->col);
    }
  }
  uncover(col);
  return false;
}

// rows is the number of matrix row
// cols is the number of matrix column
// maxNodes is the number of 1 in the matrix
BoolMatrix* CreateBoolMatrix(int rows, int cols, int maxNodes) {
  assert(rows != 0 && cols != 0 && maxNodes != 0);

  BoolMatrix* matrix = (BoolMatrix*)malloc(sizeof(BoolMatrix));
  memset(matrix, 0, sizeof(BoolMatrix));
  matrix->rows_ = rows;
  matrix->cols_ = cols;
  int max = rows * cols;
  if (max > maxNodes) {
    max = maxNodes;
  }
  matrix->size_nodes_ = max + cols + 1;
  matrix->nodes_ = (Node*)malloc(sizeof(Node) * matrix->size_nodes_);
  matrix->cur_node_ = 0;
  memset(matrix->nodes_, 0, sizeof(Node) * matrix->size_nodes_);

  matrix->size_columns_ = cols;
  matrix->columns_ = (Column**)malloc(sizeof(Column*) * matrix->size_columns_);
  memset(matrix->columns_, 0, sizeof(Column*) * matrix->size_columns_);

  matrix->size_stack_ = rows;
  matrix->stack_ = (int*)malloc(sizeof(int) * matrix->size_stack_);
  matrix->top_stack_ = 0;
  memset(matrix->stack_, 0, sizeof(int) * matrix->size_stack_);

  matrix->root_ = new_column(matrix);
  matrix->root_->left = matrix->root_->right = matrix->root_;
  for (int i = 0; i < cols; i++) {
    append_column(matrix, i);
  }
  matrix->data_rows_ = 0;
  return matrix;
}

SUDOKU_API void DestroyBoolMatrix(BoolMatrix* matrix) {
  assert(matrix != NULL);

  free(matrix->stack_);
  free(matrix->columns_);
  free(matrix->nodes_);
  free(matrix);
}

// num is the size of data array
SUDOKU_API void SetMatrixRowData(BoolMatrix* matrix, const int* data, int num) {
  assert(matrix != NULL && data != NULL && num > 0);
  for (int i = 0; i < num; i++) {
    assert(data[i] < matrix->cols_);
  }

  Node* n0 = new_row(matrix, data[0]);
  n0->u.rnum = matrix->data_rows_;
  for (int i = 1; i < num; i++) {
    Node* n = new_row(matrix, data[i]);
    n->u.rnum = matrix->data_rows_;
    put_left(n0, n);
  }
  matrix->data_rows_++;
}

SUDOKU_API int DancingLinks(BoolMatrix* matrix, bool justOne, AnswerCallback cb, void* data) {
  assert(matrix != NULL && matrix->data_rows_ == matrix->rows_);
  matrix->just_one_ = justOne;
  matrix->cb_ = cb;
  matrix->data_ = data;
  matrix->ans_cnt_ = 0;
  dancing(matrix);
  return matrix->ans_cnt_;
}
