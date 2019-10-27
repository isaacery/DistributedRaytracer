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

    void updateBounds() { // update bounds for coordinates
        float max_x = max4(v0.x,v1.x,v2.x,v3.x);
        float max_y = max4(v0.y,v1.y,v2.y,v3.y);
        float max_z = max4(v0.z,v1.z,v2.z,v3.z);
        float min_x = min4(v0.x,v1.x,v2.x,v3.x);
        float min_y = min4(v0.y,v1.y,v2.y,v3.y);
        float min_z = min4(v0.z,v1.z,v2.z,v3.z);
        max = Vec3f(max_x,max_y,max_z);
        min = Vec3f(min_x,min_y,min_z);
    }

    float min4(float a, float b, float c, float d) {
        int e = a < b ? a : b;
        int f = c < d ? c : d;
        return e < f ? e : f;
    }

    float max4(float a, float b, float c, float d) {
        int e = a > b ? a : b;
        int f = c > d ? c : d;
        return e > f ? e : f;
    }


    void createAreaLight(Value& lightSpecs);

    Vec3f vFrom(Vec3f point) { // random sampling
        // generate ratio values
        float x = ((float) rand() / (RAND_MAX));
        float y = ((float) rand() / (RAND_MAX));
        float z = ((float) rand() / (RAND_MAX));
        /* generate random point on light */
        Vec3f position = Vec3f(x,y,z);
        position = position * Vec3f(max.x-min.x,max.y-min.y,max.z-min.z);
        position = position + min;

        return (position - point);
    }

    Vec3f vFrom(Vec3f point, float g_min, float g_max) { // grid sampling
        // generate ratio values
        float x = g_min + ((double) rand() / (RAND_MAX/(g_max-g_min)));
        float y = g_min + ((double) rand() / (RAND_MAX/(g_max-g_min)));
        float z = g_min + ((double) rand() / (RAND_MAX/(g_max-g_min)));
        /* generate random point on light */
        Vec3f position = Vec3f(x,y,z);
        position = position * Vec3f(max.x-min.x,max.y-min.y,max.z-min.z);
        position = position + min;
        return (position - point);

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
    Vec3f max;
    Vec3f min;
};



} //namespace rt




#endif /* AREALIGHT_H_ */
