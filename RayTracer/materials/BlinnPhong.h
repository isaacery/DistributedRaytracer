/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include <map>

#include "core/Material.h"

using std::string;

namespace rt{

using namespace rapidjson;
class BlinnPhong: public Material{
public:
    // constructors
    BlinnPhong():Material(){};

    BlinnPhong(float specular, float alpha, float diffuse, float ambient, float reflectance, Texture* texture):
        Material(texture) {
            this->specular = specular;
            this->alpha = alpha;
            this->diffuse = diffuse;
            this->ambient = ambient;
            this->reflectance = reflectance;
        }

    void createBlinnPhong(Value& materialSpecs, std::map<string,Texture*>& textures);

    Vec3f shade(Scene* scene, Hit h, int nbounces, int nsamples);

    void print();

private:
    float specular; // in range [0,1], determines how specular material is
    float diffuse; // in range [0,1], determines how diffuse material is
    float ambient; // in range [0,1], determines ambient shading of material
    float alpha; // exponent used for specular shading
    float reflectance; // in range [0,1], determines reflectance of material
};



} //namespace rt



#endif /* BLINNPHONG_H_ */
