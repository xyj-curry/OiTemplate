ll polyval(int n, ll a[], ll x) {
    ll ret = 0;
    for (int i = n; i >= 0; i--) {
        ret = (ret * x + a[i]) % mod;
    }
    return ret;
}