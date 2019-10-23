/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{

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
        Hit h = {true,t,ray,n,p,material};
        return h;
    } else { // intersection is behind origin
        return none;
    }
}

} //namespace rt
