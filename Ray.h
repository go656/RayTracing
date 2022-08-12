#pragma once
#include "Vec3.h"

class Ray {
public:
	Vec3 o, d;
	Ray() {}
	Ray(const Vec3& o, const Vec3& d) : o(o), d(d) {}
	Vec3 p(double t) const { return o + t * d; }
};
