#pragma once

class RGB {
public:
	double r, g, b;
	RGB() : r(0.0), g(0.0), b(0.0) {}
	RGB(double r, double g, double b) : r(r), g(g), b(b) {}
	RGB operator-() const { return RGB(-r, -g, -b); }
	void operator+=(const RGB& rgb) { r += rgb.r; g += rgb.g; b += rgb.b; }
	void operator-=(const RGB& rgb) { r -= rgb.r; g -= rgb.g; b -= rgb.b; }
};

RGB operator+(const RGB& a, const RGB& b) { return RGB(a.r + b.r, a.g + b.g, a.b + b.b); }
RGB operator-(const RGB& a, const RGB& b) { return RGB(a.r - b.r, a.g - b.g, a.b - b.b); }
RGB operator*(double a, const RGB& b) { return RGB(a * b.r, a * b.g, a * b.b); }
RGB operator*(const RGB& a, double b) { return RGB(a.r * b, a.g * b, a.b * b); }
RGB operator*(const RGB& a, const RGB& b) { return RGB(a.r * b.r, a.g * b.g, a.b * b.b); }
RGB operator/(double a, const RGB& b) { return RGB(a / b.r, a / b.g, a / b.b); }
RGB operator/(const RGB& a, double b) { return RGB(a.r / b, a.g / b, a.b / b); }
RGB operator/(const RGB& a, const RGB& b) { return RGB(a.r / b.r, a.g / b.g, a.b / b.b); }
