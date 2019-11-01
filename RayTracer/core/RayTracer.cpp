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
Vec3f RayTracer::rayTrace(Scene* scene, Ray ray, int nbounces, int nsamples, bool random) {
	Hit h = getIntersection(scene, ray);
	if (h.itsct) {
		Material* m = h.mat;
		return m->shade(scene, h, nbounces, nsamples, random);
	} else {
		return scene->getBackgroundColour();
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
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces, int nsamples, bool random){
	int width = camera->getWidth();
	int height = camera->getHeight();
	float aspect = (float)width / height;

	int camerasamples = camera->distributed() ? nsamples : 1; // sample only once if camera is pinhole

	Vec3f* pixelbuffer = new Vec3f[width*height];

	Vec3f* start = pixelbuffer;

	std::size_t n = width * height;
	std::size_t cores = std::thread::hardware_concurrency();
	std::vector<std::future<void>> future_vector;

	for (std::size_t i(0); i < cores; i++)
	    future_vector.emplace_back(std::async([=, &scene]() {
            for (std::size_t index(i); index < n; index += cores) {
				int x_r = index % height;
				int y_r = index / width;
				//std::printf("%u %u \n", y_r, x_r );
				if (index % 10 == 0) {
					printf("\r%.0f%% completed", (float)((y_r*width + x_r)*100)/(width*height));
				}

				// // get normalized device coordinates for pixel
				float x_ndc = (x_r + 0.5) / width;
				float y_ndc = (y_r + 0.5) / height;

				// /* Get camera space coordinates for pixel. Multiply x by aspect ratio
				// to ensure pixels remain square. Multiply by tangent to account for fov,
				// assuming camera is one unit from sensor */
				float t_fov = tan(camera->getFov() / 2 * M_PI / 180);
				float x_w = (2 * x_ndc - 1) * t_fov * aspect;
				float y_w = 1 - (2 * y_ndc * t_fov);

				/* Camera position and pixel position in camera space, assuming
				camera is located at origin and facing along negative z axis */
				Matrix44f cameraToWorld = camera->getCameraToWorld();

				float grid_step = 1 / std::sqrt(camerasamples); // initialize step distance for grid
		        int grid_width = std::sqrt(camerasamples);

				// randomly sample lens uniformly
				Vec3f total_light = Vec3f(0);
				float focalDepth = camera->getFocus();
				for (int s = 0; s < camerasamples; s++) {
					Vec3f direction;
					Vec3f origin = Vec3f(0);
					Vec3f offset;
					if (random) {
						offset = camera->getPosition(); // offset from origin in camera space
					} else {
		                int x = s % grid_width; // sample grid x coordinate
		                int y = s / grid_width; // sample grid y coordinate
		                Vec2f x_bounds = Vec2f(x*grid_step,(x+1)*grid_step);
		                Vec2f y_bounds = Vec2f(y*grid_step,(y+1)*grid_step);
		                offset = camera->getPosition(x_bounds,y_bounds);
		            }
					cameraToWorld.multVecMatrix(origin+offset,origin); // transform origin
					cameraToWorld.multDirMatrix(Vec3f(x_w,y_w,-1),direction); // transform ray through pixel

					direction *= focalDepth;
					direction = direction - offset;
					direction = direction.normalize();

					Ray ray = {PRIMARY,origin,direction};
					Vec3f light = rayTrace(scene, ray, nbounces, nsamples, random); // trace ray and save result to pixel
					total_light = light + total_light;
				}
				float d = 1/(float)camerasamples;
				pixelbuffer[index] = d * total_light; // trace ray and save result to pixel
            }
		}));
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
