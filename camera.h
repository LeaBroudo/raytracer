#ifndef CAMERAH
#define CAMERAH
#include "ray.h"

class camera {
public:
    camera() {
        ll_corner = vec3(-2.0, -1.0, 1.0);
        horiz = vec3(4.0, 0.0, 0.0);
        vert = vec3(0.0, 2.0, 0.0);
        orig = vec3(0.0, 0.0, 0.0);
    }

    vec3 orig;
    vec3 ll_corner;
    vec3 horiz;
    vec3 vert;    
    
    ray get_ray(float u, float v) {
        vec3 A = orig;
        //vec3 B = ll_corner + u*horiz + v*vert - orig;
        vec3 B = ll_corner + u*horiz + v*vert;
        return ray(A, B);
    }

};

#endif