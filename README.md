```
meson setup build
meson compile -C build
```

## `cp`

```
./build/cp/cp cp/file.txt cp/test.txt
diff cp/file.txt cp/test.txt
```
