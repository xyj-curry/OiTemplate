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

ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int gc = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return gc;
}  // ans is (x + k * (b / gcd(a, b))), y + k * (a / gcd(a, b))

ll inv[MAXN], fact[MAXN], ifact[MAXN];
void init_fact(int n) {
    fact[0] = inv[0] = ifact[0] = 1;
    fact[1] = inv[1] = ifact[1] = 1;
    for (int i = 2; i <= n; i++) {
        fact[i] = fact[i - 1] * i % mod;
        inv[i] = (-(mod / i) * inv[mod % i] % mod + mod) % mod;
        ifact[i] = ifact[i - 1] * inv[i] % mod;
    }
}

ll C(int n, int m) {
    if (m < 0 || n < 0 || n < m) {
        return 0;
    }
    return fact[n] * (ifact[m] * ifact[n - m] % mod) % mod;
}

ll simC(int n, int m) {
    if (m < 0 || n < 0 || n < m) {
        return 0;
    }
    if (m > n - m) {
        return simC(n, n - m);
    }
    ll p = 1, q = 1;
    for (int i = 1; i <= m; i++) {
        p = p * (n - i + 1) % mod;
        q = q * i % mod;
    }
    return p * qpow(q, mod - 2) % mod;
}

ll lucas(ll n, ll m) {
    if (m < 0 || n < 0 || n < m) {
        return 0;
    }
    ll ret = 1;
    while (n || m) {
        ret = ret * simC(n % mod, m % mod) % mod;
        n /= mod;
        m /= mod;
    }
    return ret;
}

ll one_phi(ll x) {
    ll ret = x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                x /= i;
            }
            ret = ret * (i - 1) / i;
        }
    }
    if (x != 1) {
        ret = ret * (x - 1) / x;
    }
    return ret;
}

vector<ll> pfactor(ll x) {
    vector<ll> ret;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                x /= i;
            }
            ret.push_back(i);
        }
    }
    if (x != 1) {
        ret.push_back(x);
    }
    return ret;
}

// k^l + k^(l + 1) + ... + k^r
ll powLtoR(ll k, ll l, ll r) {
    return (qpow(k, r + 1) - qpow(k, l) + mod) * qpow(k - 1, mod - 2) % mod;
}

// l * k^l + (l + 1) * k^(l + 1) + ... + r * k^r
ll mulpowLtoR(ll k, ll l, ll r) {
    ll invk1 = qpow(k - 1, mod - 2);
    ll pwkr1 = qpow(k, r + 1);
    ll LtoR = (pwkr1 - qpow(k, l)) * invk1 % mod;
    ll ret = (LtoR * (l - 1) + ((pwkr1 * (r - l + 1) - LtoR) % mod) * invk1) % mod;
    return (ret + mod) % mod;
}
