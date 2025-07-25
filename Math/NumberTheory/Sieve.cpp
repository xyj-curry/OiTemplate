bool not_prime[MAXN];
vector<int> pri;
void init_prime(int n) {
    not_prime[1] = true;
    for (int i = 2; i <= n; i++) {
        if (!not_prime[i]) {
            pri.push_back(i);
        }
        for (int j : pri) {
            if (1LL * i * j > n) {
                break;
            }
            not_prime[i * j] = true;
            if (i % j == 0) {
                break;
            }
        }
    }
}

// 区间筛
bool not_prime_big[MAXN];
void range_sieve(ll l, ll r) {
    init_prime(sqrt(r));
    for (int i : pri) {
        if (i > r) {
            break;
        }
        for (ll j = max((ll)i * 2, (l / i + 1) * i); j <= r; j += i) {
            not_prime_big[j - l] = true;
        }
    }
}

// phi
bool not_prime[MAXN];
int phi[MAXN];
vector<int> pri;
void init_prime(int n) {
    not_prime[1] = true;
    phi[1] = 1;
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
// mu
