# Java 与 C 语言互调

## JNI 操作流程

1. 设计好 Java 代码与 JNI 的接口类，如 SudokuLib.java
2. 执行 `javac xxx.java` 编译该 java 文件，生成对应.class 文件
3. 执行 `javah xxx` 生成对应的.h 头文件，如 SudokuLib.h，-d 参数可以指定头文件生成路径
4. 根据.h 头文件编写相应的.c 源文件，在源文件中调用原生库方法，并通过 JNI 相关 API 给 Java 层传递参数，如 SudokuLib.c
5. 通过 gcc 命令 `gcc -dynamiclib -o libxxx.jnilib xxx.c -lxxxx` 生成对应动态库（或者通过其他方式生成，linux 要带上-shared -fPIC 参数）
6. 撰写 Java 层调用 JNI 接口类的相关函数，并通过 javac 编译和 java 命令运行

## 命令归纳如下：

```bash
javac SudokuLib.java
javah SudokuLib
gcc -dynamiclib -o libsudokujni.jnilib SudokuLib.c SudokuLib.h -lsudoku
javac Main.java
java Main
```

## 关于 Windows 下运行 Java 的 Demo

1. Windows+Cygwin 的环境下，通过 gcc 无法编译出 sudokujni.dll 动态库
2. Windows 下需要单独写 CMakeLists.txt，并通过 VisualStudio 编译出 sudokujni.dll 动态库

## Windows 下编译 sudokujni.dll

在 Cygwin 下，执行如下命令

```bash
cd for-java/jni
mkdir buildVS && cd buildVS
cmake -G "Visual Studio 15 2017 Win64" ..
# 在 Visual Studio + Release 模式下编译该动态库
cp Release/sudokujni.dll ../../build/sudokujni.dll
cd ../../ && make allclass && make run
```
