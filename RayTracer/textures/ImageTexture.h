#ifndef IMAGETEXTURE_H_
#define IMAGETEXTURE_H_

#include "core/Texture.h"
using std::string;
using namespace rapidjson;
namespace rt {

class ImageTexture:public Texture {
public:
    // constructor
    ImageTexture():Texture(){};
    ImageTexture(Vec3f* img, int width, int height): img(img), width(width), height(height){};

    void createImageTexture(Value& textureSpecs);

    Vec3f value(float u, float v, Vec3f point) const;

private:
    Vec3f* img; // image data
    int width; // width of image
    int height; // height of image

    void loadImg(string path);
};

} // namespace rt

#endif /* IMAGETEXTURE_H_ */
