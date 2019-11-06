/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"

#include <math.h>

namespace rt{

void Sphere::createSphere(Value& shapeSpecs) {
	float x = shapeSpecs["center"][0].GetFloat();
	float y = shapeSpecs["center"][1].GetFloat();
	float z = shapeSpecs["center"][2].GetFloat();
	this->center = Vec3f(x,y,z);
	radius = shapeSpecs["radius"].GetFloat(); // parse radius
}

/* get bounding box that bounds sphere */
BoundingBox* Sphere::getBoundingBox() {
	return new BoundingBox(center - Vec3f(radius), center + Vec3f(radius));
}

/* update uv coordinates at point of intersection p on sphere */
void Sphere::getUV(Vec3f p, float& u, float& v) {
	float theta1 = atan2(-(p.z-center.z), p.x-center.x);
	float theta2 = acos(-(p.y-center.y) / radius);
	u = (theta1 + M_PI) / (2 * M_PI);
	v = theta2 / M_PI;
}


/**
 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
 *
 * @param ray cast ray to check for intersection with shape
 *
 * @return hit struct containing intersection information
 *
 */
Hit Sphere::intersect(Ray ray){
	Hit none = {.itsct=false}; // default to no intersection
	float t0, t1; // two points of intersection
	Vec3f l = ray.o - center;
	float a = ray.d.dotProduct(ray.d);
	float b = 2 * l.dotProduct(ray.d);
	float c = l.dotProduct(l) - radius*radius;
	float dscr = b * b - 4 * a * c;
	// solve using quadratic formula
	if (dscr >= 0) {
		if (dscr == 0) {
			t0 = t1 = - 0.5 * b / a;
		} else {
			float z = (b > 0) ?
	            -0.5 * (b + std::sqrt(dscr)) :
	            -0.5 * (b - std::sqrt(dscr));
	        t0 = z / a;
	        t1 = c / z;
		}
	} else {
		return none;
	}
	// determine correct t to return
	if (t0 > t1) {
		 std::swap(t0, t1);
	}
	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0) {
			return none; // both are negative
		}
	}
	// construct and return hit
	Vec3f p = ray.o + t0 * ray.d; // point hit
	Vec3f n = (p - center).normalize(); // normal
	Hit h = {true,t0,ray,n,p,material,this};
	return h;
}



} //namespace rt
