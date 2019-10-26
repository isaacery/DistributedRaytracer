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
	//check if cameratype is defined

	if (!cameraSpecs.HasMember("type")){
		std::cerr<<"Camera type not specified"<<std::endl;
		exit(-1);
	}

	std::string cameraType=cameraSpecs["type"].GetString();

	//return camera object based on camera specs

	Matrix44f m = Matrix44f(1, 0, 0, 0,
						    0, 1, 0, 0,
						    0, 0, 1, 0,
						    0, 0, 0, 1).transpose();

	if (cameraType.compare("pinhole")==0){
		return new Pinhole(cameraSpecs["width"].GetInt(),
				cameraSpecs["height"].GetInt(),
				cameraSpecs["fov"].GetInt(),
				m);

	}else if (cameraType.compare("thinlens")==0){
		return new ThinLens(cameraSpecs["width"].GetInt(),
				cameraSpecs["height"].GetInt(),
				cameraSpecs["fov"].GetInt(),
				m,
				cameraSpecs["focus"].GetFloat(),
				cameraSpecs["radius"].GetFloat());
	}

	return 0;

}



} //namespace rt
