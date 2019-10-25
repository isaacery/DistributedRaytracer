/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"

using namespace rapidjson;

namespace rt{

class PointLight: public LightSource{

public:
    // constructor
    PointLight():LightSource(){};

    PointLight(Vec3f position, float intensity):
        LightSource(intensity) {
            this->position = position;
        }

    void createPointLight(Value& lightSpecs);

    Vec3f vFrom(Vec3f point) {
        return (position - point); //TODO: normalize?
    }

    void print() {
        printf("I'm a point light!\n");
        printf("My position is: [%f, %f, %f]", position.x, position.y, position.z);
    }

private:
    Vec3f position;


};



} //namespace rt




#endif /* POINTLIGHT_H_ */
