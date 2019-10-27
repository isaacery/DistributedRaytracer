/*
 * Sphere.h
 *
 *
 */

#pragma once

#include "math/geometry.h"
#include "core/Shape.h"

using namespace rapidjson;

namespace rt{

class Quad:public Shape{

public:
	// Constructors
	Quad():Shape(){};
    // n is normal vector of plane, d distance from plane to origin
	Quad(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3);
	/*
		Shape(material) {
            this->n = n.normalize();
			this->p = this->n * d;
		}
		*/

	Hit intersect(Ray ray);

	void getUV(Vec3f p, float& u, float& v) {}

private:
	/* p0 ------ p1
	   |         |
	   |		 |
	   p3 ------ p2 */
	Vec3f v0;
	Vec3f v1;
	Vec3f v2;
	Vec3f v3;
    Vec3f n; // normal of quad
};



} //namespace rt
