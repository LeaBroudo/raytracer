#ifndef BOUNDNODEH
#include "ray.h"
#include "random.h"
#include "bound.h"
#include "surface.h"

int cmp_x (const void *a, const void *b) {

    surface *a_surface = *(surface **)a; 
    surface *b_surface = *(surface **)b; 

    bound left_box, right_box; 

    if (!a_surface->bounding_box(0,0,left_box) || !b_surface->bounding_box(0,0,right_box)) {
        std::cerr << "no bounding box in bounding node constructor\n";
    }

    if (left_box.min().x() < right_box.min().x()) return -1; 
    else return 1; 

}

int cmp_y (const void *a, const void *b) {

    surface *a_surface = *(surface **)a; 
    surface *b_surface = *(surface **)b; 

    bound left_box, right_box; 

    if (!a_surface->bounding_box(0,0,left_box) || !b_surface->bounding_box(0,0,right_box)) {
        std::cerr << "no bounding box in bounding node constructor\n";
    }

    if (left_box.min().y() < right_box.min().y()) return -1; 
    else return 1; 

}

int cmp_z (const void *a, const void *b) {

    surface *a_surface = *(surface **)a; 
    surface *b_surface = *(surface **)b; 

    bound left_box, right_box; 

    if (!a_surface->bounding_box(0,0,left_box) || !b_surface->bounding_box(0,0,right_box)) {
        std::cerr << "no bounding box in bounding node constructor\n";
    }

    if (left_box.min().z() < right_box.min().z()) return -1; 
    else return 1; 

}


class bound_node : public surface {
public:
    bound_node() {}
    bound_node(surface **s, int n, float t0, float t1) {
        int dim = int(3 * get_rand());

        if (dim == 0) qsort(s, n, sizeof(surface *), cmp_x); 
        else if (dim == 1) qsort(s, n, sizeof(surface *), cmp_y); 
        else qsort(s, n, sizeof(surface *), cmp_z); 

        if (n == 1) {
            l = s[0];
            r = s[0]; 
        } else if (n == 2) {
            l = s[0];
            r = s[1]; 
        } else {
            l = new bound_node(s, n/2, t0, t1); 
            r = new bound_node(s + n/2, n - n/2, t0, t1); 
        }

        bound left_box, right_box; 

        if (!l->bounding_box(t0, t1, left_box) || !r->bounding_box(t0, t1, right_box)) {
            std::cerr << "no bounding box in bounding node constructor\n";
        }

        box = parent_bound(left_box, right_box); 

    }

    inline bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
        if (box.hit(r, t_min, t_max)) {

            hit_record left_rec, right_rec; 
            
            bool left_hit = l -> hit(r, t_min, t_max, left_rec); 
            bool right_hit = l -> hit(r, t_min, t_max, right_rec); 

            if (left_hit && right_hit) {
                
                if (left_rec.t < right_rec.t) rec = left_rec; 
                else rec = right_rec; 
                return true; 

            } else if (right_hit){

                rec = right_rec;
                return true; 

            } else if (left_hit){

                rec = left_rec;
                return true; 

            }

        }
        return false; 

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