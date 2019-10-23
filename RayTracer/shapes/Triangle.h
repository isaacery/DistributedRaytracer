/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"

namespace rt{

class Triangle: public Shape{

public:
    // Constructor
    Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Material* material):
        Shape(material) {
            this->v0 = v0;
            this->v1 = v1;
            this->v2 = v2;
        }

    Hit intersect(Ray ray);

private:
    Vec3f v0;
    Vec3f v1;
    Vec3f v2;

};



} //namespace rt




#endif /* TRIANGLE_H_ */
