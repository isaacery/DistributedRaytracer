/*
 * BlinnPhong.cpp
 *
 *
 */

#include "BlinnPhong.h"

namespace rt{

const float EPSILON = 0.001; // distance above surface from which to cast ray to avoid rounding errors

void BlinnPhong::createBlinnPhong(Value& materialSpecs, std::map<string,Texture*>& textures) {
    ambient = materialSpecs["ka"].GetFloat();
    specular = materialSpecs["ks"].GetFloat();
    alpha = materialSpecs["alpha"].GetFloat();
    diffuse = materialSpecs["kd"].GetFloat();
    reflectance = materialSpecs["reflectance"].GetFloat();
    texture = textures[materialSpecs["texture"].GetString()];
}

Vec3f BlinnPhong::shade(Scene* scene, Hit h, int nbounces, int nsamples, bool random) {
    float k_a = ambient;
    float k_d = diffuse;
    float k_s = specular;
    float r = reflectance;
    Vec3f n = h.n;
    Vec3f dir = h.ray_in.d;

    // total intensity, initialized to ambient light contribution
    float i_p = k_a * scene->getAmbientLight();

    /* shade using phong shading */
    for (LightSource* l : scene->getLightSources()) {
        float i_p_sum = 0; // total contribution of light l over nsamples samples
        int lightsamples = l->distributed() ? nsamples : 1; // only sample distributed lightsources

        float grid_step = 1 / (float)lightsamples; // initialize step distance for grid
        //TODO: this grid method is wrong, but works well
        for (int i = 0; i < lightsamples; i++) { // sample lightsource nsamples times
            Vec3f light_v;
            if (random) {
                light_v = l->vFrom(h.point);
            } else {
                light_v = l->vFrom(h.point,i*grid_step,(i+1)*grid_step); // sample light only within grid
            }
            Vec3f light_dir = light_v.normalize(); // get direction from intersection point to light
            float light_dist = light_v.length();
            float d_m = 1/(light_dist * light_dist); // inverse distance squared
            Vec3f light_reflection_dir = (-light_dir) - 2 * n * (-light_dir).dotProduct(n); // reflect light_dir about normal

            /* check for shadow */
            Ray shadow_ray = {SHADOW,h.point+(EPSILON*light_dir),light_dir}; // ray to cast toward light
            Hit s = RayTracer::getIntersection(scene, shadow_ray);
            if (s.itsct && s.t < light_dist) continue; // if there's a shape between point and light, skip to next light

            /* calculate diffuse and specular shading */
            i_p_sum += (l->getIntersity() * k_d * std::max(0.f,(light_dir).dotProduct(n))) * d_m; // diffuse
            i_p_sum += l->getIntersity() * k_s * std::pow(std::max(0.f,
                    light_reflection_dir.dotProduct(-dir)), alpha) * d_m; // specular
        }
        i_p += i_p_sum / lightsamples;
    }
    /* calculate texture coordinates */
    float u = 0;
    float v = 0;
    h.shape->getUV(h.point,u,v);

    /* get colour from texture using texture coordinates */
    Vec3f colour = texture->value(u,v,h.point);

    Vec3f out = i_p * colour;

    /* recursively trace ray for reflection */
    if (nbounces > 1 && r > 0) {
        Vec3f reflect_dir = (dir - 2 * dir.dotProduct(n) * n).normalize();
        Ray ray_out = {SECONDARY,h.point+EPSILON*reflect_dir,reflect_dir}; // cast reflection ray
        // interpolate between phong shaded intensity and reflection
        out = (1-r) * out  + r * RayTracer::rayTrace(scene,ray_out,nbounces-1,nsamples,random);
    }

    return out;
}

void BlinnPhong::print() {
    printf("Material of type BlinnPhong\n\tSpecular: %f\n\tDiffuse: %f\n\tAmbient: %f\n",
            this->specular, this->diffuse, this->ambient);
}


} //namespace rt
