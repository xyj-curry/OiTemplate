int lg2[MAXN], st[20][MAXN];
void initlg2() {
    lg2[0] = -1;
    for (int i = 1; i <= n; i++) {
        lg2[i] = lg2[i >> 1] + 1;
    }
}
void init() {
    for (int i = 1; i <= n; i++) {
        st[0][i] = a[i];
    }
    for (int i = 1; i <= lg2[n]; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
}
int query(int l, int r) {
    int k = lg2[r - l + 1];
    return max(st[k][l], st[k][r - (1 << k) + 1]);
}