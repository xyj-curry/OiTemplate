// tot = 1, MAXM*2
ll maxflow, incf[MAXN];
int pre[MAXN];
bool book[MAXN];
queue<int> q;

bool bfs() {
    for (int i = 1; i <= n; i++) {
        book[i] = false;
    }
    while (!q.empty()) {
        q.pop();
    }
    incf[s] = 1e18;
    q.push(s);
    book[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = he[u]; i != 0; i = ne[i]) {
            int v = to[i];
            if (book[v] || c[i] == 0) {
                continue;
            }
            incf[v] = min(incf[u], c[i]);
            book[v] = true;
            pre[v] = i;
            q.push(v);
            if (v == t) {
                return true;
            }
        }
    }
    return false;
}

void update() {
    int u = t;
    while (u != s) {
        c[pre[u]] -= incf[t];
        c[pre[u] ^ 1] += incf[t];
        u = to[pre[u] ^ 1];
    }
    maxflow += incf[t];
}

ll EK() {
    maxflow = 0;
    while (bfs()) {
        update();
    }
    return maxflow;
}