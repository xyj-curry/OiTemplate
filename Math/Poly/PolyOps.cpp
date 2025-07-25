const int mod_g = 3;
const int invmod_g = (mod + 1) / mod_g;
ll qpow(ll a, ll b) {
    ll ret = 1;
    while (b) {
        if (b & 1) {
            ret = ret * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}
int binv[MAXN * 4];
void ntt(ll a[], int n, bool rev) {
    for (int i = 0; i < n; i++) {
        if (i < binv[i]) {
            swap(a[i], a[binv[i]]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll wn = qpow((rev ? invmod_g : mod_g), (mod - 1) / len);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = i; j < i + (len >> 1); j++, w = w * wn % mod) {
                ll tmp = w * a[j + (len >> 1)] % mod;
                a[j + (len >> 1)] = (a[j] - tmp + mod) % mod;
                a[j] = (a[j] + tmp) % mod;
            }
        }
    }
    if (rev) {
        ll invn = qpow(n, mod - 2);
        for (int i = 0; i < n; i++) {
            a[i] = a[i] * invn % mod;
        }
    }
}

// ll tempa[MAXN * 4], tempb[MAXN * 4];
void polyconv(int _n, ll a[], int _m, ll b[], ll ret[]) {
    int n = 1;
    while (n < _n + _m - 1) {
        n *= 2;
    }
    for (int i = 0; i < n; i++) {
        binv[i] = (binv[i >> 1] >> 1);
        if (i & 1) {
            binv[i] |= (n >> 1);
        }
        // tempa[i] = a[i];
        // tempb[i] = b[i];
    }
    ntt(a, n, false);
    ntt(b, n, false);
    for (int i = 0; i < n; i++) {
        ret[i] = a[i] * b[i] % mod;
        // a[i] = tempa[i];
        // b[i] = tempb[i];
    }
    ntt(ret, n, true);
}

ll temppolyinv[MAXN * 4];
void polyinv(int n, ll a[], ll ret[]) {
    ret[0] = qpow(a[0], mod - 2);
    for (int len = 2; (len >> 1) < n; len <<= 1) {
        for (int i = 0; i < (len << 1); i++) {
            binv[i] = (binv[i >> 1] >> 1);
            if (i & 1) {
                binv[i] |= len;
            }
            temppolyinv[i] = ((i < n && i < len) ? a[i] : 0);
        }
        ntt(temppolyinv, (len << 1), false);
        ntt(ret, (len << 1), false);
        for (int i = 0; i < (len << 1); i++) {
            ret[i] = (2 - ret[i] * temppolyinv[i] % mod + mod) * ret[i] % mod;
        }
        ntt(ret, (len << 1), true);
        for (int i = min(n, len); i < (len << 1); i++) {
            ret[i] = 0;
        }
    }
}

ll tempinvb[MAXN * 4];
void polydiv(int n, ll a[], int m, ll b[], ll q[], ll r[]) {
    reverse(a, a + n);
    reverse(b, b + m);
    polyinv(n, b, tempinvb);
    polyconv(n, a, n, tempinvb, q);
    reverse(a, a + n);
    reverse(b, b + m);
    for (int i = n - m + 1; i < 4 * n; i++) {
        q[i] = 0;
    }
    reverse(q, q + n - m + 1);
    polyconv(n, b, n, q, r);
    for (int i = 0; i < m - 1; i++) {
        r[i] = (a[i] - r[i] + mod) % mod;
    }
    for (int i = m - 1; i < 4 * n; i++) {
        r[i] = 0;
    }
}