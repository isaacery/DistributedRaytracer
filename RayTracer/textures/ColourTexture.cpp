#include "ColourTexture.h"

namespace rt {

void ColourTexture::createColourTexture(Value& textureSpecs) {
    float r = textureSpecs["colour"][0].GetFloat();
    float g = textureSpecs["colour"][1].GetFloat();
    float b = textureSpecs["colour"][2].GetFloat();
    colour = Vec3f(r,g,b);
}

Vec3f ColourTexture::value(float u, float v, Vec3f point) {
    return colour;
}

} // namespace rt
