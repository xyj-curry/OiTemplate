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