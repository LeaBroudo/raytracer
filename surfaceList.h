#ifndef SURFACELISTH
#define SURFACELISTH
#include "surface.h"

class surfaceList: public surface {
public:
    surfaceList() {}
    surfaceList(surface **all_surfaces, int n) {
        list = all_surfaces;
        listLen = n;
    }

    surface **list;
    int listLen;

    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const {
        hit_record tmp_rec;
        double so_far = tmax;
        bool is_hit = false;
        
        for (int i = 0; i < listLen; i++) {
            if (list[i] -> hit(r, tmin, so_far, tmp_rec)) {
                is_hit = true;
                so_far = tmp_rec.t;
                rec = tmp_rec;
            }
        }
        
        return is_hit;
    }

};

#endif