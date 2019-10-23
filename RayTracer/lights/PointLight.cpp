/*
 * PointLight.cpp
 *
 *
 */
#include "PointLight.h"



namespace rt{

void PointLight::createPointLight(Value& lightSpecs) {
    Value& pos = lightSpecs["position"]; // parse v0
    float x = pos[0].GetFloat();
    float y = pos[1].GetFloat();
    float z = pos[2].GetFloat();
    this->position = Vec3f(x,y,z);
    this->intensity = lightSpecs["intensity"].GetFloat();
}



} //namespace rt
