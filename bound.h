#ifndef BOUNDH
#define BOUNDH
#include "ray.h"
#include "random.h"

class bound {
public:

    bound() {}
    bound(const vec3& mini, const vec3& maxi) {
        Min = mini;
        Max = maxi; 
    }

    vec3 min() {
        return Min;
    }

    vec3 max() {
        return Max;
    }

    inline bool hit(const ray& r, float t_min, float t_max) const {

        int d;
        for (d = 0; d < 3; d++) {

            float min_intersect = (Min[d] - r.origin()[d]) / r.direction()[d];
            float max_intersect = (Max[d] - r.origin()[d]) / r.direction()[d];

            float t0 = min_intersect < max_intersect? min_intersect : max_intersect; 
            float t1 = min_intersect > max_intersect? min_intersect : max_intersect; 

            t_min = t0 > t_min? t0 : t_min; 
            t_max = t1 < t_max? t1 : t_max; 

            if (t_min >= t_max) {
                return false;
            }

        }
        return true; 

    }


    vec3 Min;
    vec3 Max;

};

bound parent_bound(bound box0, bound box1) {
    vec3 min(
        box0.min()[0] < box1.min()[0]? box0.min()[0] : box1.min()[0], 
        box0.min()[1] < box1.min()[1]? box0.min()[1] : box1.min()[1],
        box0.min()[2] < box1.min()[2]? box0.min()[2] : box1.min()[2] 
    );

    vec3 max(
        box0.max()[0] > box1.max()[0]? box0.max()[0] : box1.max()[0], 
        box0.max()[1] > box1.max()[1]? box0.max()[1] : box1.max()[1],
        box0.max()[2] > box1.max()[2]? box0.max()[2] : box1.max()[2] 
    );

    return bound(min, max); 

}

#endif