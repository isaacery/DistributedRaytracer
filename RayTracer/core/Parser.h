#include <string>
#include <map>

#include "materials/BlinnPhong.h"
#include "core/Scene.h"

#include "textures/ConstantTexture.h"
#include "textures/CheckerTexture.h"
#include "textures/ImageTexture.h"

#include "cameras/Pinhole.h"

#include "lights/PointLight.h"
#include "lights/AreaLight.h"


#include "shapes/Plane.h"
#include "shapes/Sphere.h"
#include "shapes/Triangle.h"
#include "shapes/TriMesh.h"
#include "shapes/Quad.h"

using namespace rapidjson;
using std::string;

namespace rt{

class Parser{

public:

    inline static std::map<string,Material*> materials;
    inline static std::map<string,Texture*> textures;
    inline static std::vector<Shape*> shapes;
    inline static std::vector<LightSource*> lights;

    static void parseTextures(Value& texs) {
        Texture* t;
        if (texs.IsArray()) {
    		std::cout<<"Parsing "<<texs.Size()<<" textures\n";
    		for (SizeType i = 0; i < texs.Size(); i++) {
    			Value textureSpecs = texs[i].GetObject();
    			string textureType = textureSpecs["type"].GetString();
    			if (textureType.compare("constant") == 0) {
    				ConstantTexture* o = new ConstantTexture();
    				o->createConstantTexture(textureSpecs);
    				t = o;
    			} else if (textureType.compare("checker") == 0) {
                    CheckerTexture* o = new CheckerTexture();
                    o->createCheckerTexture(textureSpecs, textures);
                    t = o;
                } else if (textureType.compare("image") == 0) {
                    ImageTexture* o = new ImageTexture();
                    o->createImageTexture(textureSpecs);
                    t = o;
            }
    			textures.insert(std::pair<string,Texture*>(textureSpecs["name"].GetString(),t));
    		}
    	}
    }

    static void parseMaterials(Value& mats) {
        Material* m;
        //Value& mats = d["materials"];
        //std::map<string,Material*> materials;
        if (mats.IsArray()) {
    		std::cout<<"Parsing "<<mats.Size()<<" materials\n";
    		for (SizeType i = 0; i < mats.Size(); i++) {
    			Value materialSpecs = mats[i].GetObject();
    			string materialType = materialSpecs["type"].GetString();
    			if (materialType.compare("blinnphong") == 0) {
    				BlinnPhong* o = new BlinnPhong();
    				o->createBlinnPhong(materialSpecs, textures);
    				m = o;
    			}
    			materials.insert(std::pair<string,Material*>(materialSpecs["name"].GetString(),m));
    		}
    	}
    }

    static void parseShapes(Value& shps) {
        Shape* s;
    	//Value& shps = d["shapes"];
    	//std::vector<Shape*> shapes;
    	if (shps.IsArray()) {
    		std::cout<<"Parsing "<<shps.Size()<<" shapes\n";
    		for (SizeType i = 0; i < shps.Size(); i++) {
    			Value shapeSpecs = shps[i].GetObject();
    			string shapeType = shapeSpecs["type"].GetString();
    			if (shapeType.compare("sphere") == 0) {
    				Sphere* o = new Sphere();
    				o->createSphere(shapeSpecs);
    				s = o;
    			} else if (shapeType.compare("plane") == 0) {
    				Plane* o = new Plane();
    				o->createPlane(shapeSpecs);
    				s = o;
    			} else if (shapeType.compare("triangle") == 0) {
    				Triangle* o = new Triangle();
    				o->createTriangle(shapeSpecs);
    				s = o;
    			} else if (shapeType.compare("trianglemesh") == 0) {
    				TriMesh* o = new TriMesh();
    				o->createTriMesh(shapeSpecs);
                    o->setMaterial(materials[shapeSpecs["material"].GetString()]); // TODO: inelegant
    				s = o;
                } else if (shapeType.compare("quad") == 0) {
                    Quad* o = new Quad();
                    o->createQuad(shapeSpecs);
                    o->setMaterial(materials[shapeSpecs["material"].GetString()]); // TODO: inelegant
                    s = o;
                }
                s->setMaterial(materials[shapeSpecs["material"].GetString()]);
    			shapes.push_back(s);
    		}
    	}
    }

    static void parseLights(Value& lts) {
        LightSource* l;
        if (lts.IsArray()) {
            std::cout<<"Parsing "<<lts.Size()<<" lights\n";
            for (SizeType i = 0; i < lts.Size(); i++) {
                Value lightSpecs = lts[i].GetObject();
                string lightType = lightSpecs["type"].GetString();
                if (lightType.compare("pointlight") == 0) {
                    PointLight* o = new PointLight();
                    o->createPointLight(lightSpecs);
                    l = o;
                } else if (lightType.compare("arealight") == 0) {
                    AreaLight* o = new AreaLight();
                    o->createAreaLight(lightSpecs);
                    l = o;
                }
                lights.push_back(l);
            }
        }
    }

    /* parse scene information from raytracer input file */
    static Scene* parseScene(Value& d) {
        parseTextures(d["textures"]);
        parseMaterials(d["materials"]); // parse materials
        parseShapes(d["shapes"]); // parse shapes
        parseLights(d["lightsources"]); // parse lights
    	float r = d["backgroundcolour"][0].GetFloat(); // parse background colour
    	float g = d["backgroundcolour"][1].GetFloat();
    	float b = d["backgroundcolour"][2].GetFloat();
    	Vec3f backgroundColour = Vec3f(r,g,b);
    	float ambient = d["ambient"].GetFloat(); // parse ambient intensity

        return new Scene(lights, shapes, backgroundColour, ambient);
    }

};

} //namespace rt
