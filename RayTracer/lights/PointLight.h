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
        return (position - point);
    }

    Vec3f vFrom(Vec3f point, float g_min, float g_max) {
        return (position - point);
    }

    void print() {
        printf("I'm a point light!\n");
        printf("My position is: [%f, %f, %f]", position.x, position.y, position.z);
    }

    bool distributed() {
        return false;
    }


private:
    Vec3f position;


};



} //namespace rt




#endif /* POINTLIGHT_H_ */
