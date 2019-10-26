/*
 * AreaLight.h
 *
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include <random>
#include "core/LightSource.h"

using namespace rapidjson;

namespace rt{

class AreaLight:public LightSource { // Light in the shape of a quad

public:
    // constructors
    AreaLight():LightSource(){};
    AreaLight(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3, float intensity):
        LightSource(intensity) {
            this->v0 = v0;
            this->v1 = v1;
            this->v2 = v2;
            this->v3 = v3;
        }

    void createAreaLight(Value& lightSpecs);

    Vec3f vFrom(Vec3f point) {
        // generate ratio values
        float u = ((float) rand() / (RAND_MAX));
        float v = ((float) rand() / (RAND_MAX));
        // calculate edge vectors
        Vec3f e0 = v1 - v0;
        Vec3f e1 = v3 - v0;

        // generate random point on light
        Vec3f position = u * e0 + v * e1;
        return (position - point);
    }

    void print() {
        printf("I'm an area light!\n");
        printf("my vertices are:\n");
        printf("v0: [%f, %f, %f]\n", v0.x, v0.y, v0.z);
        printf("v1: [%f, %f, %f]\n", v1.x, v1.y, v1.z);
        printf("v2: [%f, %f, %f]\n", v2.x, v2.y, v2.z);
        printf("v3: [%f, %f, %f]\n", v3.x, v3.y, v3.z);
    }

    bool distributed() {
        return true;
    }

private:
    /* v0 ------ v1
       |         |
       |		 |
       v3 ------ v2 */
    Vec3f v0;
    Vec3f v1;
    Vec3f v2;
    Vec3f v3;
};



} //namespace rt




#endif /* AREALIGHT_H_ */
