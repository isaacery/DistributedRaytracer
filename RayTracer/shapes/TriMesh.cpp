/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"


namespace rt{

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
