/*
 * AreaLight.h
 *
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include <random>
#include "core/LightSource.h"

namespace rt{

class AreaLight:public LightSource{

public:
    // Light in the shape of a quad
    AreaLight(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3, float intensity):
        LightSource(intensity) {
            this->v0 = v0;
            this->v1 = v1;
            this->v2 = v2;
            this->v3 = v3;
        }

    Vec3f vFrom(Vec3f point) {
        // generate ratio values
        float u = ((float) rand() / (RAND_MAX));
        float v = ((float) rand() / (RAND_MAX));
        assert(u != v);
        // calculate edge vectors
        Vec3f e0 = v1 - v0;
        Vec3f e1 = v3 - v0;
        // generate random point on light
        Vec3f position = u * e0 + v * e1;
        return (position - point);
    }

private:
    /* p0 ------ p1
       |         |
       |		 |
       p3 ------ p2 */
    Vec3f v0;
    Vec3f v1;
    Vec3f v2;
    Vec3f v3;
};



} //namespace rt




#endif /* AREALIGHT_H_ */
