/*
 * main.cpp
 *
 */

#include <iostream>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "math/geometry.h"
#include "parsers/PPMWriter.h"

#include "core/RayTracer.h"
#include "core/Camera.h"
#include "core/Scene.h"

#include "lights/PointLight.h"
#include "cameras/Pinhole.h"
#include "shapes/Sphere.h"
#include "materials/BlinnPhong.h"

using namespace rt;
using namespace rapidjson;

bool test = true;

int main(int argc, char* argv[]){
	printf("main started\n");
	// camera
	printf("camera started\n");
	//TODO: doesn't work
	Matrix44f m = Matrix44f(1, 0, 0, 0,
	 						0, 1, 0, 0,
							0, 0, 1, 0,
						 	0, 0, 0, 1); // identity
	Camera* camera = new Pinhole(1000,1000,90,m);
	printf("camera done!\n");
	// light
	printf("light started\n");
	LightSource* light = new PointLight(Vec3f(0,0,0),1);
	std::vector<LightSource*> lights = {light};
	printf("light done!\n");
	// shape
	printf("shape started\n");
	Material* mat1 = new BlinnPhong(0.5,10,1,0,0.5,Vec3f(1,0,0));
	Material* mat2 = new BlinnPhong(0.5,10,1,0,0.5,Vec3f(1));
	Shape* sphere1 = new Sphere(Vec3f(-2,1,-5), 1, mat1);
	Shape* sphere2 = new Sphere(Vec3f(2,0,-5), 2, mat2);
	std::vector<Shape*> shapes = {sphere1,sphere2};
	printf("shape done!\n");
	// scene
	printf("scene started\n");
	Scene* scene = new Scene(lights,shapes,0.25); //TODO: intensity in [0,1]?
	printf("scene done!\n");

	printf("Rendering started\n");
	Vec3f* pixelbuffer = RayTracer::render(camera, scene, 4);

	pixelbuffer = RayTracer::tonemap(pixelbuffer,camera->getWidth()*camera->getHeight());
	char* out = "out.ppm";
	PPMWriter::PPMWriter(camera->getWidth(), camera->getHeight(), pixelbuffer, out);
	printf("Rendering completed\n");
	return 0;
	/*
	// parse commandline arguments
	char* inputFile=argv[1];  // first command line argument holds the path to the json input file
	char* outputFile=argv[2]; // second command line argument holds the path to the output image file

	printf("Input file: %s\n",inputFile);

	// parse json input file using rapidjson
	std::ifstream ifs(inputFile);
	IStreamWrapper is(ifs);
	Document d;     // d holds the complete json object
	d.ParseStream(is);

	// generate a camera according to the input file
	Camera* camera=Camera::createCamera(d["camera"]);

	// print camera data (based on the input file provided)
	camera->printCamera();

	// generate the scene according to the input file
	Scene* scene=new Scene();
	scene->createScene(d["scene"]);

	// Main function, render scene
	Vec3f* pixelbuffer = RayTracer::render(camera, scene, d["nbounces"].GetInt());

	// free resources when rendering is finished
	delete camera;
	delete scene;

	//Vec3f* pixelbuffer = RayTracer::render(camera, scene, 1);

	// convert linear RGB pixel values [0-1] to range 0-255
	pixelbuffer = RayTracer::tonemap(pixelbuffer, camera->getWidth()*camera->getHeight());

	printf("Output file: %s\n",outputFile);

	// write rendered scene to file (pixels RGB values must be in range 0255)
	PPMWriter::PPMWriter(camera->getWidth(), camera->getHeight(), pixelbuffer, outputFile);

	delete pixelbuffer;
	*/
}
