/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "core/Material.h"
#include "materials/BlinnPhong.h" // TODO: fix this horrible system
#include "core/RayHitStructs.h"
#include "rapidjson/document.h"

namespace rt{

class Material;

struct Hit;

struct Ray;

class Shape{
public:

	//
	// Constructors
	//
	Shape(){};

	Shape(Material* material): material(material){};

	void setMaterial(Material* material) {
		this->material = material;
	}

	//
	// Destructor (must be overriden in subclass)
	//
	virtual ~Shape(){};

	//
	// Shape abstract methods (to be implemented by subclasses)
	//
	virtual Hit intersect(Ray ray)=0;


protected:
	Material* material;

};


} //namespace rt


#endif /* SHAPE_H_ */
