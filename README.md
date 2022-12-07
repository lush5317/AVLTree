# build

1. Use `clang` or other CXX compiler, `gcc` or something (**if you don't have clang in your path, you need to revise the `makefile`**).

```bash
  make all
```

    Also, you can use`make clean` to delete the `*.o`.

2. If you don't have `make`, you can compile mannully.

```bash
  $cc main.c avl.c -o main -lm
```
