queue<int> q;
int dis[MAXN], cnt[MAXN];
bool book[MAXN];
bool SPFA(int s) {
    for (int i = 1; i <= n; i++) {
        dis[i] = 1e9;
        cnt[i] = 0;
        book[i] = false;
    }
    while (!q.empty()) {
        q.pop();
    }
    dis[s] = 0;
    cnt[s] = 1;
    book[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        book[u] = false;
        for (auto v : G[u]) {
            if (dis[v.first] > dis[u] + v.second) {
                dis[v.first] = dis[u] + v.second;
                if (!book[v.first]) {
                    cnt[v.first] = cnt[u] + 1;
                    if (cnt[v.first] > n) {
                        return false;
                    }
                    q.push(v.first);
                }
            }
        }
    }
    return true;
}