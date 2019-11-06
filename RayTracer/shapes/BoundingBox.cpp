#include "BoundingBox.h"

namespace rt{

/* update bounds of bounding box to contain point p */
void BoundingBox::add(Vec3f p) {
	// find min and max of current min point, max point, and new point
	min.x = std::min(p.x,min.x);
	min.y = std::min(p.y,min.y);
	min.z = std::min(p.z,min.z);
	max.x = std::max(p.x,max.x);
	max.z = std::max(p.y,max.y);
	max.z = std::max(p.z,max.z);
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

/* add two bounding boxes together to produce a larger bounding box */
void BoundingBox::add(BoundingBox* box) {
	this->add(box->min);
	this->add(box->max);
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
