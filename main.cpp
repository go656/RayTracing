#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Vec3.h"
#include "RGB.h"
#include "Sphere.h"

using namespace std;

const double inf = numeric_limits<double>::infinity();

double rand_d() { return (double)rand() / RAND_MAX; }
double rand_d(double min, double max) { return (max - min) * rand_d() + min; }
Vec3 rand_v(double min, double max) { return Vec3(rand_d(min, max), rand_d(min, max), rand_d(min, max)); }
Vec3 rand_v_sphere() {
	Vec3 v;
	do {
		v = rand_v(-1.0, 1.0);
	} while (1.0 < len2(v));
	return v;
}

RGB sky(const Ray& ray) {
	if (ray.d.y < 0.0) return RGB(0.6, 0.8, 1.0);
	return ray.d.y * RGB(0.0, 0.2, 0.5) + (1.0 - ray.d.y) * RGB(0.6, 0.8, 1.0);
}

RGB trace(const Ray& ray, vector<Sphere>& spheres) {
	Sphere* p_s = nullptr;
	HitPoint hp(inf);

	for (Sphere& s : spheres) {
		HitPoint hp_tmp;
		if (s.hit(ray, hp_tmp) && hp_tmp.t < hp.t) {
			hp = hp_tmp;
			p_s = &s;
		}
	}
	if (p_s != nullptr) {
		Vec3 d;
		if (p_s->m == diffuse) {
			d = normalize(hp.p + hp.n + rand_v_sphere());
		}
		else if (p_s->m == mirror) {
			d = reflect(ray.d, hp.n);
		}
		Ray r_ray(ray.o, d);
		return p_s->color * trace(r_ray, spheres);
	}

	return sky(ray);
}

int main() {

	srand((unsigned int)time(NULL));

	const int width = 1280;
	const int height = 720;

	const double aspect = (double)width / height;

	const double pw = 2.0 / height;
	const double ph = pw;

	const double x0 = -pw * (0.5 * width);
	const double y0 = -ph * (0.5 * height);

	const double focal_distance = sqrt(3.0);
	const Vec3 camera(0.0, 1.0, 3.0);

	const int n_sample = 100;

	vector<vector<RGB>> image(height, vector<RGB>(width));
	vector<Sphere> spheres(2);

	spheres[0].o = Vec3(0.0, -1000.0, 0.0);
	spheres[0].r = 1000.0;
	spheres[0].color = RGB(0.6, 0.8, 0.3);
	spheres[0].m = diffuse;

	spheres[1].o = Vec3(0.0, 1.0, 0.0);
	spheres[1].r = 1.0;
	spheres[1].color = RGB(1.0, 1.0, 1.0);
	spheres[1].m = mirror;

	/*
	for (int i = 1; i < spheres.size(); i++) {
		spheres[i].o = Vec3(rand_d(-1.0, 1.0), 0.1, rand_d(-1.0, 1.0));
		spheres[i].r = 0.1;
		spheres[i].color = RGB(rand_d(), rand_d(), rand_d());
	}
	*/

	cout << "P3" << endl;
	cout << width << " " << height << endl;
	cout << "255" << endl;

	for (int sample = 1; sample <= n_sample; sample++) {
		for (int v = 0; v < height; v++) {
			for (int u = 0; u < width; u++) {
				double dx = x0 + (u + rand_d()) * pw;
				double dy = y0 + (height - 1 - v + rand_d()) * ph;
				double dz = -focal_distance;
				Ray ray(camera, normalize(Vec3(dx, dy, dz)));
				RGB l_o = trace(ray, spheres);
				image[v][u] += l_o / n_sample;
			}
		}
		int percent = (int)(100.0 * sample / n_sample);
		cerr << "\rRendering " << percent << "%" << flush;
	}

	for (int v = 0; v < height; v++) {
		for (int u = 0; u < width; u++) {
			RGB& p = image[v][u];
			int r = (int)(255.0 * p.r);
			int g = (int)(255.0 * p.g);
			int b = (int)(255.0 * p.b);

			cout << r << " " << g << " " << b << endl;
		}
	}
}
