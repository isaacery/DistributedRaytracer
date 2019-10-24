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
	Quad(Vec3f p0, Vec3f p1, Vec3f p2, Vec3f p3);
	/*
		Shape(material) {
            this->n = n.normalize();
			this->p = this->n * d;
		}
		*/

	Hit intersect(Ray ray);

private:
	/* p0 ------ p1
	   |         |
	   |		 |
	   p2 ------ p3 */
	Vec3f p0;
	Vec3f p1;
	Vec3f p2;
	Vec3f p3;
    Vec3f n; // normal of quad
};



} //namespace rt
