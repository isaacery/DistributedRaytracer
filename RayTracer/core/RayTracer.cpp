/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"

namespace rt{

/* Returns the closest intersection between ray and a shape in the scene */
Hit* RayTracer::getIntersection(Scene* scene, Ray ray) {
	Hit* i; // current intersection
	Hit c = {.t = -1};
	Hit* closest = &c; // current closest intersection TODO: what to set this to
	for (auto s : scene->getShapes()) { // check all shapes for intersection
		i = s->intersect(ray);
		/* if intersection is closer than previous and greater than
		zero update closest intersection */
		// TODO: will t always be a number? What if no intersection occurs?
		if (i->t < closest->t && i->t > 0) {
			closest = i;
		}
	}
	return closest;
}

/* Returns the resulting r,g,b value from recursively tracing ray */
Vec3f RayTracer::rayTrace(Scene* scene, Ray ray, int nbounces) {
	Hit* h = getIntersection(scene, ray);
	Material* m = h->mat;
	return m->shade(scene, h, nbounces); // TODO: should I recurse?
}


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
	int x_r, y_r;
	float x_ndc, y_ndc, x_w, y_w, t_fov;
	Vec3f origin, pixel, origin_world, pixel_world, direction;
	Ray ray;

	int width = camera->getWidth();
	int height = camera->getHeight();
	float aspect = (float)width / height;

	Vec3f* pixelbuffer = new Vec3f[width*height];

	for (int y_r = 0; y_r < height; y_r++) { // loop through pixels in buffer
		for (int x_r = 0; x_r < width; x_r++) {

			// get normalized device coordinates for pixel
			x_ndc = (x_r + 0.5) / width;
			y_ndc = (y_r + 0.5) / height;

			/* Get camera space coordinates for pixel. Multiply x by aspect ratio
			to ensure pixels remain square. Multiply by tangent to account for fov,
			assuming camera is one unit from sensor */
			t_fov = tan((float)camera->getFov()/2);
			x_w = (2 * x_ndc - 1) * aspect * t_fov;
			y_w = 1 - 2 * y_ndc * t_fov;

			/* Camera position and pixel position in camera space, assuming
			camera is located at origin and facing along negative z axis */
			origin = Vec3f(0,0,0);
			pixel = Vec3f(x_w,y_w,-1);

			Matrix44f cameraToWorld = camera->getCameraToWorld();

			// apply cameraToWorld matrix to convert camera space coords to world space
			cameraToWorld.multVecMatrix(origin,origin_world);
			cameraToWorld.multVecMatrix(pixel,pixel_world);

			direction = pixel_world - origin_world; // ray direction

			Ray ray = {PRIMARY,origin,direction};
			*(pixelbuffer++) = rayTrace(scene, ray, nbounces); // trace ray and save result to pixel
		}
	}
	return pixelbuffer;
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
