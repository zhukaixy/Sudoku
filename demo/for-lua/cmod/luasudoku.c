/* Lua C Library */

#define LUA_LIB // for export function

#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#else
#include <alloca.h>
#endif
#include <stdbool.h>
#include <assert.h>

#include <lua.h>
#include <lauxlib.h>

#include <bool-matrix.h>
#include <sudoku.h>

static int printHello(lua_State* L) {
  (void)L;
  printf("hello lua sudoku\n");
  return 0;
}

static int callback_index_in_registry = 0;

static int create_bool_matrix(lua_State* L) {
  int rows = (int)luaL_checkinteger(L, 1);
  int cols = (int)luaL_checkinteger(L, 2);
  int maxNodes = (int)luaL_checkinteger(L, 3);
  BoolMatrix* matrix = CreateBoolMatrix(rows, cols, maxNodes);
  lua_pushlightuserdata(L, (void*)matrix);
  return 1;
}
static int destroy_bool_matrix(lua_State* L) {
  printf("Destroy Bool Matrix Now\n");
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  BoolMatrix* matrix = (BoolMatrix*)lua_topointer(L, 1);
  DestroyBoolMatrix(matrix);
  return 0;
}
static int set_matrix_row_data(lua_State* L) {
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  luaL_checktype(L, 2, LUA_TTABLE);

  int top = lua_gettop(L); // top point to the top value of stack, not empty
  BoolMatrix* matrix = (BoolMatrix*)lua_topointer(L, 1);
  lua_len(L, 2);
  int size = (int)lua_tointeger(L, top + 1);
#ifdef _WIN32
  int* data = (int*)malloc(sizeof(int) * size);
#else
  int* data = (int*)alloca(sizeof(int) * size);
#endif
  for (int i = 0; i < size; i++) {
    int type = lua_geti(L, 2, i + 1);
    assert(type == LUA_TNUMBER);
    data[i] = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);
  }
  lua_pop(L, 1);
  assert(top == lua_gettop(L));

  SetMatrixRowData(matrix, data, size);

#ifdef _WIN32
  free(data);
#endif

  return 0;
}
typedef struct LuaMatrixData {
  lua_State* L;
  BoolMatrix* matrix;
} LuaMatrixData;
void bool_matrix_answer_callback(void* data, const int* answer, int size) {
  LuaMatrixData* luaMatrix = (LuaMatrixData*)data;
  lua_State* L = luaMatrix->L;

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  type = lua_rawgetp(L, top + 1, (void*)luaMatrix->matrix);
  assert(type == LUA_TFUNCTION);
  lua_createtable(L, size, 0);
  for (int i = 0; i < size; i++) {
    lua_pushinteger(L, answer[i]);
    lua_rawseti(L, top + 3, i + 1);
  }
  int status = lua_pcall(L, 1, 0, 0);
  if (status != LUA_OK) {
    fprintf(stderr, "pcall error: %s\n", lua_tostring(L, -1));
  }
  lua_pushnil(L);
  lua_rawsetp(L, top + 1, (void*)luaMatrix->matrix);
  lua_pop(L, 1);
  assert(top == lua_gettop(L));
}
static int dancing_links(lua_State* L) {
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  luaL_checktype(L, 2, LUA_TBOOLEAN);
  luaL_checktype(L, 3, LUA_TFUNCTION);

  BoolMatrix* matrix = (BoolMatrix*)lua_topointer(L, 1);
  bool justOne = (bool)lua_toboolean(L, 2);

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  lua_pushvalue(L, 3);
  lua_rawsetp(L, top + 1, (void*)matrix);
  lua_pop(L, 1);
  assert(top == lua_gettop(L));

  LuaMatrixData luaMatrix;
  luaMatrix.L = L;
  luaMatrix.matrix = matrix;
  int count = DancingLinks(matrix, justOne, bool_matrix_answer_callback, &luaMatrix);

  lua_pushinteger(L, count);
  return 1;
}

