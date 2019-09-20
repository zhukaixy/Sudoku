/* Lua C Library */

#define LUA_LIB // for export function

#include <stdio.h>
#include <alloca.h>
#include <stdbool.h>
#include <assert.h>

#include <lua.h>
#include <lauxlib.h>

#include <bool-matrix.h>

static int callback_index_in_registry = 0;

static int lua_create_bool_matrix(lua_State* L) {
  int rows = luaL_checkinteger(L, 1);
  int cols = luaL_checkinteger(L, 2);
  int maxNodes = luaL_checkinteger(L, 3);
  BoolMatrix* matrix = CreateBoolMatrix(rows, cols, maxNodes);

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  lua_createtable(L, 0, 1);
  lua_rawsetp(L, top + 1, (void*)matrix);

  lua_pushlightuserdata(L, (void*)matrix);
  return 1;
}
static int lua_destroy_bool_matrix(lua_State* L) {
  printf("Destroy Bool Matrix Now\n");
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  BoolMatrix* matrix = (BoolMatrix*)lua_topointer(L, 1);
  DestroyBoolMatrix(matrix);
  return 0;
}
static int lua_set_matrix_row_data(lua_State* L) {
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  BoolMatrix* matrix = (BoolMatrix*)lua_topointer(L, 1);
  luaL_checkany(L, 2);
  luaL_checktype(L, 2, LUA_TTABLE);
  lua_len(L, 2);
  int size = lua_tointeger(L, 3);
  int* data = alloca(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    int type = lua_geti(L, 2, i + 1);
    assert(type == LUA_TNUMBER);
    data[i] = lua_tointeger(L, -1);
    lua_pop(L, 1);
  }
  SetMatrixRowData(matrix, data, size);
  return 0;
}
typedef struct LuaData {
  lua_State* L;
  void* data;
} LuaData;
void bool_matrix_answer_callback(void* data, const int* answer, int size) {
  LuaData* pData = (LuaData*)data;
  lua_State* L = pData->L;
  BoolMatrix* matrix = pData->data;

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  type = lua_rawgetp(L, top + 1, (void*)matrix);
  assert(type == LUA_TTABLE);
  lua_getfield(L, top + 2, "BoolMatrixAnswerCallback");
  lua_createtable(L, size, 0);
  for (int i = 0; i < size; i++) {
    lua_pushinteger(L, answer[i]);
    lua_rawseti(L, top + 4, i + 1);
  }
  int status = lua_pcall(L, 1, 0, 0);
  if (status != LUA_OK) {
    printf("pcall error: %s\n", lua_tostring(L, -1));
  }

  lua_settop(L, top);
}
static int lua_dancing_links(lua_State* L) {
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  BoolMatrix* matrix = (BoolMatrix*)lua_topointer(L, 1);
  luaL_checktype(L, 2, LUA_TBOOLEAN);
  bool justOne = (bool)lua_toboolean(L, 2);
  luaL_checktype(L, 3, LUA_TFUNCTION);

  int top = lua_gettop(L);
  int type = lua_rawgeti(L, LUA_REGISTRYINDEX, callback_index_in_registry);
  assert(type == LUA_TTABLE);
  type = lua_rawgetp(L, top + 1, (void*)matrix);
  assert(type == LUA_TTABLE);
  lua_pushvalue(L, 3);
  lua_setfield(L, top + 2, "BoolMatrixAnswerCallback");

  LuaData luaData;
  luaData.L = L;
  luaData.data = (void*)matrix;
  int count = DancingLinks(matrix, justOne, bool_matrix_answer_callback, &luaData);
  lua_pushinteger(L, count);
  return 1;
}

static int printHello(lua_State* L) {
  (void)L;
  printf("hello mod\n");
  return 0;
}

// clang-format off
static luaL_Reg luaLoadFun[] = {
	{"printHello", printHello},
  {"CreateBoolMatrix", lua_create_bool_matrix},
  {"DestroyBoolMatrix", lua_destroy_bool_matrix},
  {"SetMatrixRowData", lua_set_matrix_row_data},
  {"DancingLinks", lua_dancing_links},
	{NULL, NULL}
};
// clang-format on

LUAMOD_API int luaopen_libluasudoku(lua_State* L) {
  if (callback_index_in_registry == 0) {
    lua_createtable(L, 0, 8);
    callback_index_in_registry = luaL_ref(L, LUA_REGISTRYINDEX);
  }

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
