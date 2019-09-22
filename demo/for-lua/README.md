# 将动态库 API 导出到 Lua

## 操作流程

1. 定义好在 Lua 端调用动态库的 API（Lua 要传什么参数给 C）
2. 编写 C 语言动态库形式 Lua 模块，在该模块中去调用我们的目标动态库函数，并对参数做转换，传递给 Lua，如 luasudoku.c
3. 编译动态库
4. 编写 Lua 端导入该模块和调用函数，如 sudoku.lua、boolmatrix.lua
5. 这里涉及两个动态库，一是目标库，如 libsudoku.so，二是胶水转换参数的动态库，如 libluasudoku.so
6. 运行时需要让 Lua 找到胶水模块，为了简单可以采用 LUA_CPATH 环境变量，也可以自定义（在 Lua 代码中写或者其他方式）
7. runtime 中给出的二进制文件是针对某个版本的 OS 编译的，可能有些比较旧的系统跑不起来，可以从[这个 Github 地址](https://github.com/zhyingkun/lua-5.3.5)获取 Lua 工程手动编译出目标二进制文件
8. Lua 搜索 Lua 模块的环境变量：LUA_PATH
