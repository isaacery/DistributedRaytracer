/*
 * Scene.cpp
 *
 */
#include "Scene.h"




namespace rt{

/**
 * Parses json scene object to generate scene to render
 *
 * @param scenespecs the json scene specificatioon
 */
void Scene::createScene(Value& scenespecs){
	//----------parse json object to populate scene-----------

}

std::vector<Shape*> getShapes() {
    return this->shapes;
}

std::vector<LightSource*> getLightSources() {
    return this->lightSources;
}

} //namespace rt
