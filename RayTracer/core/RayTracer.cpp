/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"

namespace rt{


/**
 * Performs ray tracing to render a photorealistic scene
 *
 * @param camera the camera viewing the scene
 * @param scene the scene to render, including objects and lightsources
 * @param nbounces the number of bounces to consider for raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces){
	int h, w;
	float h_d, w_d;

	int width = camera->getWidth();
	int height = camera->getHeight();

	// Increment values used for translating between camera and world space
	int w_inc = 2 / ((float)width);
	int h_inc = 2 / ((float)height);

	Vec3f* pixelbuffer=new Vec3f[width*height];
	for (int i = 0; i < width*height; i++) { // loop through pixels in buffer
			// Get width and height in image
			h = i / width;
			w = i % width;
			// Get x and y coordinates of sensor pixel in world space
			x = (w_unit * (w+1)) -1;
			y = 1 - (h_unit * (h+1));
			// Set up vectors for ray
			Vec3f origin = new Vec3f(0,0,0);
			Vec3f direction = new Vec3f(x,y,0);

			ray = Ray(PRIMARY,origin,direction);
			pixelbuffer[i] = rayTrace(ray); // trace ray
	}
	return pixelbuffer;
}

Vec3f rayTrace(Scene* scene, Ray ray, int nbounces) {
	for s in scene.getShapes() { // check all objects for intersection
		i = s.intersect(ray);
		if (i.itsct) {

		}
	}
}

Hit intersection(Scene* scene, Ray ray) {
	for Shape s in scene.
}

/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer){

	//---------tonemapping function to be filled--------





	return pixelbuffer;

}





} //namespace rt
