int book[MAXN];
int f[MAXN];
bool dfs(int u, int rt) {
    for (int v : G[u]) {
        if (book[v] == rt) {
            continue;
        }
        book[v] = rt;
        if (f[v] == 0 || dfs(f[v], rt)) {
            f[v] = u;
            return true;
        }
    }
    return false;
}
int hungarian() {
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        ret += dfs(i, i);
    }
    return ret;
}