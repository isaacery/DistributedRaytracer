#ifndef COLOURTEXTURE_H_
#define COLOURTEXTURE_H_

#include "core/Texture.h"

using namespace rapidjson;
namespace rt {

class ColourTexture:public Texture {
public:
    // constructor
    ColourTexture():Texture(){};
    ColourTexture(Vec3f colour): colour(colour){};

    void createColourTexture(Value& textureSpecs);

    Vec3f value(float u, float v, Vec3f point);

private:
    Vec3f colour;
};

} // namespace rt

#endif /* TEXTURE_H_ */
