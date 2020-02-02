/*
 * Sphere.h
 *
 *
 */

#pragma once

#include "core/Shape.h"
#include "shapes/Triangle.h"
#include "shapes/TriMesh.h"
#include "shapes/BoundingBox.h"

using namespace rapidjson;

namespace rt{

/* Planar quad. Defined by a point and two edge vectors. Implemented
by an underlying triangle mesh of two triangles forming the quad. */
class Quad:public Shape{

public:
	// Constructors
	Quad():Shape(){};
<<<<<<< HEAD
	Quad(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3):
		Shape(material) {}
=======
	Quad(Vec3f p, Vec3f e0, Vec3f e1, Material* m):
		Shape(material) {
			Vec3f v0 = p;
			Vec3f v1 = p + e0;
			Vec3f v2 = p + e1;
			Vec3f v3 = p + e0 + e1;
			Vec2f uv = Vec2f(0);
			Triangle* t1 = new Triangle(v0,uv,v1,uv,v2,uv,m); // TODO: uv
			Triangle* t2 = new Triangle(v3,uv,v1,uv,v2,uv,m);
			std::vector<Triangle*> tris = {t1,t2};
			this->mesh = new TriMesh(tris,m);
		}
>>>>>>> textures

	Hit intersect(Ray ray);

	bool inBounds(Vec3f p);

	void setMaterial(Material* mat) {
		mesh->setMaterial(mat);
	}

	void createQuad(Value& shapeSpecs);

	void getUV(Vec3f p, float& u, float& v) {} // handled by underlying triangle mesh

	BoundingBox* getBoundingBox();

private:
	/* v0 ------ v1
	   |         |
	   |		 |
	   v2 ------ v3 */
	TriMesh* mesh;
};



} //namespace rt
