# Sudoku

[![Build Status](https://travis-ci.com/zhyingkun/Sudoku.svg)](https://travis-ci.com/zhyingkun/Sudoku)

----

## 基本介绍

1. 本工程是数独解决方案的库工程，包含Demo用例
2. 支持Debug/Release编译模式
3. 整个工程PC端编译构建采用cmake来管理，支持跨平台（可以在树莓派上正常cmake+make）
4. 移动端iOS直接给出Xcode工程，Android则提供Android.md用于ndk-build

----

## 关于数独
1. 本库提供求数独解的两种方法，以及求解精确覆盖问题的通用布尔矩阵
2. 第一种解法是按照人们解题思路技巧，换用计算机实现，具体思路技巧参考[琳琅在线](http://www.llang.net/sudoku/skill/1.html)
3. 第二种解法为回溯遍历，根据数独规则将数独问题转化为布尔矩阵的精确覆盖问题，并使用DancingLinks算法高效求解，这种方式可以算出所有可能的解，
4. DancingLinks算法的实现参考[陈硕的Github](https://github.com/chenshuo/muduo/blob/master/examples/sudoku/sudoku.cc)，此算法的作者是算法大师高德纳(Donald E. Knuth，《计算机程序设计艺术》丛书的作者)，这是该算法[原文链接](www-cs-faculty.stanford.edu/~uno/papers/dancing-color.ps.gz)，我给导出了[pdf版](./dancing-color.pdf)，原算法将数独问题的转换和求解耦合在一起，为了更加明确解法思路，我将其拆分为两部分，分别是数独问题转换成布尔矩阵和求解布尔矩阵
5. 陈硕的[CSDN博客](https://blog.csdn.net/Solstice/article/details/2096209)对数独有一个概括性的说明，如何将数独问题转化成布尔矩阵的精确覆盖问题可以参考[这篇博客](https://www.cnblogs.com/grenet/p/3163550.html)，DancingLinks求解精确覆盖算法原理可以参考[这篇博客](https://www.cnblogs.com/grenet/p/3145800.html)

----

## 如何编译

1. 在Mac上采用Xcode编译
```bash
cd Sudoku/
mkdir buildXcode && cd buildXcode
cmake -DCMAKE_INSTALL_PREFIX=./install -G "Xcode" ..
# cmake -DCMAKE_INSTALL_PREFIX=/usr/local/zyk -G "Xcode" ..
```
此时已经在buildXcode文件夹下生成了Xcode工程，直接打开并编译即可

2. 直接命令行编译（支持Mac和Linux）
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
make命令会自动编译好各个模块

3. 在Windows上使用Cygwin + Visual Studio 2017进行编译
```bash
cd Sudoku/
mkdir buildVS && cd buildVS
cmake -DCMAKE_INSTALL_PREFIX=./install -G "Visual Studio 15 2017 Win64" ..
```
此时已经在buildVS文件夹下生成了Visual Studio工程，双击打开并编译即可

4. 在Mac上编译出用于iOS的sudoku.a静态库（直接Xcode打开sudoku工程文件）
```bash
cd Sudoku/sudoku/iOS
open sudoku.xcodeproj
```
编译该iOS Xcode工程即可得到sudoku.a库

5. 使用NDK编译出用于Android的sudoku.so共享库
```bash
cd Sudoku/sudoku/Android/
ndk-build
ndk-build clean # clean project
ndk-build -B # rebuild project
```
编译之后便会有Sudoku/sudoku/Android/libs/${APP_ABI}/sudoku.so共享库
使用ndk-build命令需要先安装AndroidStudio+AndroidSDK+NDK，然后将ndk-bundle路径加到系统PATH环境变量中

----

## 文件夹说明

1. include：供外部调用的头文件
2. sudoku：数独库
	+ include：内部使用的头文件
	+ src：源码
	+ iOS：iOS静态库的xcode工程
	+ Android：用于编译Android动态库
3. demo：用于测试的Demo，包含多种编程语言
	+ for-c：C语言用例
	+ for-cs：C#语言用例
	+ for-go：
	+ for-java：
	+ for-lua：Lua语言用例
	+ for-nodejs：NodeJS语言用例
	+ for-php：
	+ for-python：
4. data：存放用于测试的数独案例
5. tools：工具脚本
	+ SudokuTable.xlsx：辅助填充表，来自[林健随笔](https://linjian.org/blog/tech/programming/others/sudoku-table)
	+ diff-sudoku：用于比较两个数独的区别
	+ format-sudoku：数独格式化工具
6. 所有CMakeLists.txt：用于构建整个工程

----

## 数独库API说明

### Sudoku

1. CreateSudoku：创建数独对象，获取句柄用于后续操作，传入读函数和写函数，读函数用于读取数独题目，写函数用于写出答案
2. DestroySudoku：创建的反操作，销毁该对象
3. VerifySudokuBoard：验证传入的81整数组成的数组是否是数独的有效解
4. VerifySudoku：验证数独对象内部保存的内容是否为数独的有效解
5. GetKnownCount：获取当前数独对象内部的内容中有多少个已知数
6. MakeResultString：将数独对象内部记录的内容格式化成一个字符串
7. CalculateSudokuAll：计算数独答案，dancing用于指定是否采用舞蹈链算法来处理，cb为找到一个可用解时的回调函数，data为传递给回调函数的透传字段（舞蹈链算法其实是算布尔矩阵的精确覆盖问题，只是数独可以转化成一个布尔矩阵，因此可用此算法来遍历得到所有解）
8. 当采用舞蹈链来算数独答案时，SudokuWriteData回调函数的type字段固定为None，因为此时并没有相关模式（该回调函数被调用顺序也就是解题过程的顺序）

### BoolMatrix

1. CreateBoolMatrix：创建一个布尔矩阵对象，传入参数分别为矩阵行数、矩阵列数、矩阵中值为1的节点个数
2. DestroyBoolMatrix：释放布尔矩阵占用的内存空间
3. SetMatrixRowData：设置布尔矩阵的每一行，注意这里需要按照布尔矩阵的行顺序进行设置，data为一个整数数组，数组中的数字n表示这一行中第n列的节点值为1，n取值范围为[0, 列数-1]，size表示data数组的长度
4. DancingLinks：触发舞蹈链算法，justOne表示是否找到一个解就退出，data为回调函数cb的透传字段
