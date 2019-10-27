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
#include "core/Texture.h"

namespace rt{

class Scene;

class Material{
public:
    Material(){};

    Material(Texture* texture): texture(texture){};
    // shade material based on scene and intersection h
    virtual Vec3f shade(Scene* scene, Hit h, int nbounces, int nsamples) = 0;

    virtual void print() = 0; // output information about material
protected:
    Texture* texture;
};


} //namespace rt



#endif /* MATERIAL_H_ */
