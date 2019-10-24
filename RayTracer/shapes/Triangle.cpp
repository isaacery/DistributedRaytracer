/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{

void Triangle::createTriangle(Value& shapeSpecs) {
<<<<<<< HEAD
	Value& v0 = shapeSpecs["v0"]; // parse v0
	float x = v0[0].GetFloat();
	float y = v0[1].GetFloat();
	float z = v0[2].GetFloat();
	this->v0 = Vec3f(x,y,z);
    Value& v0 = shapeSpecs["v1"]; // parse v0
    float x = v1[0].GetFloat();
    float y = v1[1].GetFloat();
    float z = v1[2].GetFloat();
    this->v1 = Vec3f(x,y,z);
    Value& v2 = shapeSpecs["v2"]; // parse v2
    float x = v2[0].GetFloat();
    float y = v2[1].GetFloat();
    float z = v2[2].GetFloat();
    this->v2 = Vec3f(x,y,z);
	BlinnPhong mat = new BlinnPhong();
    mat->createBlinnPhong(shapeSpecs["material"]); // parse material
	material = mat;
=======
	Value& vert0 = shapeSpecs["vert0"]; // parse v0
	float x = vert0[0].GetFloat();
	float y = vert0[1].GetFloat();
	float z = vert0[2].GetFloat();
	this->v0 = Vec3f(x,y,z);
    Value& vert1 = shapeSpecs["v1"]; // parse v1
    x = vert1[0].GetFloat();
    y = vert1[1].GetFloat();
    z = vert1[2].GetFloat();
    this->v1 = Vec3f(x,y,z);
    Value& vert2 = shapeSpecs["vert2"]; // parse v2
    x = vert2[0].GetFloat();
    y = vert2[1].GetFloat();
    z = vert2[2].GetFloat();
    this->v2 = Vec3f(x,y,z);
>>>>>>> tmp
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
        Hit h = {true,t,ray,n,p,material};
        return h;
    } else { // intersection is behind origin
        return none;
    }
}

} //namespace rt
