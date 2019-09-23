# Sudoku

[![Build Status](https://travis-ci.com/zhyingkun/Sudoku.svg)](https://travis-ci.com/zhyingkun/Sudoku)

---

## 基本介绍

1. 本工程是数独解决方案的库工程，包含 Demo 用例
2. 支持 Debug/Release 编译模式
3. 整个工程 PC 端编译构建采用 cmake 来管理，支持跨平台（可以在树莓派上正常 cmake+make）
4. 移动端 iOS 直接给出 Xcode 工程，Android 则提供 Android.md 用于 ndk-build
5. 提供 C#、Go、Java、Lua、NodeJS、PHP 和 Python 共 7 种语言调用数独 Native 动态库的 Demo 用例

---

## 关于数独

1. 本库提供求数独解的两种方法，以及求解精确覆盖问题的通用布尔矩阵
2. 第一种解法是按照人们解题思路技巧，换用计算机实现，具体思路技巧参考[琳琅在线](http://www.llang.net/sudoku/skill/1.html)
3. 第二种解法为回溯遍历，根据数独规则将数独问题转化为布尔矩阵的精确覆盖问题，并使用 DancingLinks 算法高效求解，这种方式可以算出所有可能的解，
4. DancingLinks 算法的实现参考[陈硕的 Github](https://github.com/chenshuo/muduo/blob/master/examples/sudoku/sudoku.cc)，此算法的作者是算法大师高德纳(Donald E. Knuth，《计算机程序设计艺术》丛书的作者)，这是该算法[原文链接](www-cs-faculty.stanford.edu/~uno/papers/dancing-color.ps.gz)，我给导出了[pdf 版](./dancing-color.pdf)，原算法将数独问题的转换和求解耦合在一起，为了更加明确解法思路，我将其拆分为两部分，分别是数独问题转换成布尔矩阵和求解布尔矩阵
5. 陈硕的[CSDN 博客](https://blog.csdn.net/Solstice/article/details/2096209)对数独有一个概括性的说明，如何将数独问题转化成布尔矩阵的精确覆盖问题可以参考[这篇博客](https://www.cnblogs.com/grenet/p/3163550.html)，DancingLinks 求解精确覆盖算法原理可以参考[这篇博客](https://www.cnblogs.com/grenet/p/3145800.html)

---

## 如何编译

1. 在 Mac 上采用 Xcode 编译

```bash
cd Sudoku/
mkdir buildXcode && cd buildXcode
cmake -DCMAKE_INSTALL_PREFIX=./install -G "Xcode" ..
# cmake -DCMAKE_INSTALL_PREFIX=/usr/local/zyk -G "Xcode" ..
```

此时已经在 buildXcode 文件夹下生成了 Xcode 工程，直接打开并编译即可

2. 直接命令行编译（支持 Mac 和 Linux）

```bash
cd Sudoku/
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=./install .. # default is Debug
# for Debug: cmake -DCMAKE_BUILD_TYPE=Debug ..
# for Release: cmake -DCMAKE_BUILD_TYPE=Release ..
make
# for more details: make VERBOSE=1
make install
```

make 命令会自动编译好各个模块

3. 在 Windows 上使用 Cygwin + Visual Studio 2017 进行编译

```bash
cd Sudoku/
mkdir buildVS && cd buildVS
cmake -DCMAKE_INSTALL_PREFIX=./install -G "Visual Studio 15 2017 Win64" ..
```

此时已经在 buildVS 文件夹下生成了 Visual Studio 工程，双击打开并编译即可

4. 在 Mac 上编译出用于 iOS 的 sudoku.a 静态库（直接 Xcode 打开 sudoku 工程文件）

```bash
cd Sudoku/sudoku/iOS
open sudoku.xcodeproj
```

编译该 iOS Xcode 工程即可得到 sudoku.a 库

5. 使用 NDK 编译出用于 Android 的 libsudoku.so 共享库

```bash
cd Sudoku/sudoku/Android/
ndk-build
ndk-build clean # clean project
ndk-build -B # rebuild project
```

编译之后便会有 Sudoku/sudoku/Android/libs/\${APP_ABI}/libsudoku.so 共享库
使用 ndk-build 命令需要先安装 AndroidStudio+AndroidSDK+NDK，然后将 ndk-bundle 路径加到系统 PATH 环境变量中

---

## 文件夹说明

1. include：供外部调用的头文件
2. sudoku：数独库
   - test：测试代码
   - src：源码
   - iOS：iOS 静态库的 xcode 工程
   - Android：用于编译 Android 动态库
3. demo：用于测试的 Demo，包含多种编程语言
   - for-c：C 语言用例（已在 Mac/Linux/Windows 跑通）
   - for-cs：C#语言用例（已在 Mac/Linux/Windows 跑通）
   - for-go：Go 语言用例（已在 Mac/Linux 跑通）
   - for-java：Java 语言用例（已在 Mac/Linux 跑通）
   - for-lua：Lua 语言用例（已在 Mac/Linux/Windows 跑通）
   - for-nodejs：NodeJS 语言用例（待处理）
   - for-php：PHP 语言用例（待处理）
   - for-python：Python 语言用例（待处理）
4. data：存放用于测试的数独案例
5. tools：工具脚本
   - SudokuTable.xlsx：辅助填充表，来自[林健随笔](https://linjian.org/blog/tech/programming/others/sudoku-table)
   - diff-sudoku：用于比较两个数独的区别
   - format-sudoku：数独格式化工具
6. 所有 CMakeLists.txt：用于构建整个工程
7. oldcode：旧代码，刚学 C++时写的，做个备份记录

---

## 数独库 API 说明

### Sudoku

1. CreateSudoku：创建数独对象，获取句柄用于后续操作，传入读函数和写函数，读函数用于读取数独题目，写函数用于写出答案
2. DestroySudoku：创建的反操作，销毁该对象
3. VerifySudokuBoard：验证传入的 81 整数组成的数组是否是数独的有效解
4. VerifySudoku：验证数独对象内部保存的内容是否为数独的有效解
5. GetKnownCount：获取当前数独对象内部的内容中有多少个已知数
6. MakeResultString：将数独对象内部记录的内容格式化成一个字符串
7. CalculateSudokuAll：计算数独答案，dancing 用于指定是否采用舞蹈链算法来处理，cb 为找到一个可用解时的回调函数，data 为传递给回调函数的透传字段（舞蹈链算法其实是算布尔矩阵的精确覆盖问题，只是数独可以转化成一个布尔矩阵，因此可用此算法来遍历得到所有解）
8. 当采用舞蹈链来算数独答案时，SudokuWriteData 回调函数的 type 字段固定为 None，因为此时并没有相关模式（该回调函数被调用顺序也就是解题过程的顺序）

### BoolMatrix

1. CreateBoolMatrix：创建一个布尔矩阵对象，传入参数分别为矩阵行数、矩阵列数、矩阵中值为 1 的节点个数
2. DestroyBoolMatrix：释放布尔矩阵占用的内存空间
3. SetMatrixRowData：设置布尔矩阵的每一行，注意这里需要按照布尔矩阵的行顺序进行设置，data 为一个整数数组，数组中的数字 n 表示这一行中第 n 列的节点值为 1，n 取值范围为[0, 列数-1]，size 表示 data 数组的长度
4. DancingLinks：触发舞蹈链算法，justOne 表示是否找到一个解就退出，data 为回调函数 cb 的透传字段
