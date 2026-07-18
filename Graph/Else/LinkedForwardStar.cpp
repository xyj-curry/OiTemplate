int to[MAXM], ne[MAXM], tot = 1, he[MAXN];
int w[MAXM];
void add(int u, int v, int ww) {
    to[++tot] = v;
    w[tot] = ww;
    ne[tot] = he[u];
    he[u] = tot;
}