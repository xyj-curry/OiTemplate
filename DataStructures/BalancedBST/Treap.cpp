mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int key[MAXN];
int hgt[MAXN], cnt[MAXN], sz[MAXN], lson[MAXN], rson[MAXN], rt = 0, nodesz = 0;
void updata(int k) {
    sz[k] = sz[lson[k]] + sz[rson[k]] + cnt[k];
}
int newnode(int qk) {
    key[++nodesz] = qk;
    hgt[nodesz] = rng();
    cnt[nodesz] = sz[nodesz] = 1;
    lson[nodesz] = rson[nodesz] = 0;
    return nodesz;
}
int lrotate(int k) {
    int ret = rson[k];
    rson[k] = lson[ret];
    lson[ret] = k;
    updata(k);
    updata(ret);
    return ret;
}
int rrotate(int k) {
    int ret = lson[k];
    lson[k] = rson[ret];
    rson[ret] = k;
    updata(k);
    updata(ret);
    return ret;
}
int ins(int k, int qk) {
    if (k == 0) {
        return newnode(qk);
    }
    if (qk < key[k]) {
        lson[k] = ins(lson[k], qk);
        if (lson[k] != 0 && hgt[lson[k]] > hgt[k]) {
            k = rrotate(k);
        }
    } else if (qk > key[k]) {
        rson[k] = ins(rson[k], qk);
        if (rson[k] != 0 && hgt[rson[k]] > hgt[k]) {
            k = lrotate(k);
        }
    } else {
        cnt[k]++;
    }
    updata(k);
    return k;
}
int del(int k, int qk) {
    if (k == 0) {
        return 0;
    }
    if (qk < key[k]) {
        lson[k] = del(lson[k], qk);
        if (lson[k] != 0 && hgt[lson[k]] > hgt[k]) {
            k = rrotate(k);
        }
    } else if (qk > key[k]) {
        rson[k] = del(rson[k], qk);
        if (rson[k] != 0 && hgt[rson[k]] > hgt[k]) {
            k = lrotate(k);
        }
    } else {
        if (cnt[k] > 1) {
            cnt[k]--;
        } else {
            if (lson[k] != 0 || rson[k] != 0) {
                if (rson[k] == 0 || (lson[k] != 0 && hgt[lson[k]] < hgt[rson[k]])) {
                    k = rrotate(k);
                    rson[k] = del(rson[k], qk);
                } else {
                    k = lrotate(k);
                    lson[k] = del(lson[k], qk);
                }
            } else {
                cnt[k] = sz[k] = 0;
                return 0;
            }
        }
    }
    updata(k);
    return k;
}
int getrank(int k, int qk) {
    if (k == 0) {
        return 1;
    }
    if (qk < key[k]) {
        return getrank(lson[k], qk);
    } else if (qk > key[k]) {
        return sz[lson[k]] + cnt[k] + getrank(rson[k], qk);
    }
    return sz[lson[k]] + 1;
}
int getval(int k, int qk) {
    if (k == 0) {
        return -1;
    }
    if (qk <= sz[lson[k]]) {
        return getval(lson[k], qk);
    } else if (qk > sz[lson[k]] + cnt[k]) {
        return getval(rson[k], qk - sz[lson[k]] - cnt[k]);
    }
    return key[k];
}
int getpre(int k, int qk) {
    int ans = -1;
    while (k != 0) {
        if (key[k] < qk && (ans == -1 || key[k] > ans)) {
            ans = key[k];
        }
        if (qk < key[k]) {
            k = lson[k];
        } else if (qk > key[k]) {
            k = rson[k];
        } else {
            if (lson[k] != 0) {
                k = lson[k];
                while (rson[k] != 0) {
                    k = rson[k];
                }
                ans = key[k];
            }
            break;
        }
    }
    return ans;
}
int getnext(int k, int qk) {
    int ans = -1;
    while (k != 0) {
        if (key[k] > qk && (ans == -1 || key[k] < ans)) {
            ans = key[k];
        }
        if (qk < key[k]) {
            k = lson[k];
        } else if (qk > key[k]) {
            k = rson[k];
        } else {
            if (rson[k] != 0) {
                k = rson[k];
                while (lson[k] != 0) {
                    k = lson[k];
                }
                ans = key[k];
            }
            break;
        }
    }
    return ans;
}