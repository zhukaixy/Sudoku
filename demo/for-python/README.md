# Python 调用 C 语言动态库

Python 有两种方式来实现调用 C 语言动态库：

1. 编写[C 模块](https://docs.python.org/3/extending/extending.html)来扩展 Python
2. 通过[ctypes 模块](https://docs.python.org/3/library/ctypes.html)直接在 Python 层调用动态库函数

第一种方式很强大，可以随意 DIY，运行效率高，不过仅支持 CPython 实现，不支持其他实现；第二种方式则简单方便，同时支持多种 Python 实现，就是效率略低。

由于 ctypes 模块的方式无法传递持久性回调函数，因此这里采用第二种仅是实现布尔矩阵的调用
