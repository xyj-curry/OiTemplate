ll lagrange_interpolation(int n, ll x[], ll y[], ll k) {
    ll ret = 0, p, q;
    for (int i = 1; i <= n; i++) {
        p = q = 1;
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                p = p * (k - x[j]) % mod;
                q = q * (x[i] - x[j]) % mod;
            }
        }
        ret = (ret + (p * qpow(q, mod - 2) % mod) * y[i] % mod + mod) % mod;
    }
    return ret;
}

ll sur[MAXN];
ll lagrange_interpolation_equi(int n, ll y[], ll k) {
    sur[n + 1] = 1;
    for (int i = n; i >= 1; i--) {
        sur[i] = sur[i + 1] * (k - i) % mod;
    }
    ll ret = 0, p = 1, q;
    for (int i = 1; i <= n; i++) {
        q = ((n - i) % 2 == 0 ? 1 : -1) * ifact[i - 1] * ifact[n - i] % mod;
        ret = (ret + ((p * sur[i + 1] % mod) * q % mod) * y[i] % mod + mod) % mod;
        p = p * (k - i) % mod;
    }
    return ret;
}

ll g[MAXN];
void lagrange_interpolation_coef(int n, ll x[], ll y[], ll f[]) {
    g[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= 0; j--) {
            g[j] = ((j == 0 ? 0 : g[j - 1]) - x[i] * g[j]) % mod;
        }
    }
    ll temp, lst;
    for (int i = 1; i <= n; i++) {
        temp = 1;
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                temp = temp * (x[i] - x[j]) % mod;
            }
        }
        temp = qpow(temp, mod - 2) * y[i] % mod;
        lst = 0;
        for (int j = n - 1; j >= 0; j--) {
            lst = (g[j + 1] + lst * x[i]) % mod;
            f[j] = (f[j] + lst * temp % mod + mod) % mod;
        }
    }
}