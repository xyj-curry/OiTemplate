ll t[MAXNODE], lazy[MAXNODE];
int ls[MAXNODE], rs[MAXNODE], nodesz = 0;
int newnode(int x) {
    nodesz++;
    t[nodesz] = x;
    lazy[nodesz] = -1;
    ls[nodesz] = rs[nodesz] = 0;
    return nodesz;
}
void build() {
    nodesz = 0;
    newnode(0);
}
void pushdown(int k, int l, int mid, int r) {
    if (ls[k] == 0) {
        ls[k] = newnode();
    }
    if (rs[k] == 0) {
        rs[k] = newnode();
    }
    if (lazy[k] == -1) {
        return;
    }
    t[ls[k]] = (t[ls[k]] + (mid - l + 1) * lazy[k]) % mod;
    lazy[ls[k]] = ((lazy[ls[k]] == -1 ? 0 : lazy[ls[k]]) + lazy[k]) % mod;

    t[rs[k]] = (t[rs[k]] + (r - mid) * lazy[k]) % mod;
    lazy[rs[k]] = ((lazy[rs[k]] == -1 ? 0 : lazy[rs[k]]) + lazy[k]) % mod;

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
        modify(ls[k], l, mid, ql, qr, qk);
    }
    if (qr > mid && ql <= r) {
        modify(rs[k], mid + 1, r, ql, qr, qk);
    }
    t[k] = (t[ls[k]] + t[rs[k]]) % mod;
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
        modify1(ls[k], l, mid, qx, qk);
    } else {
        modify1(rs[k], mid + 1, r, qx, qk);
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
        return query(ls[k], l, mid, ql, qr);
    }
    if (ql > mid) {
        return query(rs[k], mid + 1, r, ql, qr);
    }
    return (query(ls[k], l, mid, ql, qr) + query(rs[k], mid + 1, r, ql, qr)) % mod;
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
    int temp = findright(ls[k], l, mid, ql, qr, qk, s);
    if (temp != -1) {
        return temp;
    }
    return findright(rs[k], mid + 1, r, ql, qr, qk, s);
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
    int temp = findleft(rs[k], mid + 1, r, ql, qr, qk, s);
    if (temp != -1) {
        return temp;
    }
    return findleft(ls[k], l, mid, ql, qr, qk, s);
}