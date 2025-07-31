long long xorsum(long long x) {
    if (x % 4 == 0) {
        return x;
    } else if (x % 4 == 1) {
        return 1;
    } else if (x % 4 == 2) {
        return x + 1;
    }
    return 0;
}
