#ifndef CONSTANTTEXTURE_H_
#define CONSTANTTEXTURE_H_

#include "core/Texture.h"

using namespace rapidjson;
namespace rt {

class ConstantTexture:public Texture {
public:
    // constructor
    ConstantTexture():Texture(){};
    ConstantTexture(Vec3f colour): colour(colour){};

    void createConstantTexture(Value& textureSpecs);

    Vec3f value(float u, float v, Vec3f point) const;

private:
    Vec3f colour;
};

} // namespace rt

#endif /* CONSTANTTEXTURE_H_ */
