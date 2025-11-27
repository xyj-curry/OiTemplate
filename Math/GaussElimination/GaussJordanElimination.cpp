void gauss() {
    int r = 1;
    for (int i = 1; i <= n; i++) {
        int l = -1;
        for (int j = r; j <= n; j++) {
            if (fabs(a[j][i]) >= eps) {
                l = j;
                break;
            }
        }
        if (l == -1) {
            continue;
        }
        for (int j = 1; j <= n + 1; j++) {
            swap(a[r][j], a[l][j]);
        }
        for (int j = 1; j <= n; j++) {
            if (j == r) {
                continue;
            }
            double tmp = a[j][i] / a[r][i];
            for (int k = 1; k <= n + 1; k++) {
                a[j][k] -= (tmp * a[r][k]);
            }
        }
        r++;
    }
    if (r <= n) {
        for (; r <= n; r++) {
            if (fabs(a[r][n + 1]) >= eps) {
                printf("-1");  // no ans
                return;
            }
        }
        printf("0");  // inf ans
        return;
    }
    for (int i = 1; i <= n; i++) {
        a[i][n + 1] / a[i][i];  // x_i ans
    }
}