int ne[MAXN];
string s, t;
void initNext() {
    int i = 1, l = 0;
    ne[0] = 0;
    while (i < m) {
        if (t[i] == t[l]) {
            ne[i++] = ++l;
        } else if (l == 0) {
            ne[i++] = 0;
        } else {
            l = ne[l - 1];
        }
    }
}
void find() {
    int i = 0, j = 0;
    while (i < n) {
        if (s[i] == t[j]) {
            i++;
            j++;
        } else if (j == 0) {
            i++;
        } else {
            j = ne[j - 1];
        }
        if (j == m) {
            printf("%d\n", i - m + 1);
            j = ne[j - 1];
        }
    }
}