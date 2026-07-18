// tot = 1, MAXM * 2
ll maxflow = 0;
queue<int> q;
int d[MAXN], cur[MAXN];
bool bfs() {
    for (int i = 1; i <= n; i++) {
        d[i] = -1;
        cur[i] = he[i];
    }
    q.push(s);
    d[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = he[u]; i != 0; i = ne[i]) {
            int v = to[i];
            if (d[v] != -1 || c[i] == 0) {
                continue;
            }
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
    return d[t] != -1;
}
ll dfs(int u, ll lim) {
    if (u == t) {
        return lim;
    }
    ll flow = 0;
    for (int i = cur[u]; i != 0; i = ne[i]) {
        cur[u] = i;
        int v = to[i];
        if (c[i] == 0 || d[v] != d[u] + 1) {
            continue;
        }
        ll used = dfs(v, min(lim - flow, c[i]));
        c[i] -= used;
        c[i ^ 1] += used;
        flow += used;
        if (flow == lim) {
            break;
        }
    }
    return flow;
}
ll Dinic() {
    maxflow = 0;
    while (bfs()) {
        maxflow += dfs(s, 1e18);
    }
    return maxflow;
}