/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "math/geometry.h"
#include "core/Scene.h"
#include "core/RayHitStructs.h"
#include "core/RayTracer.h"
#include "rapidjson/document.h"

namespace rt{

class Scene;

class Material{
public:
    Material(){};

    Material(Vec3f colour): colour(colour){};
    // shade material based on scene and intersection h
    virtual Vec3f shade(Scene* scene, Hit h, int nbounces) = 0;

    virtual void print() = 0; // output information about material
protected:
    Vec3f colour;
};


} //namespace rt



#endif /* MATERIAL_H_ */
