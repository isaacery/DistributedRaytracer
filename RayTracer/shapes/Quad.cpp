/*
 * Sphere.cpp
 *
 *
 */
#include "Quad.h"


namespace rt{


/**
 * Computes whether a ray hit the specific instance of a quad shape and returns the hit data
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
    float t = n.dotProduct(v0-ray.o) / denom;
    if (t > 0) { // intersection occurred with plane
        // construct and return hit
        Vec3f p_hit = ray.o + t * ray.d; // point hit
        if (Quad::inBounds(p_hit)) {
            Hit h = {true,t,ray,n,p_hit,material,this};
            return h;
        }
    }
    return none;
    */
    Hit none = {.itsct=false}; // default to no intersection
    return none;
}

bool Quad::inBounds(Vec3f p) {
    bool x = (min.x <= p.x) && (p.x <= max.x);
    if (x) {
        bool y = (min.y <= p.y) && (p.y <= max.y);
        if (y) {
            bool z = (min.z <= p.z) && (p.z <= max.z);
            return z;
        }
    }
}



} //namespace rt
