const int MAXNODE = MAXN * 30;
int t[MAXNODE][2], w[MAXNODE], ed[MAXNODE], tot = 0;
ll xorv[MAXNODE];
void pushup(int k) {
    w[k] = xorv[k] = 0;
    if (t[k][0] != 0) {
        w[k] += w[t[k][0]];
        xorv[k] ^= (xorv[t[k][0]] << 1);
    }
    if (t[k][1] != 0) {
        w[k] += w[t[k][1]];
        xorv[k] ^= (xorv[t[k][1]] << 1);
        xorv[k] ^= (w[t[k][1]] & 1);
    }
    w[k] += ed[k];
}
void ins(int k, int x) {
    if (x == 0) {
        w[k]++;
        ed[k]++;
        return;
    }
    if (t[k][x & 1] == 0) {
        t[k][x & 1] = ++tot;
    }
    ins(t[k][x & 1], x >> 1);
    pushup(k);
}
void del(int k, int x) {
    if (x == 0) {
        assert(w[k] > 0 && ed[k] > 0);
        w[k]--;
        ed[k]--;
        return;
    }
    if (t[k][x & 1] == 0) {
        t[k][x & 1] = ++tot;
    }
    assert(t[k][x & 1] != 0);
    del(t[k][x & 1], x >> 1);
    pushup(k);
}
void addall(int k) {
    swap(t[k][0], t[k][1]);
    if (ed[k] != 0) {
        if (t[k][1] == 0) {
            t[k][1] = ++tot;
        }
        w[t[k][1]] += ed[k];
        ed[t[k][1]] += ed[k];
        ed[k] = 0;
    }
    if (t[k][0] != 0) {
        addall(t[k][0]);
    }
    pushup(k);
}
// merge
// split
