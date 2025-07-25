const int inv2 = (mod + 1) / 2;
void fwt(ll a[], int n, bool rev, int type) {  // 1 or, 2 and, 3 xor
    for (int len = 2; len <= n; len <<= 1) {
        for (int i = 0; i < n; i += len) {
            for (int j = i; j < i + (len >> 1); j++) {
                if (type == 1) {  // or
                    a[j + (len >> 1)] = ((rev ? -1 : 1) * a[j] + a[j + (len >> 1)] + mod) % mod;
                } else if (type == 2) {  // and
                    a[j] = (a[j] + (rev ? -1 : 1) * a[j + (len >> 1)] + mod) % mod;
                } else {  // xor
                    ll tmp = a[j + (len >> 1)] * (rev ? inv2 : 1) % mod;
                    a[j + (len >> 1)] = (a[j] * (rev ? inv2 : 1) - tmp + mod) % mod;
                    a[j] = (a[j] * (rev ? inv2 : 1) + tmp) % mod;
                }
            }
        }
    }
}

// ll tempa[MAXN], tempb[MAXN];
void bitconv(int n, ll a[], ll b[], ll ret[], int type) {  // 1 or, 2 and, 3 xor
    // for (int i = 0; i < n; i++) {
    //     tempa[i] = a[i];
    //     tempb[i] = b[i];
    // }
    fwt(a, n, false, type);
    fwt(b, n, false, type);
    for (int i = 0; i < n; i++) {
        ret[i] = a[i] * b[i] % mod;
        // a[i] = tempa[i];
        // b[i] = tempb[i];
    }
    fwt(ret, n, true, type);
}
