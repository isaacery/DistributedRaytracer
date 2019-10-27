#include "CheckerTexture.h"
namespace rt {

void CheckerTexture::createCheckerTexture(Value& textureSpecs, std::map<string,Texture*>& textures) {
    texture1 = textures[textureSpecs["texture1"].GetString()];
    texture2 = textures[textureSpecs["texture2"].GetString()];
}
// TODO: must parse earlier textures first
// TODO: how to use u and v?
/* alternate between textures via sin of point coordinates
   produces a checkerboard pattern */
Vec3f CheckerTexture::value(float u, float v, Vec3f point) const {
    if ((sin(10 * point.x) * sin(10 * point.y) * sin(10 * point.z)) < 0)
    	return texture1->value(u, v, point);
    else
    	return texture2->value(u, v, point);
}

} // namespace rt
