#include "ConstantTexture.h"

namespace rt {

void ConstantTexture::createConstantTexture(Value& textureSpecs) {
    float r = textureSpecs["colour"][0].GetFloat();
    float g = textureSpecs["colour"][1].GetFloat();
    float b = textureSpecs["colour"][2].GetFloat();
    colour = Vec3f(r,g,b);
}

Vec3f ConstantTexture::value(float u, float v, Vec3f point) const {
    return colour;
}

} // namespace rt
