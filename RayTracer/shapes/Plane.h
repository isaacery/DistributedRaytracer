/*
 * Sphere.h
 *
 *
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "math/geometry.h"
#include "core/Shape.h"

using namespace rapidjson;

namespace rt{

class Plane:public Shape{

public:
	// Constructors
	Plane():Shape(){};
    // n is normal vector of plane, d distance from plane to origin
	Plane(Vec3f n, float d, Material* material):
		Shape(material) {
            this->n = n.normalize();
			this->p = this->n * d;
		}

	void createPlane(Value& shapeSpecs);

	Hit intersect(Ray ray);

private:
	Vec3f p; // point on plane representing how far plane is from origin
    Vec3f n; // normal of plane
};



} //namespace rt




#endif /* SPHERE_H_ */