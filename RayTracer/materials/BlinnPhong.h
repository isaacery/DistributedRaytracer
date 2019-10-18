/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "core/Material.h"

namespace rt{

class BlinnPhong: public Material{
public:
    // constructor
    BlinnPhong(float specular, float alpha, float diffuse, float ambient, Vec3f colour):
        specular(specular), alpha(alpha), diffuse(diffuse), ambient(ambient),
        colour(colour), reflectance(reflectance) {};

    // setters and getters TODO: do we need these?
    float getSpecular() const {
        return specular;
    }

    void setSpecular(float specular) {
        this->specular = specular;
    }

    float getAlpha() const {
        return alpha;
    }

    void setAlpha(float alpha) {
        this->alpha = alpha;
    }

    float getDiffuse() const {
        return diffuse;
    }

    void setDiffuse(float diffuse) {
        this->diffuse = diffuse;
    }

    float getReflectance() const {
        return reflectance;
    }

    void setReflectance(float reflectance) {
        this->reflectance = reflectance;
    }

    Vec3f shade(Scene* scene, Hit h);

private:
    // TODO: do we always have specular + diffuse = 1?
    float specular; // in range [0,1], determines how specular material is
    float diffuse; // in range [0,1], determines how diffuse material is
    float ambient; // ambient shading of material
    float alpha; // exponent used for specular shading
    float reflectance;
};



} //namespace rt



#endif /* BLINNPHONG_H_ */
