const int mod = 998244353;
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