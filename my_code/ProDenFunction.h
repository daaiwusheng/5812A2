//
// Created by 王宇 on 2022/1/25.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_PRODENFUNCTION_H
#define RAYTRACERENDERWINDOWRELEASE_PRODENFUNCTION_H

#include "../Cartesian3.h"
#include "utility.h"
#include "OrthonormalBasis.h"
#include "HittableObject.h"

class ProDenF {
public:
    virtual ~ProDenF();
    virtual double value(const Cartesian3& direction) const = 0;
    virtual Cartesian3 generate() const = 0;
};

class CosineProDenF : public ProDenF {
public:
    CosineProDenF(const Cartesian3& w);

    virtual double value(const Cartesian3& direction) const override;

    virtual Cartesian3 generate() const override;

public:
    OrthonormalBasis uvw;
};


class hittable_pdf : public ProDenF {
public:
    hittable_pdf(shared_ptr<HittableObject> p, const Cartesian3& origin);

    virtual double value(const Cartesian3& direction) const override;

    virtual Cartesian3 generate() const override;

public:
    Cartesian3 o;
    shared_ptr<HittableObject> ptr;
};

#endif //RAYTRACERENDERWINDOWRELEASE_PRODENFUNCTION_H
