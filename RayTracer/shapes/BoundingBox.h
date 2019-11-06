/*
 * BoundingBox.h
 *
 *
 */

#pragma once

#include "core/Shape.h"
#include "math/geometry.h"

using namespace rapidjson;

namespace rt{

class BoundingBox:public Shape{ // not technically a shape as has no material

public:
	// Constructors
	BoundingBox():
		min(Vec3f(INFINITY, INFINITY, INFINITY)),
		max(Vec3f(-INFINITY, -INFINITY, -INFINITY)){};
    // min is min corner of BoundingBox, max is max corner, material is irrelevant
	BoundingBox(Vec3f min, Vec3f max):
		Shape(nullptr,getBoundingBox()) {
            this->min = min;
			this->max = max;
		}

	Hit intersect(Ray ray);

	void getUV(Vec3f p, float& u, float& v){};

    void add(BoundingBox* box);

	void add(Vec3f p);

	BoundingBox* getBoundingBox() {
		return this;
	}

	bool contains(Vec3f p); // return true if box contains point p

	bool contains(BoundingBox* box); // return true if this box contains provided bounding box

private:
	Vec3f min;
    Vec3f max;
};



} //namespace rt
