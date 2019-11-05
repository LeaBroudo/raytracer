#ifndef RAYH
#define RAYH
#include "vec3.h"

/*
p(t) = A + t * B
    p: 3D pos along line
    A: ray origin (t=0)
    B: ray direction
    t: parameter (float) t get diff point along ray
*/

class ray {
public:
    ray() {}
    ray(const vec3& a, const vec3& b) { 
        A = a;
        B = b; 
    }

    vec3 A;
    vec3 B;

    vec3 origin() const {
        return A;
    }
    vec3 direction() const {
        return B;
    }
    vec3 point_at_param(float t) const {
        return A + t * B; 
    }
};

#endif