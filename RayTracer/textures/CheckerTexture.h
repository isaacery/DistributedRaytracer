#ifndef CHECKERTEXTURE_H_
#define CHECKERTEXTURE_H_

#include "core/Texture.h"

#include <map>
using std::string;

using namespace rapidjson;
namespace rt {

class CheckerTexture:public Texture {
public:
    // constructor
    CheckerTexture():Texture(){};
    CheckerTexture(Texture* texture1, Texture* texture2): texture1(texture1), texture2(texture2){};

    void createCheckerTexture(Value& textureSpecs, std::map<string,Texture*>& textures);

    Vec3f value(float u, float v, Vec3f point) const;

private:
    Texture* texture1;
    Texture* texture2;
};

} // namespace rt

#endif /* CHECKERTEXTURE_H_ */
