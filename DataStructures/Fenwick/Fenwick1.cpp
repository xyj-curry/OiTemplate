int t[MAXN];
void modify(int i, int x) {
    for (; i <= n; i += (i & (-i))) {
        t[i] += x;
    }
}
int query(int i) {
    int ret = 0;
    for (; i > 0; i -= (i & (-i))) {
        ret += t[i];
    }
    return ret;
}
int rangequery(int l, int r) {
    return query(r) - query(l - 1);
}
int lower_bound(int x) {
    int ret = 0;
    for (int i = __lg(n); i >= 0; i--) {
        if (ret + (1 << i) <= n && t[ret + (1 << i)] < x) {
            x -= t[ret + (1 << i)];
            ret += (1 << i);
        }
    }
    return ret + 1;
}
int upper_bound(int x) {
    int ret = 0;
    for (int i = __lg(n); i >= 0; i--) {
        if (ret + (1 << i) <= n && t[ret + (1 << i)] <= x) {
            x -= t[ret + (1 << i)];
            ret += (1 << i);
        }
    }
    return ret + 1;
}