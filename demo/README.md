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
6. NodeJS 工具链可从[官网](https://nodejs.org/en/)获得，JS 调用 C 库有两种方式，第一种是将 C 库做成 Node 模块，第二种是通过第三方库 ffi 进行动态加载（这里采用第二种来实现布尔矩阵的调用，简单方便，虽然运行效率低一些）
7. PHP 由于需要 PHP 源码参与编译，并且除 Web 外很少使用，因此仅提供 Linux 版，具体请看[此 README](./for-php/README.md)
8. Python 采用的是 python3，可从[官网](https://www.python.org)下载安装

## 编译和执行命令

Mac/Linux/Windows+Cygwin：

```bash
cd Sudoku/demo/${for-lang}
make # 编译代码
make run # 执行Demo
```

其中，\${for-lang}代表具体语言的 Demo 目录

## 高级语言访问 C 动态库

1. C# 访问 C 动态库只有一种方式，动过 DllImport 方式将 C#类静态方法与库导出方法对应起来，优雅高效
2. Go 语言的 cgo 采用了一种类似在 Go 源码文件嵌入 C 代码的方式
3. Java 通过编写 jni 胶水库，实现数据类型转换和函数调用
4. Lua 本身就是一门嵌入式语言，将动态库设计成 Lua 的 C 模块本身就是 Lua 的设计之一
5. NodeJS 有两种不同的方式调用 C 动态库，一种是将动态库设计成 Node 模块，另一种是通过 ffi 做动态调用
6. PHP 类似 NodeJS，有两种方式，一是将动态库设计成 PHP 扩展模块，二是使用 ffi 做动态调用
7. Python 类似 NodeJS，两种方式分别是将动态库设计成 Python 模块和通过 ctypes 做动态调用

## 相关内容记录

1. Windows 下的 `fopen` 函数只能打开 windows 格式的路径名，即使是在 cygwin 环境下运行，因此在 Makefile 中，需要使用重定向标准输入的方式输入数据，或者针对 cygwin 环境下调用 `cygpath` 命令进行转换
2. Windows 下的 Visual Studio 没有 `alloca` 函数，但是 `malloc.h` 头文件中有类似的 `_alloca` 函数，在这 JNI 和 Lua 模块中，为了方便，Windows 中统一用 `malloc` 代替 `alloca`
3. 64 位系统中 C 语言中的枚举类型 `enum` 变量占用 4 个字节，类似 `int`，`stdbool.h` 中的 `bool` 类型占用 1 个字节，类似 `char`
4. C#的 for-cs.csproj 工程文件中不可以指定 `TargetFrameworkVersion`，否则有些不存在该指定版本的环境下就会编译失败，反正 Demo 只用到很少的功能，采用环境默认的 Runtime 版本就好
5. 在 Linux/Windows 中，除了要引用\${JAVA_HOME}环境变量下的 include 目录，还要引用 include 下面的 linux/win32 目录，不然会有一些头文件找不到
6. Java 的 Demo 在 Windows+Cygwin 下编译失败，错误：未知的类型名‘\_\_int64’，通过 CMakeLists.txt 配置在 Visual Studio 下编译才能成功，并且这样做之后，在 Windows 下正常跑该 demo
7. Makefile 中采用 Shell 类型的=号赋值会存在循环引用的问题，改成:=赋值则可避免该问题
8. CMakeLists.txt 配置文件中，可以通过\$ENV{HOME}的方式访问进程环境变量
9. `bash -n script.sh` 可检查脚本语法但是不执行，`bash -x script.sh` 可以让脚本在执行命令前打印出该命令，包括变量的解引用结果
10. 回车 carriage return, 缩写 CR，对应 ASCII 码为 0x0D，字符表示为'\r'；换行 line feed（或 new line），缩写 LF（或 NL），对应 ASCII 码为 0x0A，字符表示为'\n'；Windows 下默认行结束符为回车换行，也就是 CRLF（或 CRNL）、'\r\n'、0x0D0A，因此 Cygwin 执行 shell 脚本就会报错找不到'\r'命令，三种解决方式：
    - 手动将 shell 脚本行结束符改成 Unix 版，如 `dos2unix` 工具
    - 在脚本开头处加上命令：`(set -o igncr) 2>/dev/null && set -o igncr; #` 注意，命令最后一个'#'注释符号是必要的，否则会报一次找不到'\r'命令，我猜是因为逐行读取命令导致，因此加上最后一个注释符来避免这一行的'\r'被执行，后续其他行的'\r'则由该命令指定来忽略
    - 使用如下命令执行脚本：`bash -o igncr script.sh`
11. 针对 NodeJS、PHP、Python 这三个支持 FFI 操作调用动态库的语言，经过 FFI 的包装之后，往动态库传递的函数指针并非静态变量，也就是说该指针仅在此次函数调用过程生效，C 端记录该指针供后续使用则会引发奇怪的错误。FFI 功能虽然方便，但存在局限性，具体原因与 FFI 内部实现有关，Java 通过 JNI 往 C 传递对象也同样存在这个问题。（如：NodeJS 示例的 main.js 脚本中，多次调用动态库的 `SolveTypeName` 函数会引发 Segmentation fault: 11 报错，Python 示例通过 CreateSudoku 注册的 WritteData 回调函数，在 CalculateAll 计算过程回调该函数时，会引发 Python Crash）

## 未解决问题

1. Go 语言工具用起来是比较舒服的，只是在 Windows 下用 cgo 编译会报错，错误为\_beginthread 函数未声明，目前尚未解决
2. cgo 中有些往 C 传递结构体指针需要先引用第一个字段再取地址，不明白为什么这样做就可以，如 `CreateSudoku` 函数
3. Windows+Cygwin 下 for-nodejs 目录下执行 `npm install ref` 命令失败，目前尚未解决
4. Ubuntu 环境下，安装 curl4-dev 会要求删除 ssl1.0-dev，然而 npm 等 node 工具需要 ssl1.0-dev 这个依赖，另外 phpize 工具也与 npm 有冲突，目前尚未解决！
