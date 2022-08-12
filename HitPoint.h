#pragma once
#include "Vec3.h"

class HitPoint {
public:
	double t;
	Vec3 p, n;
	HitPoint() : t(0.0) {}
	HitPoint(double t) : t(t) {}
};