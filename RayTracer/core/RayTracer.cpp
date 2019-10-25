/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"

namespace rt{

/* Returns the closest intersection between ray and a shape in the scene */
Hit RayTracer::getIntersection(Scene* scene, Ray ray) {
	Hit i; // current intersection
	Hit closest;
	closest.itsct = false;
	closest.t = INFINITY;
	for (Shape* s : scene->getShapes()) { // check all shapes for intersection
		Hit i = s->intersect(ray);
		/* if intersection occured and is closer than previous */
		if (i.itsct && i.t < closest.t) {
			closest = i;
		}
	}
	return closest;
}

/* Returns the resulting r,g,b value from recursively tracing ray */
Vec3f RayTracer::rayTrace(Scene* scene, Ray ray, int nbounces, int nsamples) {
	Hit h = getIntersection(scene, ray);
	if (h.itsct) {
		Material* m = h.mat;
		return m->shade(scene, h, nbounces, nsamples);
	} else {
		return Vec3f(0,0,0);
	}
}


/**
 * Performs ray tracing to render a photorealistic scene
 *
 * @param camera the camera viewing the scene
 * @param scene the scene to render, including objects and lightsources
 * @param nbounces the number of bounces to consider for raytracing
 * @param nsamples the number of samples to consider for distributed raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces, int nsamples){
	int x_r, y_r;
	float x_ndc, y_ndc, x_w, y_w, t_fov;
	Vec3f origin, direction;
	Ray ray;

	int width = camera->getWidth();
	int height = camera->getHeight();
	float aspect = (float)width / height;

	Vec3f* pixelbuffer = new Vec3f[width*height];

	Vec3f* start = pixelbuffer;

	for (int y_r = 0; y_r < height; y_r++) { // loop through pixels in buffer
		for (int x_r = 0; x_r < width; x_r++) {
			//std::printf("%u %u \n", y_r, x_r );

			// // get normalized device coordinates for pixel
			x_ndc = (x_r + 0.5) / width;
			y_ndc = (y_r + 0.5) / height;

			// /* Get camera space coordinates for pixel. Multiply x by aspect ratio
			// to ensure pixels remain square. Multiply by tangent to account for fov,
			// assuming camera is one unit from sensor */
			float t_fov = tan(camera->getFov() / 2 * M_PI / 180);
			float x_w = (2 * x_ndc - 1) * t_fov * aspect;
			float y_w = 1 - (2 * y_ndc * t_fov);

			/* Camera position and pixel position in camera space, assuming
			camera is located at origin and facing along negative z axis */
			Matrix44f cameraToWorld = camera->getCameraToWorld();
			cameraToWorld.multVecMatrix(Vec3f(0),origin); // transform origin
			cameraToWorld.multDirMatrix(Vec3f(x_w,y_w,-1),direction); // transform ray through pixel
			direction = direction.normalize();

			//direction = (pixel_world - origin_world).normalize(); // ray direction

			Ray ray = {PRIMARY,origin,direction};
			*(pixelbuffer++) = rayTrace(scene, ray, nbounces, nsamples); // trace ray and save result to pixel
		}
	}
	return start;
}

/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer, int len){
	for (int i = 0; i < len; i++) {
		Vec3f p = pixelbuffer[i];
		p *= 255;
		p.x = (float)std::min((int)p.x, 255);
		p.y = (float)std::min((int)p.y, 255);
		p.z = (float)std::min((int)p.z, 255);
		pixelbuffer[i] = p;
	}
	return pixelbuffer;
}





} //namespace rt
