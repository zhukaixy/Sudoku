# Sudoku

[![Build Status](https://travis-ci.com/zhyingkun/Sudoku.svg)](https://travis-ci.com/zhyingkun/Sudoku)

----

## 基本介绍

1. 本工程是数独解决方案的库工程，包含Demo用例
2. 支持Debug/Release编译模式
3. 整个工程PC端编译构建采用cmake来管理，支持跨平台（可以在树莓派上正常cmake+make）
4. 移动端iOS直接给出Xcode工程，Android则提供Android.md用于ndk-build

----

## 如何编译

1. 在Mac上采用Xcode编译
```bash
cd Sudoku/
mkdir buildXcode && cd buildXcode
cmake -DCMAKE_INSTALL_PREFIX=./install -G "Xcode" ..
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
	+ for-lua：Lua语言用例
	+ for-nodejs：NodeJS语言用例
4. data：存放用于测试的数独案例
5. tools：工具脚本
6. 所有CMakeLists.txt：用于构建整个工程
