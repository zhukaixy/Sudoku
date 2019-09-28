# PHP 的 C 语言扩展

1. 本示例仅在 Linux 平台下跑通（其他平台也类似，可能有些参数不一样）
2. PHP 本身有一套创建 C 扩展的操作流程，通过脚本 ext_skel 创建基本结构
3. 修改 config.m4 并编写接口层胶水代码（解注释一些 dnf 定义来创建动态加载库）
4. 编写胶水代码，并执行编译命令（phpize、./configure、make、make test、sudo make install）
5. 修改 php.ini 配置（extension="phpsudoku.so"）
6. 编写调用 C 扩展的 PHP 代码

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

```
