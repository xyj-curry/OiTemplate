void manacher(string t, int d[]) {
    string s = "#";
    int n = t.length();
    for (int i = 0; i < n; i++) {
        s += t[i];
        s += '#';
    }
    b = t.length();
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        d[i] = 1;
        if (i <= r) {
            d[i] = min(r - i + 1, d[l + r - i]);
        }
        while ((i - d[i] >= 0 && i + d[i] < n) && (t[i - d[i]] == t[i + d[i]])) {
            d[i]++;
        }
        if (i + d[i] - 1 > r) {
            r = i + d[i] - 1;
            l = i - d[i] + 1;
        }
    }
    for (int i = 1; i < n - 1; i++) {
        if (i % 2 == 1) {
            //((i / 2) - ((d[i] - 1) / 2)]) ~ ((i / 2) + ((d[i] - 1) / 2)) = d[i] - 1
        } else {
            //((i / 2) - ((d[i] - 1) / 2)]) ~ ((i / 2) + ((d[i] - 1) / 2) - 1) = d[i] - 1
        }
    }
}