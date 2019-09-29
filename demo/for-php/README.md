# PHP 的 C 语言扩展

1. 本示例仅在 Linux 平台下跑通（其他平台也类似，可能有些参数不一样）
2. 参考资料：《PHP 内核剖析》一书第 10 章

## 创建 C 扩展的基本流程

1. 下载对应版本的 PHP 源码
2. 通过 ext 目录下 `ext_skel` 脚本生成扩展的基本框架
3. 修改 config.m4 编译配置：设置编译配置参数、设置扩展的源文件、依赖库/函数检查等
4. 编写胶水代码：按照 PHP 扩展的格式，应用 PHP 提供的 API
5. 生成 configure：执行 `phpize` 命令
6. 执行编译命令： `./configure`、`make`、`make test`、`sudo make install`
7. 修改 php.ini 配置（extension="phpsudoku.so"），包括 `php` 命令的 `php.ini` 和 `php-fpm` 的 `php.ini`
8. 编写调用 C 扩展的 PHP 代码

## 创建 C 扩展的命令行操作

```bash
$ git clone https://github.com/php/php-src.git
$ cd php-src
$ php --version
$ git branch -a
$ git checkout PHP-7.1.30
$ cd ext
$ ./ext_skel --extname=phpsudoku
Creating directory phpsudoku
Creating basic files: config.m4 config.w32 .gitignore phpsudoku.c php_phpsudoku.h CREDITS EXPERIMENTAL tests/001.phpt phpsudoku.php [done].

To use your new extension, you will have to execute the following steps:

1.  $ cd ..
2.  $ vi ext/phpsudoku/config.m4
3.  $ ./buildconf
4.  $ ./configure --[with|enable]-phpsudoku
5.  $ make
6.  $ ./sapi/cli/php -f ext/phpsudoku/phpsudoku.php
7.  $ vi ext/phpsudoku/phpsudoku.c
8.  $ make

Repeat steps 3-6 until you are satisfied with ext/phpsudoku/config.m4 and
step 6 confirms that your module is compiled into PHP. Then, start writing
code and repeat the last two steps as often as necessary.
$ phpize
$ ./configure
$ make
$ make test
$ sudo make install
```

## 问题记录

1. C 扩展模块回调 PHP 层采用了调用 PHP 全局函数的形式，目前尚不知道如何调用 PHP 传递过来的闭包！（后续整改更新）
2. 目前仅实现了布尔矩阵的引用，Sudoku 相关函数待实现
