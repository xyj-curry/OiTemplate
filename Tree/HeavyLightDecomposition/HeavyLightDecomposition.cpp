int dfn[MAXN], fa[MAXN], top[MAXN], sz[MAXN], dep[MAXN], bson[MAXN], tot = 0;
int wt[MAXN];
ll t[MAXN * 4], lazy[MAXN * 4];
void pushdown(int k, int l, int mid, int r) {
    if (lazy[k] == -1) {
        return;
    }
    t[k * 2] = (t[k * 2] + lazy[k] * (mid - l + 1)) % mod;
    lazy[k * 2] = ((lazy[k * 2] == -1 ? 0 : lazy[k * 2]) + lazy[k]) % mod;

    t[k * 2 + 1] = (t[k * 2 + 1] + lazy[k] * (r - mid)) % mod;
    lazy[k * 2 + 1] = ((lazy[k * 2 + 1] == -1 ? 0 : lazy[k * 2 + 1]) + lazy[k]) % mod;

    lazy[k] = -1;
}
void build(int k, int l, int r) {
    if (l == r) {
        t[k] = wt[l];
        lazy[k] = -1;
        return;
    }
    int mid = (l + r) / 2;
    build(k * 2, l, mid);
    build(k * 2 + 1, mid + 1, r);
    t[k] = (t[k * 2] + t[k * 2 + 1]) % mod;
    lazy[k] = -1;
}
void modify(int k, int l, int r, int ql, int qr, ll qk) {
    assert(ql <= qr);
    if (l >= ql && r <= qr) {
        t[k] = (t[k] + qk * (r - l + 1)) % mod;
        lazy[k] = ((lazy[k] == -1 ? 0 : lazy[k]) + qk) % mod;
        return;
    }
    int mid = (l + r) / 2;
    pushdown(k, l, mid, r);
    if (qr >= l && ql <= mid) {
        modify(k * 2, l, mid, ql, qr, qk);
    }
    if (qr > mid && ql <= r) {
        modify(k * 2 + 1, mid + 1, r, ql, qr, qk);
    }
    t[k] = (t[k * 2] + t[k * 2 + 1]) % mod;
}
int query(int k, int l, int r, int ql, int qr) {
    assert(ql <= qr);
    if (l >= ql && r <= qr) {
        return t[k];
    }
    int mid = (l + r) / 2;
    pushdown(k, l, mid, r);
    if (qr <= mid) {
        return query(k * 2, l, mid, ql, qr);
    }
    if (ql > mid) {
        return query(k * 2 + 1, mid + 1, r, ql, qr);
    }
    return (query(k * 2, l, mid, ql, qr) + query(k * 2 + 1, mid + 1, r, ql, qr)) % mod;
}
void dfs1(int u) {
    sz[u] = 1;
    dep[u] = dep[fa[u]] + 1;
    bson[u] = -1;
    for (int v : G[u]) {
        if (v == fa[u]) {
            continue;
        }
        fa[v] = u;
        dfs1(v);
        sz[u] += sz[v];
        if (bson[u] == -1 || sz[bson[u]] < sz[v]) {
            bson[u] = v;
        }
    }
}
void dfs2(int u) {
    dfn[u] = ++tot;
    wt[dfn[u]] = a[u] % mod;
    if (bson[u] == -1) {
        return;
    }
    top[bson[u]] = top[u];
    dfs2(bson[u]);
    for (int v : G[u]) {
        if (v == fa[u] || v == bson[u]) {
            continue;
        }
        top[v] = v;
        dfs2(v);
    }
}
void modify_chain(int u, int v, int qx) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        modify(1, 1, n, dfn[top[u]], dfn[u], qx);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    modify(1, 1, n, dfn[u], dfn[v], qx);
}
void modify_son(int u, int qx) {
    modify(1, 1, n, dfn[u], dfn[u] + sz[u] - 1, qx);
}
int query_chain(int u, int v) {
    int ans = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        ans = (ans + query(1, 1, n, dfn[top[u]], dfn[u])) % mod;
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    ans = (ans + query(1, 1, n, dfn[u], dfn[v])) % mod;
    return ans;
}
int query_son(int u) {
    return query(1, 1, n, dfn[u], dfn[u] + sz[u] - 1);
}
void buildt(int rt) {
    tot = dep[0] = 0;
    fa[rt] = 0;
    dfs1(rt);
    top[rt] = rt;
    dfs2(rt);
    build(1, 1, n);
}