#ifndef BOUNDNODEH
#include "ray.h"
#include "random.h"
#include "bound.h"
#include "surface.h"

class bound_node : public hittable {
public:
    bound_node() {}
    bound_node(surface **l, int n, float t0, float t1) {
        
    }

    inline bool hit(const ray& r, float t_min, float t_max) const {

    }

    virtual bool bounding_box(float t0, float t1, bound& b) const {
        b = box;
        return true; 
    }

    bound box;
    surface *l;
    surface *r; 

};

#endif