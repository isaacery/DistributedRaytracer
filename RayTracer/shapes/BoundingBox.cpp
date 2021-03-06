#include "BoundingBox.h"

namespace rt{

/* update bounds of bounding box to contain point p */
void BoundingBox::add(Vec3f p) {
	// find min and max of current min point, max point, and new point
	min.x = std::min(p.x,min.x);
	min.y = std::min(p.y,min.y);
	min.z = std::min(p.z,min.z);
	max.x = std::max(p.x,max.x);
	max.y = std::max(p.y,max.y);
	max.z = std::max(p.z,max.z);
	// 	printf("%f,%f,%f\n",min.x,min.y,min.z);
	// 	printf("%f,%f,%f\n",max.x,max.y,max.z);
}

/* add two bounding boxes together to produce a larger bounding box */
void BoundingBox::add(BoundingBox* box) {
	this->add(box->min);
	this->add(box->max);
}

/* split bounding box in half along longest axis, and return results in
   left and right bounding boxes */
void BoundingBox::split(BoundingBox* left, BoundingBox* right) {
	float size_x = std::abs(min.x-max.x);
	float size_y = std::abs(min.y-max.y);
	float size_z = std::abs(min.z-max.z);

	float size_max = std::max(std::max(size_x,size_y),size_z);

	Vec3f min_mid = min;
	Vec3f max_mid = max;

	if (size_max == size_x) { // split on x axis
		min_mid.x = min.x + size_x / 2.0;
		max_mid.x = min_mid.x;
	} else if (size_max == size_y) { // split on y axis
		min_mid.y = min.y + size_y / 2.0;
		max_mid.y = min_mid.y;
	} else if (size_max == size_z) { // split on z axis
		min_mid.z = min.z + size_z / 2.0;
		max_mid.z = min_mid.z;
	}

	/* update the left right boxes */
	left->setMin(min);
	left->setMax(max_mid);
	right->setMin(min_mid);
	right->setMax(max);
}

/* intersection functon for bounding box - adapted from
   https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection */
Hit BoundingBox::intersect(Ray ray) {
	Hit h;
	h.itsct = false;

    float t_min = (this->min.x - ray.o.x) / ray.d.x;
    float t_max = (this->max.x - ray.o.x) / ray.d.x;
	if (t_min > t_max) {
		std::swap(t_min, t_max);
	}

    float min_y = (min.y - ray.o.y) / ray.d.y;
    float max_y = (max.y - ray.o.y) / ray.d.y;
	if (min_y > max_y) {
		std::swap(min_y, max_y);
	}

    if ((t_min > max_y) || (min_y > t_max)) {
		return h;
	}

    if (min_y > t_min) t_min = min_y;
	if (max_y < t_max) t_max = max_y;

    float min_z = (min.z - ray.o.z) / ray.d.z;
    float max_z = (max.z - ray.o.z) / ray.d.z;
    if (min_z > max_z) {
		std::swap(min_z, max_z);
	}

    if ((t_min > max_z) || (min_z > t_max)) {
        return h;
	}

    if (min_z > t_min) {
		t_min = min_z;
	}
    if (max_z < t_max) {
		t_max = max_z;
	}

	h.itsct = true;
    return h;
}

/* return true if box contans point p */
bool BoundingBox::contains(Vec3f p) {
	return min.x <= p.x && p.x <= max.x && min.y <= p.y && p.y <= max.y
		&& min.z <= p.z && p.z <= max.z;
}

/* return true if this box contains provided bounding box */
bool BoundingBox::contains(BoundingBox* box) {
	// return true if this box contains other box's min and max points
	return this->contains(box->min) && this->contains(box->max);
}

} // namespace rt
