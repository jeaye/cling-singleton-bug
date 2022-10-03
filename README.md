# Cling singleton bug
This appears to be a bug related to static globals and an odd combination of
`unique_ptr<T>` and `T*` fields. The result is that non-JIT code sees one value
for the `T*` field, while JIT code sees another. All other fields show the same
value.

## Building and running
```bash
$ mkdir build ; cd build
$ cmake .. -DCling_DIR=/path/to/cling-build/builddir
$ make
$ ./cling-demo
before: 0
cling: (int *) 0x1 <invalid memory address>
after: 0
```

As shown in the output above, this demo outputs the same value from non-JIT code
and JIT code. It doesn't match up. However, if the `unique_ptr` field before the
`T*` field is a `T*` or even a `shared_ptr<T>`, this issue doesn't manifest.

## Environment
I have reproduced this in the following configurations:

* Arch Linux, GCC 12.2.0, Cling stable debug build (from cpt)
* Arch Linux, Clang 14.0.6, Cling stable debug build (from cpt)
* Arch Linux, Clang 14.0.6, Cling llvm-13 debug build (from cpt)
* Ubuntu 22.04, Clang 14, Cling stable release build (from cpt)

Curiously, I have not been able to reproduce it on:

* macOS 12, AppleClang 12, Cling stable release build (from cpt)

## Bug
I suspect that this is a bug, since I do not believe this to be UB and I haven't
seen any Cling documentation stating this should not work. Also, the oddities
around `unique_ptr` are perplexing.
