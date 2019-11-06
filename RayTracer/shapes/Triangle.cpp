/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{

/* return bounding box that bounds triangle */
BoundingBox* Triangle::getBoundingBox() {
	BoundingBox* box = new BoundingBox;
	box->add(v0);
	box->add(v1);
	box->add(v2);
	return box;
}

/* interpolate between uv coordinates at each vertex */
void Triangle::getUV(Vec3f p, float& u, float& v) {
	float a;
	float b;
	float c;
	barycentric(p,a,b,c);
	Vec2f uv = v0_uv * a + v1_uv * b + v2_uv * c;
	u = uv.x;
	v = uv.y;
}

void Triangle::createTriangle(Value& shapeSpecs) { // TODO: parse vertex normals, interpolate
	float x = shapeSpecs["v0"][0].GetFloat();
	float y = shapeSpecs["v0"][1].GetFloat();
	float z = shapeSpecs["v0"][2].GetFloat();
	float u = shapeSpecs["v0_uv"][0].GetFloat();
	float v = shapeSpecs["v0_uv"][1].GetFloat();
	this->v0 = Vec3f(x,y,z);
	this->v0_uv = Vec2f(u,v);
    x = shapeSpecs["v1"][0].GetFloat();
    y = shapeSpecs["v1"][1].GetFloat();
    z = shapeSpecs["v1"][2].GetFloat();
	u = shapeSpecs["v1_uv"][0].GetFloat();
	v = shapeSpecs["v1_uv"][1].GetFloat();
    this->v1 = Vec3f(x,y,z);
	this->v1_uv = Vec2f(u,v);
    x = shapeSpecs["v2"][0].GetFloat();
    y = shapeSpecs["v2"][1].GetFloat();
    z = shapeSpecs["v2"][2].GetFloat();
	u = shapeSpecs["v2_uv"][0].GetFloat();
	v = shapeSpecs["v2_uv"][1].GetFloat();
    this->v2 = Vec3f(x,y,z);
	this->v2_uv = Vec2f(u,v);
}

/* convert point p on triangle to barycentric coordinates */
void Triangle::barycentric(Vec3f p, float &a, float&b, float&c) {
    Vec3f vec0 = v1 - v0;
	Vec3f vec1 = v2 - v0;
	Vec3f vec2 = p - v0;
    float d00 = vec0.dotProduct(vec0);
    float d01 = vec0.dotProduct(vec1);
    float d11 = vec1.dotProduct(vec1);
    float d20 = vec2.dotProduct(vec0);
    float d21 = vec2.dotProduct(vec1);
    float denom = d00 * d11 - d01 * d01;
    b = (d11 * d20 - d01 * d21) / denom;
    c = (d00 * d21 - d01 * d20) / denom;
    a = 1 - b - c;
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
