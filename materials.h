#ifndef MATERIALH
#define MATERIALH
#include "texture.h"
#include "random.h"

vec3 reflect(const vec3& V, const vec3& N);
bool refract(const vec3& V, const vec3& N, float n_o_t, vec3& refracted);
float schlick(float cosTheta, float refract_idx);

class material {
public:
    virtual bool scatter(
        const ray& r_in, 
        const hit_record& rec, 
        vec3& attenuation, 
        ray& scattered
    ) const = 0;

};

class lambert : public material {
public: 
    lambert(texture *a) : albedo(a) {}
    
    texture *albedo;
    
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + rand_unit_rad();
        scattered = ray(rec.p, target-rec.p);
        attenuation = albedo -> value(0,0,rec.p);

        return true;
    }
};

class metal : public material {
public:
    metal(const vec3& a, float f) : albedo(a) {
        fuzz = f < 1? f : 1; 
    }

    vec3 albedo;
    float fuzz;

    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflect_vec = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflect_vec + fuzz*rand_unit_rad());
        attenuation = albedo;
        float blackness = dot(scattered.direction(), rec.normal);

        return (blackness > 0);
    }
};

class dielectric : public material {
public:
    dielectric(float ri) : refract_idx(ri) {}

    float refract_idx;

    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        
        attenuation = vec3(1.0, 1.0, 1.0);
        vec3 reflect_vec = reflect(r_in.direction(), rec.normal);
        vec3 refract_vec;
        vec3 norm_out;
        float n_o_t;
        float reflect_prob;
        float cosTheta;
        
        //Find cos(theta) for Schlick's law
        if (dot(r_in.direction(), rec.normal) < 0) {
            norm_out = rec.normal;
            n_o_t = pow(refract_idx, -1);
            cosTheta = -1*dot(r_in.direction(), rec.normal) / r_in.direction().length();
        } else {
            norm_out = -1*rec.normal;
            n_o_t = refract_idx;
            cosTheta = refract_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }

        //Get reflection probability from Schlick
        if (refract(r_in.direction(), norm_out, n_o_t, refract_vec)) {
            reflect_prob = schlick(cosTheta, refract_idx);
        } else {
            reflect_prob = 1.0; 
        }

        //Scatter based on reflection probability 
        if (get_rand() < reflect_prob) {
            scattered = ray(rec.p, reflect_vec);
        } else {
            scattered = ray(rec.p, refract_vec);
        }

        return true;
    }
}; 

//Helper functions
vec3 reflect(const vec3& V, const vec3& N) {
    return V - 2.0*dot(V,N)*N;
}

bool refract(const vec3& V, const vec3& N, float n_o_t, vec3& refracted) {
    vec3 uv_coods = unit_vector(V);
    float dt = dot(uv_coods, N);
    float discriminant = 1.0 - pow(n_o_t, 2)*(1.0 - pow(dt, 2));

    if (discriminant > 0) {
        refracted = n_o_t*(uv_coods - N*dt) - N*sqrt(discriminant);
        return true;
    }

    return false;
}

float schlick(float cosTheta, float refract_idx) {
    float R0 = pow((1-refract_idx)/(1+refract_idx), 2);
    return R0 + (1-R0)*pow(1-cosTheta, 5);
}

#endif