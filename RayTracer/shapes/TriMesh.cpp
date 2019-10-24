/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"

namespace rt{

void TriMesh::createTriMesh(Value& shapeSpecs) {
    Value trianglesSpecs = shapeSpecs["triangles"].GetObject();
    if (trianglesSpecs.IsArray()) {
        Triangle* triangle;
        for (SizeType i = 0; i < trianglesSpecs.Size(); i++) {
            triangle = new Triangle();
            Value triangleSpecs = trianglesSpecs[i].GetObject();
            triangle->createTriangle(triangleSpecs);
            triangles.push_back(triangle);
        }
    }
}

Hit TriMesh::intersect(Ray ray) {
    Hit closest;
    closest.itsct = false;
    closest.t = INFINITY;
    for (Triangle* tri : triangles) {
        Hit i = tri->intersect(ray);
        if (i.itsct && i.t < closest.t) {
            closest = i;
        }
    }
    return closest;
}




} //namespace rt
