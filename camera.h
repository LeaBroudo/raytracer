#ifndef CAMERAH
#define CAMERAH
#include "ray.h"
#include "random.h"

class camera {
public:
    camera(vec3 og, vec3 visTo, vec3 ogUp, float vfov, float aspect, float aperture, float focus) {
        
        //Get ratios
        float angle = (M_PI/180) * vfov;
        float height_mid = tan(angle/2);
        float width_mid = aspect * height_mid;
        lens_rad = aperture/2;

        //vectors
        vec3 w = unit_vector(og - visTo);
        vec3 u = unit_vector(cross(ogUp, w));
        vec3 v = cross(w,u);
        
        //Create Dimensions
        orig = og;
        ll_corner = orig - (width_mid * u * focus) - (height_mid * v * focus) - (focus * w);
        horiz = 2 * width_mid * u;
        vert = 2 * height_mid * v;
    }

    vec3 orig;
    vec3 ll_corner;
    vec3 horiz, vert;
    vec3 u, v, w;  
    float lens_rad;
    
    ray get_ray(float s, float t) {
        
        vec3 rd = lens_rad * rand_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        
        vec3 A = orig + offset;
        vec3 B = ll_corner + s*horiz + t*vert - orig - offset;
        
        return ray(A, B);
    }

};

#endif