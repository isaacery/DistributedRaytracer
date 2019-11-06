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

    Vec3f out_reflective = Vec3f(0); // colour out due to reflection

    // total intensity, initialized to ambient light contribution
    float i_p = k_a * scene->getAmbientLight();

    /* shade using phong shading */
    for (LightSource* l : scene->getLightSources()) {
        float i_p_sum = 0; // total contribution of light l over nsamples samples
        Vec3f out_reflective_sum = Vec3f(0); // total reflective contribution of light l over nsamples samples
        int lightsamples = l->distributed() ? nsamples : 1; // only sample distributed lightsources

        float grid_step = 1 / std::sqrt(lightsamples); // initialize step distance for grid
        int grid_width = std::sqrt(lightsamples);
        for (int i = 0; i < lightsamples; i++) { // sample lightsource nsamples times
            Vec3f light_v;
            Vec2f x_bounds = Vec2f(0);
            Vec2f y_bounds = Vec2f(0);
            if (random) {
                light_v = l->vFrom(h.point);
            } else {
                int x = i % grid_width; // sample grid x coordinate
                int y = i / grid_width; // sample grid y coordinate
                Vec2f x_bounds = Vec2f(x*grid_step,(x+1)*grid_step);
                Vec2f y_bounds = Vec2f(y*grid_step,(y+1)*grid_step);
                light_v = l->vFrom(h.point,x_bounds,y_bounds);
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
            i_p_sum += (l->getIntersity() * k_d * std::max(0.f,(light_dir).dotProduct(n))) * d_m; // diffuse contribution
            if (nbounces > 1 && r > 0) { // specular reflection contribution
                Vec3f reflect_dir = (dir - 2 * dir.dotProduct(n) * n).normalize();
                Ray ray_out = {SECONDARY,h.point+EPSILON*reflect_dir,reflect_dir}; // cast reflection ray
                out_reflective_sum = out_reflective_sum + r * RayTracer::rayTrace(scene,ray_out,nbounces-1,nsamples,random);
            }
            i_p_sum += l->getIntersity() * k_s * std::pow(std::max(0.f,
                    light_reflection_dir.dotProduct(-dir)), alpha) * d_m; // specular contribution
            //}
        }
        i_p += i_p_sum / lightsamples; // average over samples
        out_reflective = out_reflective + out_reflective_sum * (1 / (float)lightsamples); // average over samples
    }
    /* calculate texture coordinates */
    float u = 0;
    float v = 0;
    h.shape->getUV(h.point,u,v);

    /* get colour from texture using texture coordinates */
    Vec3f colour = texture->value(u,v,h.point);

    Vec3f out = out_reflective + i_p * colour;

    return out;
}

void BlinnPhong::print() {
    printf("Material of type BlinnPhong\n\tSpecular: %f\n\tDiffuse: %f\n\tAmbient: %f\n",
            this->specular, this->diffuse, this->ambient);
}


} //namespace rt
