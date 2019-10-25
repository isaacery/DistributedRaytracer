/*
 * main.cpp
 *
 */

#include <iostream>
#include <fstream>
#include <chrono>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "math/geometry.h"
#include "parsers/PPMWriter.h"

#include "core/RayTracer.h"
#include "core/Camera.h"
#include "core/Scene.h"

#include "core/Parser.h"

#include "lights/PointLight.h"
#include "cameras/Pinhole.h"
#include "shapes/Sphere.h"
#include "shapes/Triangle.h"
#include "shapes/Plane.h"
#include "shapes/TriMesh.h"
#include "materials/BlinnPhong.h"

using std::string;
using namespace rt;
using namespace rapidjson;
using namespace std::chrono;

int main(int argc, char* argv[]){

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
	Camera* camera = Camera::createCamera(d["camera"]);

	// print camera data (based on the input file provided)
	camera->printCamera();

	// generate the scene according to the input file
	Scene* scene = Parser::parseScene(d["scene"]);

	int nsamples = 1;
	if (d.HasMember("nsamples")){
		nsamples = d["nsamples"].GetInt();
	}

	auto start = high_resolution_clock::now(); // measure start time of render
	// Main function, render scene
	Vec3f* pixelbuffer = RayTracer::render(camera, scene, d["nbounces"].GetInt(), nsamples);
	auto stop = high_resolution_clock::now(); // measure stop time of render
	float duration = duration_cast<milliseconds>(stop - start).count()/(float)1000;
	printf("Rendering completed in %0.2f seconds\n", duration);
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
}
