#ifndef MATERIALH
#define MATERIALH

#include "random.h"

vec3 reflect(const vec3& V, const vec3& N);


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
    lambert(const vec3& a) : albedo(a) {}
    
    vec3 albedo;
    
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.normal + rand_unit_rad();
        scattered = ray(rec.p, target);
        attenuation = albedo;

        return true;
    }
};

class metal : public material {
public:
    metal(const vec3& a) : albedo(a) {}

    vec3 albedo;

    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflect_vec = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflect_vec);
        attenuation = albedo;
        float blackness = dot(scattered.direction(), rec.normal);

        return (blackness > 0);
    }
};

//Helper functions
vec3 reflect(const vec3& V, const vec3& N) {
    return V - 2.0*dot(V,N)*N;
}
/*
inline double get_rand() {
    return rand() / (RAND_MAX + 1.0);
}

vec3 rand_unit_rad() {
    
    vec3 p = 2.0 * vec3(get_rand(), get_rand(), get_rand()) - vec3(1,1,1);

    while (p.squared_length() >= 1.0) {
        p = 2.0 * vec3(get_rand(), get_rand(), get_rand()) - vec3(1,1,1);
    }

    return p;
    
}
*/
#endif