int fa[MAXN], sz[MAXN];
void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
}
int getf(int x) {
    if (x == fa[x]) {
        return x;
    }
    return fa[x] = getf(fa[x]);
}
void merge(int x, int y) {
    int fax = getf(x);
    int fay = getf(y);
    if (fax == fay) {
        return;
    }
    if (sz[fax] < sz[fay]) {
        swap(fax, fay);
    }
    fa[fay] = fax;
    sz[fax] += sz[fay];
}