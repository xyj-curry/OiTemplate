void manacher(string t, int d[]) {
    string s = "#";
    int n = t.length();
    for (int i = 0; i < n; i++) {
        s += t[i];
        s += '#';
    }
    int l = 0, r = -1;
    for (int i = 0; i < n * 2 + 1; i++) {
        if (r >= i) {
            d[i] = min(d[(l + r) - i], r - i);
        } else {
            d[i] = 0;
        }
        while (((i - d[i] - 1 >= 0) && (i + d[i] + 1 < n * 2 + 1)) &&
               (s[i - d[i] - 1] == s[i + d[i] + 1])) {
            d[i]++;
        }
        if (i + d[i] > r) {
            r = i + d[i];
            l = i - d[i];
        }
    }
}