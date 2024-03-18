```
meson setup build
meson compile -C build
```

## `cp`

```
./build/cp/cp cp/file.txt cp/test.txt
diff cp/file.txt cp/test.txt
```

`lurk ./build/cp/cp cp/file.txt cp/test.txt`

```c
[172589] execve("", "", "") = 0
[172589] brk(0x0) = 0x555555559000
[172589] access("/etc/ld.so.preload", 4) = -2
[172589] openat(4294967196, "/etc/ld.so.cache", 524288) = 3
[172589] fstat(3, 0x7FFFFFFFD100) = 0
[172589] mmap(0x0, 170195, 1, 2, 3, 0) = 0x7FFFF7F98000
[172589] close(3) = 0
[172589] openat(4294967196, "/usr/lib/libc.so.6", 524288) = 3
[172589] read(3, "ELF\u0002\u0001\u0001\u0003", 832) = 832
[172589] pread64(3, "\u0006", 784, 64) = 784
[172589] fstat(3, 0x7FFFFFFFD100) = 0
[172589] mmap(0x0, 8192, 3, 34, 4294967295, 0) = 0x7FFFF7F96000
[172589] pread64(3, "\u0006", 784, 64) = 784
[172589] mmap(0x0, 1973104, 1, 2050, 3, 0) = 0x7FFFF7DB4000
[172589] mmap(0x7FFFF7DD8000, 1421312, 5, 2066, 3, 147456) = 0x7FFFF7DD8000
[172589] mmap(0x7FFFF7F33000, 348160, 1, 2066, 3, 1568768) = 0x7FFFF7F33000
[172589] mmap(0x7FFFF7F88000, 24576, 3, 2066, 3, 1912832) = 0x7FFFF7F88000
[172589] mmap(0x7FFFF7F8E000, 31600, 3, 50, 4294967295, 0) = 0x7FFFF7F8E000
[172589] close(3) = 0
[172589] mmap(0x0, 12288, 3, 34, 4294967295, 0) = 0x7FFFF7DB1000
[172589] arch_prctl(4098, 0x7FFFF7DB1740) = 0
[172589] set_tid_address(0x7FFFF7DB1A10) = 0x2A22D
[172589] set_robust_list(0x7FFFF7DB1A20, 24) = 0
[172589] rseq() = 0
[172589] mprotect(0x7FFFF7F88000, 16384, 1) = 0
[172589] mprotect(0x555555557000, 4096, 1) = 0
[172589] mprotect(0x7FFFF7FFB000, 8192, 1) = 0
[172589] prlimit64(0, 3, 0x0, 0x7FFFFFFFDC40) = 0
[172589] munmap(0x7FFFF7F98000, 170195) = 0
[172589] getrandom("y0\u0019\u0018R=K", 8, 1) = 8
[172589] brk(0x0) = 0x555555559000
[172589] brk(0x55555557A000) = 0x55555557A000
[172589] openat(4294967196, "cp/file.txt", 0) = 3
[172589] openat(4294967196, "cp/test.txt", 578) = 4
[172589] fstat(3, 0x7FFFFFFFDC70) = 0
[172589] fstat(3, 0x7FFFFFFFDD60) = 0
[172589] lseek(3, 0, 0) = 0
[172589] read(3, "jykuo\n", 6) = 6
[172589] lseek(3, 6, 0) = 6
[172589] fstat(4, 0x7FFFFFFFDD20) = 0
[172589] close(3) = 0
[172589] write(4, "jykuo\n", 6) = 6
[172589] close(4) = 0
[172589] exit_group(0) = ?
```

## `time`

```bash
./build/time/time_shm ls
# build  builddir  cp  meson.build  README.md  time
# 1477us

./build/time/time_pipe ls
# build  builddir  cp  meson.build  README.md  time
# 1409us
```

