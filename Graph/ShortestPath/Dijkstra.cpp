int dis[MAXN];
bool flag[MAXN];
priority_queue<pair<int, int> > q;
void dijkstra(int s) {
    for (int i = 1; i <= n; i++) {
        dis[i] = 1e9;
        flag[i] = false;
    }
    while (!q.empty()) {
        q.pop();
    }
    dis[s] = 0;
    q.emplace(-dis[s], s);
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (flag[u]) {
            continue;
        }
        flag[u] = true;
        for (auto v : G[u]) {
            if (dis[v.first] > dis[u] + v.second) {
                dis[v.first] = dis[u] + v.second;
                q.emplace(-dis[v.first], v.first);
            }
        }
    }
}