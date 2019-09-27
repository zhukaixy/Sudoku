# Python 调用 C 语言动态库

Python 有两种方式来实现调用 C 语言动态库：

1. 编写[C 模块](https://docs.python.org/3/extending/extending.html)来扩展 Python
2. 通过[ctype 模块](https://docs.python.org/3/library/ctypes.html)直接在 Python 层调用动态库函数

第一种方式很强大，可以随意 DIY，运行效率高，不过仅支持 CPython 实现，不支持其他实现；第二种方式则简单方便，同时支持多种 Python 实现，就是效率略低，这里采用第二种
