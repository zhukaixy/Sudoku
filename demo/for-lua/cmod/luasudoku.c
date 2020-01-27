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

static int create_bool_matrix(lua_State* L) {
  int rows = (int)luaL_checkinteger(L, 1);
  int cols = (int)luaL_checkinteger(L, 2);
  int maxNodes = (int)luaL_checkinteger(L, 3);

  BoolMatrix** mat = (BoolMatrix**)lua_newuserdata(L, sizeof(BoolMatrix*));
  *mat = NULL;

  luaL_getmetatable(L, "BoolMatrix");
  lua_setmetatable(L, -2);

  *mat = CreateBoolMatrix(rows, cols, maxNodes);
  if (*mat == NULL)
    luaL_error(L, "cannot create bool matrix");

  return 1;
}

static int destroy_bool_matrix(lua_State* L) {
  printf("Destroy Bool Matrix Now\n");
  BoolMatrix** mat = (BoolMatrix**)luaL_checkudata(L, 1, "BoolMatrix");
  if (*mat != NULL) {
    DestroyBoolMatrix(*mat);
  }
  return 0;
}

static int set_matrix_row_data(lua_State* L) {
  BoolMatrix** mat = (BoolMatrix**)luaL_checkudata(L, 1, "BoolMatrix");
  luaL_checktype(L, 2, LUA_TTABLE);
  BoolMatrix* matrix = *mat;

  int top = lua_gettop(L); // top point to the top value of stack, not empty
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

void bool_matrix_answer_callback(void* data, const int* answer, int size) {
  lua_State* L = (lua_State*)data;

  lua_pushvalue(L, 3); // index 3 is the function
  lua_createtable(L, size, 0);
  for (int i = 0; i < size; i++) {
    lua_pushinteger(L, answer[i]);
    lua_rawseti(L, -2, i + 1);
  }
  lua_call(L, 1, 0);
}

static int dancing_links(lua_State* L) {
  BoolMatrix** mat = (BoolMatrix**)luaL_checkudata(L, 1, "BoolMatrix");
  luaL_checktype(L, 2, LUA_TBOOLEAN);
  luaL_checktype(L, 3, LUA_TFUNCTION);

  // lua_pushvalue(L, 3);
  // lua_setuservalue(L, 1);

  int count = DancingLinks(*mat, (bool)lua_toboolean(L, 2), bool_matrix_answer_callback, (void*)L);

  lua_pushinteger(L, count);
  return 1;
}

typedef struct LuaSudokuData {
  lua_State* L;
  Sudoku* sudo;
  const void* readFunc;
  const void* writeFunc;
  const void* procCallback;
  // const void* answerCallback;
} LuaSudokuData;

static int callback_index_in_registry = 0;

static int sudoku_read_data(void* data, int row, int col) {
  LuaSudokuData* luaSudoku = (LuaSudokuData*)data;
  lua_State* L = luaSudoku->L;

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  type = lua_rawgetp(L, -1, luaSudoku->readFunc);
  assert(type == LUA_TFUNCTION);
  lua_pushinteger(L, (lua_Integer)row);
  lua_pushinteger(L, (lua_Integer)col);
  lua_call(L, 2, 1);
  int ret = lua_tointeger(L, -1);
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
  type = lua_rawgetp(L, -1, luaSudoku->writeFunc);
  assert(type == LUA_TFUNCTION);
  lua_pushinteger(L, (lua_Integer)row);
  lua_pushinteger(L, (lua_Integer)col);
  lua_pushinteger(L, (lua_Integer)value);
  lua_pushinteger(L, (lua_Integer)sType);
  lua_call(L, 4, 0);
  lua_pop(L, 1);
  assert(top == lua_gettop(L));
}

static void solve_process_callback(void* data, SolveProcedure* proc) {
  LuaSudokuData* luaSudoku = (LuaSudokuData*)data;
  if (luaSudoku->procCallback == NULL) {
    return;
  }
  lua_State* L = luaSudoku->L;

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  type = lua_rawgetp(L, -1, luaSudoku->procCallback);
  assert(type == LUA_TFUNCTION);

  lua_createtable(L, 0, 20);

#define ADD_PROC_FIELD(field) \
  do { \
    lua_pushinteger(L, (lua_Integer)proc->field); \
    lua_setfield(L, -2, #field); \
  } while (0)
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
#undef ADD_PROC_FIELD

  lua_call(L, 1, 0);
  lua_pop(L, 1);
  assert(top == lua_gettop(L));
}

static void sudoku_answer_callback(void* data, const char* ans) {
  LuaSudokuData* luaSudoku = (LuaSudokuData*)data;
  lua_State* L = luaSudoku->L;
  if (lua_type(L, 3) != LUA_TFUNCTION) {
    return;
  }
  lua_pushvalue(L, 3);
  lua_pushstring(L, ans);
  lua_call(L, 1, 0);
}

static int create_sudoku(lua_State* L) {
  luaL_checktype(L, 1, LUA_TFUNCTION);
  luaL_checktype(L, 2, LUA_TFUNCTION);
  lua_settop(L, 3);

  LuaSudokuData* luaSudoku = (LuaSudokuData*)lua_newuserdata(L, sizeof(LuaSudokuData));
  luaSudoku->L = L;
  luaSudoku->readFunc = lua_topointer(L, 1);
  luaSudoku->writeFunc = lua_topointer(L, 2);
  luaSudoku->sudo = NULL;
  if (lua_isnoneornil(L, 3)) {
    luaSudoku->procCallback = NULL;
  } else {
    luaL_checktype(L, 3, LUA_TFUNCTION);
    luaSudoku->procCallback = lua_topointer(L, 3);
  }

  luaL_getmetatable(L, "Sudoku");
  lua_setmetatable(L, -2);

  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  lua_pushvalue(L, 1);
  lua_rawsetp(L, -2, luaSudoku->readFunc);
  lua_pushvalue(L, 2);
  lua_rawsetp(L, -2, luaSudoku->writeFunc);
  if (luaSudoku->procCallback != NULL) {
    lua_pushvalue(L, 3);
    lua_rawsetp(L, -2, luaSudoku->procCallback);
  }
  lua_pop(L, 1);

  luaSudoku->sudo = CreateSudoku(sudoku_read_data, sudoku_write_data, solve_process_callback, (void*)luaSudoku);
  if (luaSudoku->sudo == NULL)
    luaL_error(L, "cannot create sudoku");

  return 1;
}

static int destroy_sudoku(lua_State* L) {
  printf("Destroy Sudoku Now\n");
  LuaSudokuData* luaSudoku = (LuaSudokuData*)luaL_checkudata(L, 1, "Sudoku");
  if (luaSudoku->sudo != NULL) {
    DestroySudoku(luaSudoku->sudo);
  }
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
  LuaSudokuData* luaSudoku = (LuaSudokuData*)luaL_checkudata(L, 1, "Sudoku");
  bool status = VerifySudoku(luaSudoku->sudo);
  lua_pushboolean(L, (int)status);
  return 1;
}

static int get_known_count(lua_State* L) {
  LuaSudokuData* luaSudoku = (LuaSudokuData*)luaL_checkudata(L, 1, "Sudoku");
  int count = GetKnownCount(luaSudoku->sudo);
  lua_pushinteger(L, (lua_Integer)count);
  return 1;
}

static int make_result_string(lua_State* L) {
  LuaSudokuData* luaSudoku = (LuaSudokuData*)luaL_checkudata(L, 1, "Sudoku");
  char buffer[RESULT_BUFFER_SIZE];
  MakeResultString(luaSudoku->sudo, buffer, RESULT_BUFFER_SIZE);
  lua_pushstring(L, buffer);
  return 1;
}

static int calculate_sudoku_all(lua_State* L) {
  LuaSudokuData* luaSudoku = (LuaSudokuData*)luaL_checkudata(L, 1, "Sudoku");
  luaL_checktype(L, 2, LUA_TBOOLEAN);
  int dancing = lua_toboolean(L, 2);

  lua_settop(L, 3);

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

static luaL_Reg BoolMatrix__index[] = {
    {"SetMatrixRowData", set_matrix_row_data},
    {"DancingLinks", dancing_links},
};

static luaL_Reg Sudoku__index[] = {
    {"VerifySudoku", verify_sudoku},
    {"GetKnownCount", get_known_count},
    {"MakeResultString", make_result_string},
    {"CalculateSudokuAll", calculate_sudoku_all},
};

static luaL_Reg luaLoadFun[] = {
    {"printHello", printHello},
    // for BoolMatrix
    {"CreateBoolMatrix", create_bool_matrix},
    // for Sudoku
    {"CreateSudoku", create_sudoku},
    {"VerifySudokuBoard", verify_sudoku_board},
    {"SolveTypeName", solve_type_name},
    {"ImproveTypeName", improve_type_name},
    {NULL, NULL},
};

LUAMOD_API int luaopen_libluasudoku(lua_State* L) {
  luaL_newmetatable(L, "BoolMatrix");
  lua_createtable(L, 0, sizeof(BoolMatrix__index) / sizeof(BoolMatrix__index[0]));
  luaL_setfuncs(L, BoolMatrix__index, 0);
  lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, destroy_bool_matrix);
  lua_setfield(L, -2, "__gc");

  luaL_newmetatable(L, "Sudoku");
  lua_createtable(L, 0, sizeof(Sudoku__index) / sizeof(Sudoku__index[0]));
  luaL_setfuncs(L, Sudoku__index, 0);
  lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, destroy_sudoku);
  lua_setfield(L, -2, "__gc");

  int top = lua_gettop(L);
  if (callback_index_in_registry == 0) {
    lua_createtable(L, 0, 16);
    callback_index_in_registry = luaL_ref(L, LUA_REGISTRYINDEX);
  }
  assert(top == lua_gettop(L));

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
