const double PI = acos(-1.0);

struct Complex {
    double x, y;
    Complex(double _x = 0, double _y = 0) {
        x = _x;
        y = _y;
    }
    Complex operator+(const Complex& a) const { return Complex(x + a.x, y + a.y); }
    Complex operator-(const Complex& a) const { return Complex(x - a.x, y - a.y); }
    Complex operator*(const Complex& a) const {
        return Complex(x * a.x - y * a.y, x * a.y + y * a.x);
    }
};

int binv[MAXN * 4];
void fft(Complex a[], int n, bool rev) {
    for (int i = 0; i < n; i++) {
        if (i < binv[i]) {
            swap(a[i], a[binv[i]]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        Complex wn(cos(2 * PI / len), (rev ? -1 : 1) * sin(2 * PI / len));
        for (int i = 0; i < n; i += len) {
            Complex w(1, 0);
            for (int j = i; j < i + (len >> 1); j++, w = w * wn) {
                Complex tmp = w * a[j + (len >> 1)];
                a[j + (len >> 1)] = a[j] - tmp;
                a[j] = a[j] + tmp;
            }
        }
    }
    if (rev) {
        for (int i = 0; i < n; i++) {
            a[i].x /= n;
            a[i].y /= n;
        }
    }
}

void polyconv(int _n, Complex a[], int _m, Complex b[], Complex ret[]) {
    int n = 1;
    while (n < _n + _m - 1) {
        n *= 2;
    }
    for (int i = 0; i < n; i++) {
        binv[i] = (binv[i >> 1] >> 1);
        if (i & 1) {
            binv[i] |= (n >> 1);
        }
    }
    fft(a, n, false);
    fft(b, n, false);
    for (int i = 0; i < n; i++) {
        ret[i] = a[i] * b[i];
    }
    fft(ret, n, true);
}

void fft(Complex a[], int n, bool rev) {
    if (n == 1) {
        return;
    }
    for (int i = 0; i < n; i++) {
        temp[i] = a[i];
    }
    for (int i = 0; i < n / 2; i++) {
        a[i] = temp[i * 2];
        a[i + (n / 2)] = temp[i * 2 + 1];
    }
    fft(a, n / 2, rev);
    fft(a + n / 2, n / 2, rev);
    Complex w(1, 0), wn(cos(PI * 2 / n), (rev ? -1 : 1) * sin(PI * 2 / n));
    for (int i = 0; i < n / 2; i++, w = w * wn) {
        Complex tmp = w * a[i + n / 2];
        a[i + n / 2] = a[i] - tmp;
        a[i] = a[i] + tmp;
    }
}