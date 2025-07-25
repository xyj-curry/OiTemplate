template <typename T = int>
inline T read() {
    T val = 0, sgn = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) {
        if (ch == '-') {
            sgn = -sgn;
        }
    }
    for (; ch >= '0' && ch <= '9'; ch = getchar()) {
        val = (val << 3) + (val << 1) + ch - '0';
    }
    return sgn * val;
}

template <typename T = int>
inline void write(T val) {
    static T stk[50];
    int top = 0;
    if (val < 0) {
        putchar('-');
        val = -val;
    }
    do {
        stk[top++] = val % 10;
        val /= 10;
    } while (val);
    while (top) {
        putchar(stk[--top] + '0');
    }
}