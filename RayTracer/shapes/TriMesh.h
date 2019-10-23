/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include "core/Shape.h"
#include "shapes/Triangle.h"

namespace rt{

// TODO: NAIVE APPROACH

class TriMesh: public Shape{
public:
    // constructors
    TriMesh(std::vector<Triangle*> triangles, Material* material):
        Shape(material) {
            // update material of every triangle to material of mesh
            for (Triangle* tri : triangles) {
                tri->setMaterial(material);
            }
            this->triangles = triangles;
        }

    Hit intersect(Ray ray);

private:
    //std::vector<Vec3f> tInd; // triangle index, each entry point to three vertices
    std::vector<Triangle*> triangles;

};



} //namespace rt




#endif /* TRIMESH_H_ */
