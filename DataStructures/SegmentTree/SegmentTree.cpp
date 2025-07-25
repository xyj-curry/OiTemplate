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
        t[k] = a[l];
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
void modify1(int k, int l, int r, int qx, ll qk) {
    assert(qx >= l && qx <= r);
    if (l == r) {
        t[k] = (t[k] + qk) % mod;
        return;
    }
    int mid = (l + r) / 2;
    pushdown(k, l, mid, r);
    if (qx <= mid) {
        modify1(k * 2, l, mid, qx, qk);
    } else {
        modify1(k * 2 + 1, mid + 1, r, qx, qk);
    }
    t[k] = (t[k * 2] + t[k * 2 + 1]) % mod;
}
ll query(int k, int l, int r, int ql, int qr) {
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
int findright(int k, int l, int r, int ql, int qr, int qk, int& s) {
    assert(ql <= qr);
    if (r < ql || l > qr) {
        return -1;
    }
    if (l >= ql) {
        int ss = (s + t[k]) % mod;
        if (ss < qk) {
            s = ss;
            return -1;
        }
        if (l == r) {
            return l;
        }
    }
    int mid = (l + r) / 2;
    pushdown(k, l, mid, r);
    int temp = findright(k * 2, l, mid, ql, qr, qk, s);
    if (temp != -1) {
        return temp;
    }
    return findright(k * 2 + 1, mid + 1, r, ql, qr, qk, s);
}
int findleft(int k, int l, int r, int ql, int qr, int qk, int& s) {
    assert(ql <= qr);
    if (r < ql || l > qr) {
        return -1;
    }
    if (r <= qr) {
        int ss = (s + t[k]) % mod;
        if (ss < qk) {
            s = ss;
            return -1;
        }
        if (l == r) {
            return l;
        }
    }
    int mid = (l + r) / 2;
    pushdown(k, l, mid, r);
    int temp = findleft(k * 2 + 1, mid + 1, r, ql, qr, qk, s);
    if (temp != -1) {
        return temp;
    }
    return findleft(k * 2, l, mid, ql, qr, qk, s);
}