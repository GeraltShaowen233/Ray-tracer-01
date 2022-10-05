#pragma once
#include"hittable.h"
#include "MathConstants.h"

#include <memory>
#include <vector>

class hittable_list  : public hittable
{
public:
    std::vector<std::shared_ptr<hittable>> objects;
public:
    hittable_list(){}
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }
    hittable_list(std::shared_ptr<hittable> object){ add(object); }
    void clear() { objects.clear(); }

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
  
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec)const
{
    hit_record record;
    bool hit_anything = false;
    auto closest = t_max;

    for (const auto& obj : objects) 
    {
        if (obj->hit(r, t_min, closest,record)) 
        {
            
            hit_anything = true;
            closest = record.t;
            rec = record;
              
        }
    
    }

    return hit_anything;
}