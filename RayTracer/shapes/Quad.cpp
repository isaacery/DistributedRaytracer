/*
 * Sphere.cpp
 *
 *
 */
#include "Quad.h"


namespace rt{


/**
 * Computes whether a ray hit the specific instance of a quad shape and returns the hit data
 *
 * @param ray cast ray to check for intersection with shape
 *
 * @return hit struct containing intersection information
 *
 */

void Quad::createQuad(Value& shapeSpecs) {
    Material* m;

    float x = shapeSpecs["e0"][0].GetFloat();
    float y = shapeSpecs["e0"][1].GetFloat();
    float z = shapeSpecs["e0"][2].GetFloat();
    Vec3f e0 = Vec3f(x,y,z);
    x = shapeSpecs["e1"][0].GetFloat();
    y = shapeSpecs["e1"][1].GetFloat();
    z = shapeSpecs["e1"][2].GetFloat();
    Vec3f e1 = Vec3f(x,y,z);
    x = shapeSpecs["p"][0].GetFloat();
    y = shapeSpecs["p"][1].GetFloat();
    z = shapeSpecs["p"][2].GetFloat();
    Vec3f p = Vec3f(x,y,z);
    assert(e1.dotProduct(e0) == 0);
    Vec3f v0 = p;
    Vec3f v1 = p + e0;
    Vec3f v2 = p + e1;
    Vec3f v3 = p + e0 + e1;

    float u = shapeSpecs["v0_uv"][0].GetFloat();
    float v = shapeSpecs["v0_uv"][1].GetFloat();
    Vec2f v0_uv = Vec2f(u,v);
    u = shapeSpecs["v1_uv"][0].GetFloat();
    v = shapeSpecs["v1_uv"][1].GetFloat();
    Vec2f v1_uv = Vec2f(u,v);
    u = shapeSpecs["v2_uv"][0].GetFloat();
    v = shapeSpecs["v2_uv"][1].GetFloat();
    Vec2f v2_uv = Vec2f(u,v);
    u = shapeSpecs["v3_uv"][0].GetFloat();
    v = shapeSpecs["v3_uv"][1].GetFloat();
    Vec2f v3_uv = Vec2f(u,v);

    Triangle* t1 = new Triangle(v0,v0_uv,v1,v1_uv,v2,v2_uv,m);
    Triangle* t2 = new Triangle(v3,v3_uv,v1,v1_uv,v2,v2_uv,m);
    std::vector<Triangle*> tris = {t1,t2};
    this->mesh = new TriMesh(tris,m);
<<<<<<< HEAD
}

BoundingBox* Quad::getBoundingBox() {
    return mesh->getBoundingBox();
=======
    this->mesh->setBoundingBox(this->mesh->getBoundingBox());
}

BoundingBox* Quad::getBoundingBox() {
    return mesh->getBoundingBox(); // don't need bounding box
>>>>>>> textures
}

Hit Quad::intersect(Ray ray){
    return mesh->intersect(ray);
}



} //namespace rt
