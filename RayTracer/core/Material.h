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

namespace rt{

class Scene;

class Material{
public:
    // shade material based on scene and intersection h
    virtual Vec3f shade(Scene* scene, Hit* h) = 0;

private:
    Vec3f colour;
};


} //namespace rt



#endif /* MATERIAL_H_ */
