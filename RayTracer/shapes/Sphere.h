/*
 * Sphere.h
 *
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "math/geometry.h"
#include "core/Shape.h"

using namespace rapidjson;

namespace rt{

class Sphere:public Shape{

public:
	// Constructors
	Sphere():Shape(){};
	Sphere(Vec3f center, float radius, Material* material):
		Shape(material) {
			this->center = center;
			this->radius = radius;
		}

	void createSphere(Value& shapeSpecs);

	Hit intersect(Ray ray);

private:

	Vec3f center;
	float radius;

};



} //namespace rt




#endif /* SPHERE_H_ */
