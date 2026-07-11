const int MAXN = 3e5 + 5;
int n, m = 127;
int sa[MAXN], rk[MAXN * 2], oldsa[MAXN], oldrk[MAXN * 2], cnt[MAXN], height[MAXN];
void initSA_2log(string s) {
    for (int i = 1; i <= n; i++) {
        sa[i] = i;
        rk[i] = s[i];
    }
    for (int w = 1; w < n; w <<= 1) {
        sort(sa + 1, sa + 1 + n, [&](int x, int y) {
            if (rk[x] != rk[y]) {
                return rk[x] < rk[y];
            }
            return rk[x + w] < rk[y + w];
        });
        for (int i = 1; i <= n; i++) {
            oldrk[i] = rk[i];
        }
        int p = 0;
        for (int i = 1; i <= n; i++) {
            if ((i == 1) || (oldrk[sa[i]] != oldrk[sa[i - 1]]) ||
                (oldrk[sa[i] + w] != oldrk[sa[i - 1] + w])) {
                p++;
            }
            rk[sa[i]] = p;
        }
        if (p == n) {
            break;
        }
    }
}

void initSA(string s) {
    for (int i = 1; i <= n; i++) {
        rk[i] = s[i];
        cnt[rk[i]]++;
    }
    for (int i = 1; i <= m; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n; i >= 1; i--) {
        sa[cnt[rk[i]]--] = i;
    }

    for (int w = 1; w < n; w <<= 1) {
        int cur = 0;
        for (int i = n - w + 1; i <= n; i++) {
            oldsa[++cur] = i;
        }
        for (int i = 1; i <= n; i++) {
            if (sa[i] > w) {
                oldsa[++cur] = sa[i] - w;
            }
        }

        for (int i = 1; i <= m; i++) {
            cnt[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            cnt[rk[oldsa[i]]]++;
        }
        for (int i = 1; i <= m; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n; i >= 1; i--) {
            sa[cnt[rk[oldsa[i]]]--] = oldsa[i];
        }

        for (int i = 1; i <= n; i++) {
            oldrk[i] = rk[i];
        }
        int p = 0;
        for (int i = 1; i <= n; i++) {
            if ((i == 1) || (oldrk[sa[i]] != oldrk[sa[i - 1]]) ||
                (oldrk[sa[i] + w] != oldrk[sa[i - 1] + w])) {
                p++;
            }
            rk[sa[i]] = p;
        }
        m = p;
        if (m == n) {
            break;
        }
    }
}

void initHeight(string s) {
    int k = 0;
    for (int i = 1; i <= n; i++) {
        if (rk[i] == 1) {
            continue;
        }
        if (k != 0) {
            k--;
        }
        while ((i + k <= n && sa[rk[i] - 1] + k <= n) && (s[i + k] == s[sa[rk[i] - 1] + k])) {
            k++;
        }
        height[rk[i]] = k;
    }
}
