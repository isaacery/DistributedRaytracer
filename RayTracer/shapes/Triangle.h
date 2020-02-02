/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"
#include "parsers/happly.h"
#include "shapes/BoundingBox.h"

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
            this->v0_uv = Vec2f(0,0);
            this->v1_uv = Vec2f(1,0);
            this->v2_uv = Vec2f(1,1);
<<<<<<< HEAD
=======
            this->setBoundingBox(this->getBoundingBox());
>>>>>>> textures
        }

    Triangle(Vec3f v0, Vec2f v0_uv, Vec3f v1, Vec2f v1_uv, Vec3f v2, Vec2f v2_uv, Material* material):
        Shape(material) {
            this->v0 = v0;
            this->v1 = v1;
            this->v2 = v2;
            this->v0_uv = v0_uv;
            this->v1_uv = v1_uv;
            this->v2_uv = v2_uv;
<<<<<<< HEAD
=======
            this->setBoundingBox(this->getBoundingBox());
>>>>>>> textures
        }

    void createTriangle(Value& shapeSpecs);

    Hit intersect(Ray ray);

    void getUV(Vec3f p, float& u, float& v);

    void barycentric(Vec3f p, float &a, float&b, float&c);

    BoundingBox* getBoundingBox();

private:
    /* v0 -- v1
        |   /
        |  /
        | /
       v2      */
    Vec3f v0;
    Vec3f v1;
    Vec3f v2;
    Vec2f v0_uv;
    Vec2f v1_uv;
    Vec2f v2_uv;
};



} //namespace rt




#endif /* TRIANGLE_H_ */
