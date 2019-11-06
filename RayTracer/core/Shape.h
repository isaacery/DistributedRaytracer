/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "core/Material.h"
#include "core/RayHitStructs.h"
#include "math/geometry.h"
#include "rapidjson/document.h"

namespace rt{

class Material;

struct Hit;

class BoundingBox;

struct Ray;

class Shape{
public:

	//
	// Constructors
	//
	Shape(){};

	Shape(Material* material, BoundingBox* boundingBox):
		material(material), boundingBox(boundingBox){};

	void setMaterial(Material* material) {
		this->material = material;
	}

	virtual ~Shape(){};

	virtual Hit intersect(Ray ray) = 0;

	virtual void getUV(Vec3f p, float& u, float& v) = 0;

	virtual BoundingBox* getBoundingBox() = 0;


protected:
	Material* material;
	BoundingBox* boundingBox;
};


} //namespace rt


#endif /* SHAPE_H_ */
