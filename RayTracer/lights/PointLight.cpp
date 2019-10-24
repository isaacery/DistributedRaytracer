/*
 * PointLight.cpp
 *
 *
 */
#include "PointLight.h"



namespace rt{

void PointLight::createPointLight(Value& lightSpecs) {
    float x = lightSpecs["position"][0].GetFloat();
    float y = lightSpecs["position"][1].GetFloat();
    float z = lightSpecs["position"][2].GetFloat();
    this->position = Vec3f(x,y,z);
    this->intensity = lightSpecs["intensity"].GetFloat();
}



} //namespace rt
