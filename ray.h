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
    ray(const vec3& a, const vec3& b, float t = 0.0) { 
        A = a;
        B = b; 
        T = t; 
    }

    vec3 A;
    vec3 B;
    float T; 

    vec3 origin() const {
        return A;
    }

    vec3 direction() const {
        return B;
    }

    float time() const {
        return T; 
    }

    vec3 point_at_param(float p) const {
        return A + p * B; 
    }
};

#endif