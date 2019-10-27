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
	Quad(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3):
		Shape(material) {
            this->n = (v1-v0).crossProduct(v2-v1);
			this->v0 = v0;
			this->v1 = v1;
			this->v2 = v2;
			this->v3 = v3;

			/* Find bounds for x,y,z - used in intersection test
			std::vector<float> values;
			values = {v0.x,v1.x,v2.x,v3.x}; // temporary vector for calculation
			float min_x = std::min_element(values.begin(),values.end());
			float max_x = std::max_element(values.begin(),values.end());
			values = {v0.y,v1.y,v2.y,v3.y};
			float min_y = std::min_element(values.begin(),values.end());
			float max_y = std::max_element(values.begin(),values.end())
			values = {v0.z,v1.z,v2.z,v3.z};
			float min_z = std::min_element(values.begin(),values.end());
			float max_z = std::max_element(values.begin(),values.end())
			this->min = Vec3f(min_x,min_y,min_z);
			this->max = Vec3f(max_x,max_y,max_z);
			*/
		}

	Hit intersect(Ray ray);

	bool inBounds(Vec3f p);

	void getUV(Vec3f p, float& u, float& v) {}

private:
	/* v0 ------ v1
	   |         |
	   |		 |
	   v3 ------ v2 */
	Vec3f v0;
	Vec3f v1;
	Vec3f v2;
	Vec3f v3;
    Vec3f n; // normal of quad
	Vec3f min; // stores min of x,y,z coordinates from v0,v1,v2,v3
	Vec3f max; // stores max of x,y,z coordinates from v0,v1,v2,v3
};



} //namespace rt
