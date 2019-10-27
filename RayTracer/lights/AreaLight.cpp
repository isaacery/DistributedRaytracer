/*
 * AreaLight.cpp
 *
 *
 */
#include "AreaLight.h"




namespace rt{

void AreaLight::createAreaLight(Value& lightSpecs) {
	float x = lightSpecs["v0"][0].GetFloat();
	float y = lightSpecs["v0"][1].GetFloat();
	float z = lightSpecs["v0"][2].GetFloat();
	this->v0 = Vec3f(x,y,z);
    x = lightSpecs["v1"][0].GetFloat();
    y = lightSpecs["v1"][1].GetFloat();
    z = lightSpecs["v1"][2].GetFloat();
    this->v1 = Vec3f(x,y,z);
    x = lightSpecs["v2"][0].GetFloat();
    y = lightSpecs["v2"][1].GetFloat();
    z = lightSpecs["v2"][2].GetFloat();
    this->v2 = Vec3f(x,y,z);
    x = lightSpecs["v3"][0].GetFloat();
    y = lightSpecs["v3"][1].GetFloat();
    z = lightSpecs["v3"][2].GetFloat();
    this->v3 = Vec3f(x,y,z);
    this->intensity = lightSpecs["intensity"].GetFloat();
	this->updateBounds();
}


} //namespace rt
