/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"


namespace rt{


	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	Hit Sphere::intersect(Ray ray){
		Vec3f l = ray.o - center;
		float a = ray.d.dotProduct(ray.d);
		float b = 2 * ray.d.dotProduct(l);
		float c = l.dotProduct(l) - std::pow(radius,2);
		float t1 = (-b + std::sqrt(std::pow(b,2) - 4*a*c)) / (2 * a);
		float t2 = (-b - std::sqrt(std::pow(b,2) - 4*a*c)) / (2 * a);
		if (t1 > t2) std::swap(t1, t2);
		if (t1 < 0) {
            t1 = t2; // use t2 if t1 is negative
            if (t2 < 0) { // both t1 and t2 negative
				Hit h = {.itsct=false};
				return h; // return no intersection
			}
        }
		Vec3f p = t1 * ray.d; // point hit
		Vec3f n = (center - p).normalize(); // normal
		Hit h = {true,t1,ray,n,p,material};
		return h;
   }



} //namespace rt
