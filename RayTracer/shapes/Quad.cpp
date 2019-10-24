/*
 * Sphere.cpp
 *
 *
 */
#include "Quad.h"


namespace rt{


/**
 * Computes whether a ray hit the specific instance of a plane shape and returns the hit data
 *
 * @param ray cast ray to check for intersection with shape
 *
 * @return hit struct containing intersection information
 *
 */
Hit Quad::intersect(Ray ray){
	/*
	Hit none = {.itsct=false}; // default to no intersection
    float denom = n.dotProduct(ray.d);
    //printf("%f\n", denom);
    //if (denom < 0.00001) {
    float t = n.dotProduct(p-ray.o) / denom;
    //printf("%f\n", t);
    if (t > 0) { // intersection occurred
        // construct and return hit
        Vec3f p_hit = ray.o + t * ray.d; // point hit
        Hit h = {true,t,ray,n,p_hit,material};
        return h;
    }
    //}
    return none;
	*/
}



} //namespace rt
