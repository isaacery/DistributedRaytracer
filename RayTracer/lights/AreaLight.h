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

const float EPSILON = 0.00001;

namespace rt{

class AreaLight:public LightSource { // Light in the shape of a quad

public:
    // constructors
    AreaLight():LightSource(){};
    AreaLight(Vec3f e0, Vec3f e1, float intensity):
        LightSource(intensity) {
            this->e0 = e0;
            this->e1 = e1;
            assert(e0.dotProduct(e1) == 0);
        }
    /*
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
    */


    void createAreaLight(Value& lightSpecs);

    Vec3f vFrom(Vec3f point) { // random sampling
        /* generate ratio values */
        float u = ((float) rand() / (RAND_MAX));
        float v = ((float) rand() / (RAND_MAX));

        /* generate random point on light */
        Vec3f position = p + u * e0 + v * e1;
        return (position - point);
    }

    Vec3f vFrom(Vec3f point, Vec2f x_bounds, Vec2f y_bounds) { // jittered grid sampling
        /* generate ratio values: x in [x_bounds.x, x_bounds.y],
                                  y in [y_bounds.x, y_bounds.y] */
        float u = x_bounds.x + ((double) rand() / (RAND_MAX/(x_bounds.y-x_bounds.x)));
        float v = y_bounds.x + ((double) rand() / (RAND_MAX/(y_bounds.y-y_bounds.x)));

        /* generate random point on light */
        Vec3f position = p + u * e0 + v * e1;
        return (position - point);
    }

    void print() {
        printf("I'm an area light!\n");
        printf("my edges are:\n");
        printf("e0: [%f, %f, %f]\n", e0.x, e0.y, e0.z);
        printf("e1: [%f, %f, %f]\n", e1.x, e1.y, e1.z);
    }

    bool distributed() {
        return true;
    }

private:
    /*     e0
       p ------->x
       |         |
    e1 |         | e2
       v		 |
       x ------- x */
    Vec3f p;
    Vec3f e0;
    Vec3f e1;
    Vec3f max; //TODO: remove
    Vec3f min;
};



} //namespace rt




#endif /* AREALIGHT_H_ */
