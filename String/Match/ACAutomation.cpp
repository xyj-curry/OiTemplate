int ans[MAXN];
int son[MAXN][26], fail[MAXN], cnt[MAXN], tot = 0;
void insert(string s, int id) {
    int n = s.length();
    int now = 0;
    for (int i = 0; i < n; i++) {
        if (son[now][s[i] - 'a'] == 0) {
            son[now][s[i] - 'a'] = ++tot;
        }
        now = son[now][s[i] - 'a'];
    }
}
queue<int> q;
void setfail() {
    for (int i = 0; i < 26; i++) {
        if (son[0][i] != 0) {
            fail[son[0][i]] = 0;
            q.push(son[0][i]);
        }
    }
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (son[now][i]) {
                fail[son[now][i]] = son[fail[now]][i];
                q.push(son[now][i]);
            } else {
                son[now][i] = son[fail[now]][i];
            }
        }
    }
}
void query(string s) {
    int n = s.length();
    int now = 0;
    for (int i = 0; i < n; i++) {
        now = son[now][s[i] - 'a'];
        ans[now]++;
    }
}
int du[MAXN];
void topu() {
    for (int i = 1; i <= tot; i++) {
        du[fail[i]]++;
    }
    for (int i = 1; i <= tot; i++) {
        if (du[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        ans[fail[now]] += ans[now];
        du[fail[now]]--;
        if (du[fail[now]] == 0) {
            q.push(fail[now]);
        }
    }
}