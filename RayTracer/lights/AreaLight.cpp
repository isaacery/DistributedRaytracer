/*
 * AreaLight.cpp
 *
 *
 */
#include "AreaLight.h"




namespace rt{

void AreaLight::createAreaLight(Value& lightSpecs) {
	float x = lightSpecs["e0"][0].GetFloat();
	float y = lightSpecs["e0"][1].GetFloat();
	float z = lightSpecs["e0"][2].GetFloat();
	this->e0 = Vec3f(x,y,z);
	x = lightSpecs["e1"][0].GetFloat();
	y = lightSpecs["e1"][1].GetFloat();
	z = lightSpecs["e1"][2].GetFloat();
	this->e1 = Vec3f(x,y,z);
	x = lightSpecs["p"][0].GetFloat();
	y = lightSpecs["p"][1].GetFloat();
	z = lightSpecs["p"][2].GetFloat();
	this->p = Vec3f(x,y,z);
	assert(e1.dotProduct(e0) == 0);
    this->intensity = lightSpecs["intensity"].GetFloat();
	// TODO this->updateBounds();
}


} //namespace rt