typedef struct LuaSudokuData {
  lua_State* L;
  Sudoku* sudo;
  const void* readFunc;
  const void* writeFunc;
  const void* procCallback;
  const void* answerCallback;
} LuaSudokuData;
static int sudoku_read_data(void* data, int row, int col) {
  LuaSudokuData* luaSudoku = (LuaSudokuData*)data;
  lua_State* L = luaSudoku->L;

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  type = lua_rawgetp(L, top + 1, luaSudoku->readFunc);
  assert(type == LUA_TFUNCTION);
  lua_pushinteger(L, (lua_Integer)row);
  lua_pushinteger(L, (lua_Integer)col);
  int status = lua_pcall(L, 2, 1, 0);
  if (status != LUA_OK) {
    fprintf(stderr, "pcall error: %s\n", lua_tostring(L, -1));
    lua_settop(L, top);
    return 0;
  }
  int ret = lua_tointeger(L, top + 2);
  lua_pop(L, 2);
  assert(top == lua_gettop(L));
  return ret;
}
static void sudoku_write_data(void* data, int row, int col, int value, SolveType sType) {
  LuaSudokuData* luaSudoku = (LuaSudokuData*)data;
  lua_State* L = luaSudoku->L;

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  type = lua_rawgetp(L, top + 1, luaSudoku->writeFunc);
  assert(type == LUA_TFUNCTION);
  lua_pushinteger(L, (lua_Integer)row);
  lua_pushinteger(L, (lua_Integer)col);
  lua_pushinteger(L, (lua_Integer)value);
  lua_pushinteger(L, (lua_Integer)sType);
  int status = lua_pcall(L, 4, 0, 0);
  if (status != LUA_OK) {
    fprintf(stderr, "pcall error: %s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
  }
  lua_pop(L, 1);
  assert(top == lua_gettop(L));
}

#define ADD_PROC_FIELD(field) \
  do { \
    lua_pushinteger(L, (lua_Integer)proc->field); \
    lua_setfield(L, -2, #field); \
  } while (0)

static void solve_process_callback(void* data, SolveProcedure* proc) {
  LuaSudokuData* luaSudoku = (LuaSudokuData*)data;
  if (luaSudoku->procCallback == NULL) {
    return;
  }
  lua_State* L = luaSudoku->L;

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  type = lua_rawgetp(L, top + 1, luaSudoku->procCallback);
  assert(type == LUA_TFUNCTION);

  lua_createtable(L, 0, 20);
  ADD_PROC_FIELD(type);
  ADD_PROC_FIELD(gridOneX);
  ADD_PROC_FIELD(gridOneY);
  ADD_PROC_FIELD(gridTwoX);
  ADD_PROC_FIELD(gridTwoY);
  ADD_PROC_FIELD(gridThreeX);
  ADD_PROC_FIELD(gridThreeY);
  ADD_PROC_FIELD(numberOne);
  ADD_PROC_FIELD(numberTwo);
  ADD_PROC_FIELD(numberThree);
  ADD_PROC_FIELD(panelRow);
  ADD_PROC_FIELD(panelCol);
  ADD_PROC_FIELD(number);
  ADD_PROC_FIELD(rowOne);
  ADD_PROC_FIELD(rowTwo);
  ADD_PROC_FIELD(rowThree);
  ADD_PROC_FIELD(colOne);
  ADD_PROC_FIELD(colTwo);
  ADD_PROC_FIELD(colThree);

  int status = lua_pcall(L, 1, 0, 0);
  if (status != LUA_OK) {
    fprintf(stderr, "pcall error: %s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
  }
  lua_pop(L, 1);
  assert(top == lua_gettop(L));
}
static void sudoku_answer_callback(void* data, const char* ans) {
  LuaSudokuData* luaSudoku = (LuaSudokuData*)data;
  if (luaSudoku->answerCallback == NULL) {
    return;
  }
  lua_State* L = luaSudoku->L;

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  type = lua_rawgetp(L, top + 1, luaSudoku->answerCallback);
  assert(type == LUA_TFUNCTION);
  lua_pushstring(L, ans);
  int status = lua_pcall(L, 1, 0, 0);
  if (status != LUA_OK) {
    fprintf(stderr, "pcall error: %s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
  }
  lua_pushnil(L);
  lua_rawsetp(L, top + 1, luaSudoku->answerCallback);
  lua_pop(L, 1);
  assert(top == lua_gettop(L));
}
static int create_sudoku(lua_State* L) {
  luaL_checktype(L, 1, LUA_TFUNCTION);
  luaL_checktype(L, 2, LUA_TFUNCTION);

  LuaSudokuData* luaSudoku = (LuaSudokuData*)malloc(sizeof(LuaSudokuData));
  luaSudoku->L = L;
  luaSudoku->readFunc = lua_topointer(L, 1);
  luaSudoku->writeFunc = lua_topointer(L, 2);
  if (lua_isnoneornil(L, 3)) {
    luaSudoku->procCallback = NULL;
  } else {
    luaL_checktype(L, 3, LUA_TFUNCTION);
    luaSudoku->procCallback = lua_topointer(L, 3);
  }
  luaSudoku->answerCallback = NULL;

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  lua_pushvalue(L, 1);
  lua_rawsetp(L, top + 1, luaSudoku->readFunc);
  lua_pushvalue(L, 2);
  lua_rawsetp(L, top + 1, luaSudoku->writeFunc);
  if (luaSudoku->procCallback != NULL) {
    lua_pushvalue(L, 3);
    lua_rawsetp(L, top + 1, luaSudoku->procCallback);
  }
  lua_pop(L, 1);
  assert(top == lua_gettop(L));

  luaSudoku->sudo = CreateSudoku(sudoku_read_data, sudoku_write_data, solve_process_callback, (void*)luaSudoku);

  lua_pushlightuserdata(L, (void*)luaSudoku);
  return 1;
}
static int destroy_sudoku(lua_State* L) {
  printf("Destroy Sudoku Now\n");
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  LuaSudokuData* luaSudoku = (LuaSudokuData*)lua_topointer(L, 1);
  DestroySudoku(luaSudoku->sudo);
  free(luaSudoku);

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  lua_pushnil(L);
  lua_rawsetp(L, top + 1, luaSudoku->readFunc);
  lua_pushnil(L);
  lua_rawsetp(L, top + 1, luaSudoku->writeFunc);
  if (luaSudoku->procCallback != NULL) {
    lua_pushnil(L);
    lua_rawsetp(L, top + 1, luaSudoku->procCallback);
  }
  lua_pop(L, 1);
  assert(top == lua_gettop(L));
  return 0;
}
static int verify_sudoku(lua_State* L) {
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  LuaSudokuData* luaSudoku = (LuaSudokuData*)lua_topointer(L, 1);
  bool status = VerifySudoku(luaSudoku->sudo);
  lua_pushboolean(L, (int)status);
  return 1;
}
static int get_known_count(lua_State* L) {
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  LuaSudokuData* luaSudoku = (LuaSudokuData*)lua_topointer(L, 1);
  int count = GetKnownCount(luaSudoku->sudo);
  lua_pushinteger(L, (lua_Integer)count);
  return 1;
}
static int make_result_string(lua_State* L) {
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  LuaSudokuData* luaSudoku = (LuaSudokuData*)lua_topointer(L, 1);
  char buffer[RESULT_BUFFER_SIZE];
  MakeResultString(luaSudoku->sudo, buffer, RESULT_BUFFER_SIZE);
  lua_pushstring(L, buffer);
  return 1;
}
static int calculate_sudoku_all(lua_State* L) {
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  luaL_checktype(L, 2, LUA_TBOOLEAN);

  LuaSudokuData* luaSudoku = (LuaSudokuData*)lua_topointer(L, 1);
  int dancing = lua_toboolean(L, 2);

  if (lua_isnoneornil(L, 3)) {
    luaSudoku->answerCallback = NULL;
  } else {
    luaL_checktype(L, 3, LUA_TFUNCTION);
    luaSudoku->answerCallback = lua_topointer(L, 3);
    int top = lua_gettop(L);
    int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
    assert(type == LUA_TTABLE);
    lua_pushvalue(L, 3);
    lua_rawsetp(L, top + 1, luaSudoku->answerCallback);
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
  }

  int count = CalculateSudokuAll(luaSudoku->sudo, (bool)dancing, sudoku_answer_callback, (void*)luaSudoku);

  lua_pushinteger(L, (lua_Integer)count);
  return 1;
}

static int verify_sudoku_board(lua_State* L) {
  luaL_checktype(L, 1, LUA_TTABLE);

  int top = lua_gettop(L);
  lua_len(L, 1);
  int size = (int)lua_tointeger(L, top + 1);
#ifdef _WIN32
  int* data = (int*)malloc(sizeof(int) * size);
#else
  int* data = (int*)alloca(sizeof(int) * size);
#endif
  for (int i = 0; i < size; i++) {
    int type = lua_geti(L, 1, i + 1);
    assert(type == LUA_TNUMBER);
    data[i] = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);
  }
  lua_pop(L, 1);
  assert(top == lua_gettop(L));

  bool status = VerifySudokuBoard(data);

#ifdef _WIN32
  free(data);
#endif

  lua_pushboolean(L, (int)status);
  return 1;
}
static int solve_type_name(lua_State* L) {
  luaL_checktype(L, 1, LUA_TNUMBER);
  int type = (int)lua_tointeger(L, 1);
  lua_pushstring(L, SolveTypeName((SolveType)type));
  return 1;
}
static int improve_type_name(lua_State* L) {
  luaL_checktype(L, 1, LUA_TNUMBER);
  int type = (int)lua_tointeger(L, 1);
  lua_pushstring(L, ImproveTypeName((ImproveType)type));
  return 1;
}

static luaL_Reg luaLoadFun[] = {
    {"printHello", printHello},
    // for BoolMatrix
    {"CreateBoolMatrix", create_bool_matrix},
    {"DestroyBoolMatrix", destroy_bool_matrix},
    {"SetMatrixRowData", set_matrix_row_data},
    {"DancingLinks", dancing_links},
    // for Sudoku
    {"CreateSudoku", create_sudoku},
    {"DestroySudoku", destroy_sudoku},
    {"VerifySudokuBoard", verify_sudoku_board},
    {"VerifySudoku", verify_sudoku},
    {"GetKnownCount", get_known_count},
    {"MakeResultString", make_result_string},
    {"CalculateSudokuAll", calculate_sudoku_all},
    {"SolveTypeName", solve_type_name},
    {"ImproveTypeName", improve_type_name},
    {NULL, NULL},
};

LUAMOD_API int luaopen_libluasudoku(lua_State* L) {
  int top = lua_gettop(L);
  if (callback_index_in_registry == 0) {
    lua_createtable(L, 0, 16);
    callback_index_in_registry = luaL_ref(L, LUA_REGISTRYINDEX);
  }
  assert(top == lua_gettop(L));

  //   printf("First argument: %s\n", lua_tostring(L, 1));
  //   printf("Second argument: %s\n", lua_tostring(L, 2));
  luaL_newlib(L, luaLoadFun);
  // luaL_newlib will check lua runtime and runtime version
  // Use Marco for version number (when compile this module, the lua version
  // will fixed in code) the argument lua_State *L is passed from the caller
  // which has a runtime(1) and, this module link with a runtime(2) dylib so,
  // this luaL_newlib will call the runtime(2), it has a version and version
  // pointer lua_State *L has a version pointer, if (runtime2->pversion !=
  // runtime1->pversion) then there are different runtime dylib (case the lua
  // are link static) check version contains three data
  // 1. version number in the module
  // 2. version pointer in the lua_State *L, passed from caller
  // 3. version pointer in the dylib the module dylink with
  return 1;
}
