/*
 * Sphere.cpp
 *
 *
 */
#include "Plane.h"


namespace rt {

void Plane::getUV(Vec3f p, float& u, float& v) {}

BoundingBox* Plane::getBoundingBox() {
	return new BoundingBox(Vec3f(-INFINITY),Vec3f(INFINITY));
}

void Plane::createPlane(Value& shapeSpecs) {
	float x = shapeSpecs["normal"][0].GetFloat();
	float y = shapeSpecs["normal"][1].GetFloat();
	float z = shapeSpecs["normal"][2].GetFloat();
	this->n = Vec3f(x,y,z).normalize();
	float distance = shapeSpecs["distance"].GetFloat(); // parse distance
	this->p = this->n * distance;
}

/**
 * Computes whether a ray hit the specific instance of a plane shape and returns the hit data
 *
 * @param ray cast ray to check for intersection with shape
 *
 * @return hit struct containing intersection information
 *
 */
Hit Plane::intersect(Ray ray){
	Hit none = {.itsct=false}; // default to no intersection
	float denom = n.dotProduct(ray.d);
	float t = n.dotProduct(p-ray.o) / denom;
	if (t > 0) { // intersection occurred
		// construct and return hit
		Vec3f p_hit = ray.o + t * ray.d; // point hit
		Hit h = {true,t,ray,n,p_hit,material,this};
		return h;
	}
    return none;
}



} //namespace rt
