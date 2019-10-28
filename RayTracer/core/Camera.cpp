/*
 * Camera.cpp
 *
 */
#include <iostream>

#include "Camera.h"
#include "cameras/Pinhole.h"
#include "cameras/ThinLens.h"

namespace rt{

	Camera::~Camera(){};



/**
 * Factory function that returns camera subclass based on camera specifications
 *
 * @param cameraSpecs camera specifications json object
 *
 * @return camera subclass instance
 *
 */
Camera* Camera::createCamera(Value& cameraSpecs){
	// check if cameratype is defined

	if (!cameraSpecs.HasMember("type")) {
		std::cerr<<"Camera type not specified"<<std::endl;
		exit(-1);
	}

	std::string cameraType = cameraSpecs["type"].GetString();

	// return camera object based on camera specs

	Matrix44f cameraToWorld = Matrix44f(1, 0, 0, 0,
						    			0, 1, 0, 0,
						    			0, 0, 1, 3,
						    			0, 0, 0, 1).transpose();
	Matrix44f cameraToWorld;
	if (!cameraSpecs.HasMember("cameraToWorld")) {
		cameraToWorld = Matrix44f(1, 0, 0, 0,
								  0, 1, 0, 0,
								  0, 0, 1, 0,
						       	  0, 0, 0, 1).transpose(); // default to I
	} else { // get cameraToWorld matrix from input file
		float a = cameraSpecs["cameraToWorld"][0].GetFloat();
		float b = cameraSpecs["cameraToWorld"][1].GetFloat();
		float c = cameraSpecs["cameraToWorld"][2].GetFloat();
		float d = cameraSpecs["cameraToWorld"][3].GetFloat();
		float e = cameraSpecs["cameraToWorld"][4].GetFloat();
		float f = cameraSpecs["cameraToWorld"][5].GetFloat();
		float g = cameraSpecs["cameraToWorld"][6].GetFloat();
		float h = cameraSpecs["cameraToWorld"][7].GetFloat();
		float i = cameraSpecs["cameraToWorld"][8].GetFloat();
		float j = cameraSpecs["cameraToWorld"][9].GetFloat();
		float k = cameraSpecs["cameraToWorld"][10].GetFloat();
		float l = cameraSpecs["cameraToWorld"][11].GetFloat();
		float m = cameraSpecs["cameraToWorld"][12].GetFloat();
		float n = cameraSpecs["cameraToWorld"][13].GetFloat();
		float o = cameraSpecs["cameraToWorld"][14].GetFloat();
		float p = cameraSpecs["cameraToWorld"][15].GetFloat();
		cameraToWorld = Matrix44f(a, b, c, d,
								  e, f, g, h,
								  i, j, k, l,
								  m, n, o, p).transpose();
	}





	if (cameraType.compare("pinhole")==0){
		return new Pinhole(cameraSpecs["width"].GetInt(),
				cameraSpecs["height"].GetInt(),
				cameraSpecs["fov"].GetInt(),
				cameraToWorld);

	}else if (cameraType.compare("thinlens")==0){
		return new ThinLens(cameraSpecs["width"].GetInt(),
				cameraSpecs["height"].GetInt(),
				cameraSpecs["fov"].GetInt(),
				cameraToWorld,
				cameraSpecs["focus"].GetFloat(),
				cameraSpecs["radius"].GetFloat());
	}

	return 0;

}



} //namespace rt
