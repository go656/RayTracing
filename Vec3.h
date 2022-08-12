#pragma once
#include <cmath>

class Vec3 {
public:
	double x, y, z;
	Vec3() : x(0.0), y(0.0), z(0.0) {}
	Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
	Vec3 operator-() const { return Vec3(-x, -y, -z); }
	void operator+=(const Vec3& v) { x += v.x; y += v.y; z += v.z; }
	void operator-=(const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; }
};

Vec3 operator+(const Vec3& a, const Vec3& b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
Vec3 operator-(const Vec3& a, const Vec3& b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
Vec3 operator*(double a, const Vec3& b) { return Vec3(a * b.x, a * b.y, a * b.z); }
Vec3 operator*(const Vec3& a, double b) { return Vec3(a.x * b, a.y * b, a.z * b); }
Vec3 operator/(double a, const Vec3& b) { return Vec3(a / b.x, a / b.y, a / b.z); }
Vec3 operator/(const Vec3& a, double b) { return Vec3(a.x / b, a.y / b, a.z / b); }
double dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
Vec3 cross(const Vec3& a, const Vec3& b) { return Vec3(a.y * b.z - a.z * b.y, a.z* b.x - a.x * b.z, a.x* b.y - a.y * b.x); }
double len2(const Vec3& v) { return v.x * v.x + v.y * v.y + v.z * v.z; }
double len(const Vec3& v) { return sqrt(len2(v)); }
Vec3 normalize(const Vec3& v) { return v / len(v); }
Vec3 reflect(const Vec3& v, const Vec3& n) { return v - 2.0 * dot(v, n) * n; }
