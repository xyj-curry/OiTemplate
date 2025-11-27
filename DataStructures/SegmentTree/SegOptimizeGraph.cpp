vector<pair<int, int> > G[MAXN * 8];
int tot = 0;
int ls[MAXN * 8], rs[MAXN * 8];
int lf[2][MAXN];
int newnode() {
    tot++;
    return tot;
}
int build(int l, int r, int id) {
    if (l == r) {
        int nd = newnode();
        lf[id][l] = nd;
        return nd;
    }
    int mid = (l + r) / 2;
    int nd = newnode();
    ls[nd] = build(l, mid, id);
    rs[nd] = build(mid + 1, r, id);
    if (id == 0) {
        G[nd].push_back({ls[nd], 0});
        G[nd].push_back({rs[nd], 0});
    } else {
        G[ls[nd]].push_back({nd, 0});
        G[rs[nd]].push_back({nd, 0});
    }
    return nd;
}
void link(int k, int l, int r, int ql, int qr, int qk, int qw, bool dir) {
    if (l >= ql && r <= qr) {
        if (dir) {
            G[qk].push_back({k, qw});
        } else {
            G[k].push_back({qk, qw});
        }
        return;
    }
    int mid = (l + r) / 2;
    if (qr >= l && ql <= mid) {
        link(ls[k], l, mid, ql, qr, qk, qw, dir);
    }
    if (qr > mid && ql <= r) {
        link(rs[k], mid + 1, r, ql, qr, qk, qw, dir);
    }
}
int rt0 = build(1, n, 0);
int rt1 = build(1, n, 1);
for (int i = 1; i <= n; i++) {
    G[lf[0][i]].push_back({lf[1][i], 0});
    G[lf[1][i]].push_back({lf[0][i], 0});
}