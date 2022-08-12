#pragma once
#include "Ray.h"
#include "HitPoint.h"

enum Material {
	diffuse,
	mirror
};

class Sphere {
public:
	Vec3 o;
	double r;
	RGB color;
	Material m;

	Sphere() : r(1.0) {}
	Sphere(const Vec3& o) : o(o), r(1.0) {}
	Sphere(const Vec3& o, double r) : o(o), r(r) {}
	bool hit(const Ray& ray, HitPoint& hp) const {
        Vec3 oc = ray.o - o;
        double a = dot(ray.d, ray.d);
        double b = 2.0 * dot(oc, ray.d);
        double c = dot(oc, oc) - r * r;
        double d = b * b - 4.0 * a * c;
		if (d < 0.0) return false;
		double t = (-b - sqrt(d)) / (2.0 * a);
		if (t > 0.0) {
			Vec3 p = ray.p(t);
			Vec3 n = (p - o) / r;
			hp.t = t; hp.p = p;	hp.n = n;
			return true;
		}
		t = (-b + sqrt(d)) / (2.0 * a);
		if (t > 0.0) {
			Vec3 p = ray.p(t);
			Vec3 n = (p - o) / r;
			hp.t = t; hp.p = p;	hp.n = n;
			return true;
		}
		return false;
	}
};