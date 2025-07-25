const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) ? EOF : *p1++)
#define fastflush() fwrite(pbuf, 1, pp - pbuf, stdout);
template <typename T = int>
inline T read() {
    T val = 0, sgn = 1;
    char ch = gc();
    for (; ch < '0' || ch > '9'; ch = gc()) {
        if (ch == '-') {
            sgn = -sgn;
        }
    }
    for (; ch >= '0' && ch <= '9'; ch = gc()) {
        val = (val << 3) + (val << 1) + ch - '0';
    }
    return sgn * val;
}
char pbuf[MAXSIZE], *pp = pbuf;
void push(const char& c) {
    if (pp - pbuf == MAXSIZE) {
        fwrite(pbuf, 1, MAXSIZE, stdout);
        pp = pbuf;
    }
    *pp++ = c;
}

template <typename T = int>
inline void write(T val) {
    static T stk[50];
    int top = 0;
    if (val < 0) {
        push('-');
        val = -val;
    }
    do {
        stk[top++] = val % 10;
        val /= 10;
    } while (val);
    while (top) {
        push(stk[--top] + '0');
    }
}