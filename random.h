#ifndef RANDOMH
#define RANDOMH

#include "vec3.h"
#include <cstdlib>

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

vec3 rand_unit_disk() {
    vec3 p = 2.0*vec3(get_rand(), get_rand(), 0) - vec3(1,1,0);

    while (dot(p,p) >= 1.0) {
        p = 2.0*vec3(get_rand(), get_rand(), 0) - vec3(1,1,0);
    }

    return p;
}

#endif