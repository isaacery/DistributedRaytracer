/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"

using namespace rapidjson;

namespace rt{

class Triangle: public Shape{

public:
    // Constructors
    Triangle():Shape(){};

    Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Material* material):
        Shape(material) {
            this->v0 = v0;
            this->v1 = v1;
            this->v2 = v2;
        }

    void createTriangle(Value& shapeSpecs);

    Hit intersect(Ray ray);

private:
    /* v0 -- v1
        |   /
        |  /
        | /
       v2      */
    Vec3f v0;
    Vec3f v1;
    Vec3f v2;
};



} //namespace rt




#endif /* TRIANGLE_H_ */
