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
	Quad():Shape(nullptr,getBoundingBox()){};
	Quad(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3):
		Shape(material,getBoundingBox()) {}

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
