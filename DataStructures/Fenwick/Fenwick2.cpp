template <typename T>
struct Fenwick {
    int n, lg2;
    vector<int> t;

    Fenwick(int n_ = 0) { init(n_); }

    void init(int n_) {
        n = n_;
        lg2 = 0;
        while (n_) {
            n_ /= 2;
            lg2++;
        }
        t.assign(n + 1, T{});
    }

    void modify(int i, T x) {
        for (; i <= n; i += (i & (-i))) {
            t[i] += x;
        }
    }

    T query(int i) {
        T ret{};
        for (; i > 0; i -= (i & (-i))) {
            ret += t[i];
        }
        return ret;
    }

    T rangequery(int l, int r) { return query(r) - query(l - 1); }

    int lower_bound(T x) {
        int ret = 0;
        for (int i = lg2; i >= 0; i--) {
            if (ret + (1 << i) <= n && t[ret + (1 << i)] < x) {
                x -= t[ret + (1 << i)];
                ret += (1 << i);
            }
        }
        return ret + 1;
    }

    int upper_bound(T x) {
        int ret = 0;
        for (int i = lg2; i >= 0; i--) {
            if (ret + (1 << i) <= n && t[ret + (1 << i)] <= x) {
                x -= t[ret + (1 << i)];
                ret += (1 << i);
            }
        }
        return ret + 1;
    }
};