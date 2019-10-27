/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{

void Triangle::createTriangle(Value& shapeSpecs) {
	float x = shapeSpecs["v0"][0].GetFloat();
	float y = shapeSpecs["v0"][1].GetFloat();
	float z = shapeSpecs["v0"][2].GetFloat();
	this->v0 = Vec3f(x,y,z);
    x = shapeSpecs["v1"][0].GetFloat();
    y = shapeSpecs["v1"][1].GetFloat();
    z = shapeSpecs["v1"][2].GetFloat();
    this->v1 = Vec3f(x,y,z);
    x = shapeSpecs["v2"][0].GetFloat();
    y = shapeSpecs["v2"][1].GetFloat();
    z = shapeSpecs["v2"][2].GetFloat();
    this->v2 = Vec3f(x,y,z);
}

Hit Triangle::intersect(Ray ray) {
    Hit none = {.itsct=false};
    Vec3f e0 = v1 - v0;
    Vec3f e1 = v2 - v0;
    Vec3f h = ray.d.crossProduct(e1);
    float a = e0.dotProduct(h);
    if (a == 0) { // a == 0
        return none; // ray parallel to triangle
    }
    float f = 1/a;
    Vec3f s = ray.o - v0;
    float u = f * s.dotProduct(h);
    if (u < 0 || u > 1) { // return none if u out of range [0,1]
        return none;
    }
    Vec3f q = s.crossProduct(e0);
    float v = f * ray.d.dotProduct(q);
    if (v < 0.0 || u + v > 1.0)
        return none;
    float t = f * e1.dotProduct(q); // compute t
    if (t >= 0) { // ray intersects
        // construct and return hit
        Vec3f p = ray.o + t * ray.d; // point hit
        Vec3f n = e0.crossProduct(e1).normalize();
		if (ray.d.dotProduct(n) > 0) {
			n = -n; // flip normal if normal faces same dir as ray
		}
        Hit h = {true,t,ray,n,p,material,this};
        return h;
    } else { // intersection is behind origin
        return none;
    }
}

} //namespace rt
