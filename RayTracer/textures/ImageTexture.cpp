#include "ImageTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "parsers/stb_image.h"

namespace rt {

void ImageTexture::loadImg(string path) { // assumes 8 bit per channel image TODO: generalise
    int w_x = 0;
    int w_y = 0;
    int nbits = 0;
    unsigned char* img_char = stbi_load(path.c_str(),&w_x,&w_y,&nbits,3); // load image
    img = (Vec3f*)calloc(w_x*w_y,sizeof(Vec3f)); // assign memory for Vec3f image
    for (int i=0; i<w_x*w_y; i+=1) {
        float r = (float)img_char[i*3]/255.0;
        float g = (float)img_char[i*3+1]/255.0;
        float b = (float)img_char[i*3+2]/255.0;
        img[i] = Vec3f(r,g,b); // save colour as Vec3f to img array
    }
    width = w_x;
    height = w_y;
}

void ImageTexture::createImageTexture(Value& textureSpecs) {
    ImageTexture::loadImg(textureSpecs["image"].GetString());
}

// lookup pixel in image based on uv coordinates
Vec3f ImageTexture::value(float u, float v, Vec3f point) const {
    int i = width * u;
    int j = height * (1-v); // - 0.001
    i = std::min(std::max(0,i),width-1);
    j = std::min(std::max(0,j),height-1);
    return img[j*width+i];
}

} // namespace rt
