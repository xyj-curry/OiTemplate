bool not_prime[MAXN];
int phi[MAXN];
vector<int> pri;
void init_prime(int n) {
    not_prime[1] = true;
    phi[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (!not_prime[i]) {
            pri.push_back(i);
            phi[i] = i - 1;
        }
        for (int j : pri) {
            if (1LL * i * j > n) {
                break;
            }
            not_prime[i * j] = true;
            if (i % j == 0) {
                phi[i * j] = phi[i] * j;
                break;
            }
            phi[i * j] = phi[i] * phi[j];
        }
    }
}
ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
ll qpow(ll a, ll b, ll mod) {
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
vector<ll> pfactor(ll x) {
    vector<ll> ret;
    for (int i : pri) {
        if (1LL * i * i > x) {
            break;
        }
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
bool checkprt(int x, int prt, vector<ll> phi_pfactor) {
    for (int i : phi_pfactor) {
        if (qpow(prt, phi[x] / i, x) == 1) {
            return false;
        }
    }
    return true;
}
bool existprt(int x) {
    if (x == 2 || x == 4) {
        return true;
    }
    if (x % 2 == 0) {
        x /= 2;
    }
    vector<ll> x_pfactor = pfactor(x);
    return x_pfactor.size() == 1 && x_pfactor[0] != 2;
}
int min_prt(int x) {
    if (!existprt(x)) {
        return -1;
    }
    vector<ll> phi_pfactor = pfactor(phi[x]);
    for (int i = 1;; i++) {
        if (gcd(i, x) != 1) {
            continue;
        }
        if (checkprt(x, i, phi_pfactor)) {
            return i;
        }
    }
    return -1;
}
vector<int> all_prt(int x) {
    int g = min_prt(x);
    vector<int> ret;
    if (g == -1) {
        return ret;
    }
    int nowg = 1;
    for (int i = 1; i <= phi[x]; i++) {
        nowg = 1LL * nowg * g % x;
        if (gcd(i, phi[x]) == 1) {
            ret.push_back(nowg);
        }
    }
    return ret;
}
/*
ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
ll qpow(ll a, ll b, ll mod) {
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
bool checkprt(int x, int prt, int phi, vector<ll> phi_pfactor) {
    for (int i : phi_pfactor) {
        if (qpow(prt, phi / i, x) == 1) {
            return false;
        }
    }
    return true;
}
bool existprt(int x) {
    if (x == 2 || x == 4) {
        return true;
    }
    if (x % 2 == 0) {
        x /= 2;
    }
    vector<ll> x_pfactor = pfactor(x);
    return x_pfactor.size() == 1 && x_pfactor[0] != 2;
}
int min_prt(int x) {
    if (!existprt(x)) {
        return -1;
    }
    int phi = one_phi(x);
    vector<ll> phi_pfactor = pfactor(phi);
    for (int i = 1;; i++) {
        if (gcd(i, x) != 1) {
            continue;
        }
        if (checkprt(x, i, phi, phi_pfactor)) {
            return i;
        }
    }
    return -1;
}
vector<int> all_prt(int x) {
    int g = min_prt(x);
    vector<int> ret;
    if (g == -1) {
        return ret;
    }
    int phi = one_phi(x);
    int nowg = 1;
    for (int i = 1; i <= phi; i++) {
        nowg = 1LL * nowg * g % x;
        if (gcd(i, phi) == 1) {
            ret.push_back(nowg);
        }
    }
    return ret;
}
*/