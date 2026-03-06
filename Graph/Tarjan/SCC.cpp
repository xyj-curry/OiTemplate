vector<int> G[MAXN];
stack<int> s;
int dfn[MAXN], low[MAXN], tot = 0;
int scc[MAXN], scctot = 0;
void dfs(int u) {
    s.push(u);
    low[u] = dfn[u] = ++tot;
    for (int v : G[u]) {
        if (!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (!scc[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        scctot++;
        while (s.top() != u) {
            scc[s.top()] = scctot;
            s.pop();
        }
        scc[s.top()] = scctot;
        s.pop();
    }
}
for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
        dfs(i);
        if (!s.empty()) {
            scctot++;
            while (s.top() != i) {
                scc[s.top()] = scctot;
                s.pop();
            }
            scc[s.top()] = scctot;
            s.pop();
        }
    }
}