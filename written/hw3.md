## 7.8

Potential deadlocks can occur

## 8.20

(a) safe

(b) unsafe

(c) unsafe

(d) safe

(e) unsafe

(f) safe

## 8.27

(a)
safe, $P_4 \rightarrow P_0 \rightarrow P_3 \rightarrow P_1 \rightarrow P_2$

(b)
safe, $P_4 \rightarrow P_1 \rightarrow P_2 \rightarrow P_3 \rightarrow P_0$

## 8.30

```rs
let mutex: Mutex;

fn cross(from: Town) {
    lock(&mutex);

    // cross

    unlock(&mutex)
}
```

## 9.15

(a)
- contiguous: yes
- paging: no

(b)
- contiguous: yes
- paging: yes

(c)
- contiguous: hard
- paging: easy

## 9.24

(a)

$$
\frac{2^{32}}{2^{13}} = 2^{19}
$$

(b)

$$
\frac{2^{30}}{2^{13}} = 2^{17}
$$
