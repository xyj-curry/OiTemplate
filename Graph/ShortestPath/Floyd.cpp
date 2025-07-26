void floyd_dot(int k) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
        }
    }
}
void floyd() {
    for (int k = 1; k <= n; k++) {
        floyd_dot(k);
    }
}