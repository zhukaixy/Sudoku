# Demo 使用方式

## Demo 运行前提

1. 按照[主 README 文件](../README.md)的说明，根据平台编译出 sudoku 动态库（支持 Mac/Linux/Windows+Cygwin）
2. 注意，三个平台对应的编译目录为 buildXcode、build、buildVS，Windows 平台安装目录为 install（假如自定义目录，则对应 Makefile 配置也需要修改）
3. 由于 Mac 和 Linux 下支持链接-rpath 编译参数，因此编译结束无需 install 就可以运行，windows 下则必须 install 之后，从 install 目录执行对应 exe（Windows 下 install 方式：VisualStudio 中打开 CMake 生成的 sln 文件之后，编译 ALL_BUILD 目标，之后生成 install 目标即可安装）

## 语言环境搭建

1. Xcode、Linux 命令行编译工具和 VisualStudio 之类的基础工具
2. C#采用跨平台的 Mono，因此需要[安装 Mono](https://www.mono-project.com)
3. Go 语言环境，需要[安装 Go](https://golang.org)
4. Java 环境需要 JDK，并配置 JDK 环境变量（主要是 JAVA_HOME 环境变量，需要靠它找到 jni.h）
5. Lua 的命令行工具和动态库已经放在工程中，直接 make 执行即可，无需安装

## 编译和执行命令

Mac/Linux/Windows+Cygwin：

```bash
cd Sudoku/demo/${for-lang}
make # 编译代码
make run # 执行Demo
```

其中，\${for-lang}代表具体语言的 Demo 目录

## 问题记录

1. Windows 下的 fopen 函数只能打开 windows 格式的路径名，即使是在 cygwin 环境下运行，因此在 Makefile 中，需要使用重定向标准输入的方式输入数据，或者针对 cygwin 环境下调用 cygpath 命令进行转换
2. C#的 for-cs.csproj 工程文件中不可以指定 TargetFrameworkVersion，否则有些不存在该指定版本的环境下就会编译失败，反正 Demo 只用到很少的功能，采用环境默认的 Runtime 版本就好
3. Go 语言工具用起来是比较舒服的，只是在 Windows 下用 cgo 编译会报错，错误为\_beginthread 函数未声明，目前尚未解决
4. cgo 中有些往 C 传递结构体指针需要先引用第一个字段再取地址，不明白为什么这样做就可以，如 CreateSudoku 函数
5. 在 Linux/Windows 中，除了要引用\${JAVA_HOME}环境变量下的 include 目录，还要引用 include 下面的 linux/win32 目录，不然会有一些头文件找不到
6. Java 的 Demo 在 Windows 下编译失败，错误：未知的类型名‘\_\_int64’，目前尚未解决
