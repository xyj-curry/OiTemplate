struct querydata {
    int l, r, x;
    int id;
} q[MAXN];
ll ans[MAXN];
int blsmo;
bool cmp(querydata x, querydata y) {
    if (x.l / blsmo != y.l / blsmo) {
        return x.l < y.l;
    }
    if ((x.l / blsmo) & 1) {
        return x.r > y.r;
    } else {
        return x.r < y.r;
    }
}
int nowl = 1, nowr = 0;
void add(int x) {}
void del(int x) {}

blsmo = n / sqrt(qu);
sort(q + 1, q + 1 + qu, cmp);
for (int i = 1; i <= qu; i++) {
    while (nowl > q[i].l) {
        add(--nowl);
    }
    while (nowr < q[i].r) {
        add(++nowr);
    }
    while (nowl < q[i].l) {
        del(nowl++);
    }
    while (nowr > q[i].r) {
        del(nowr--);
    }
    ans[q[i].id];
}