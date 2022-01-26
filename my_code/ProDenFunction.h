//
// Created by 王宇 on 2022/1/25.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_PRODENFUNCTION_H
#define RAYTRACERENDERWINDOWRELEASE_PRODENFUNCTION_H

#include "../Cartesian3.h"
#include "utility.h"
#include "OrthonormalBasis.h"
#include "HittableObject.h"

//in this file, we define some probability density functions. they can be used for Monte Carlo recursive scattering.
//honestly, this knowledge I referred online.
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


class hittableProDenF : public ProDenF {
public:
    hittableProDenF(shared_ptr<HittableObject> p, const Cartesian3& _origin);

    virtual double value(const Cartesian3& direction) const override;

    virtual Cartesian3 generate() const override;

public:
    Cartesian3 origin;
    shared_ptr<HittableObject> hittableObject;
};

class CombineProDenF : public ProDenF {
public:
    CombineProDenF(shared_ptr<ProDenF> p0, shared_ptr<ProDenF> p1);

    virtual double value(const Cartesian3& direction) const override;

    virtual Cartesian3 generate() const override;

public:
    shared_ptr<ProDenF> p[2];
};

#endif //RAYTRACERENDERWINDOWRELEASE_PRODENFUNCTION_H
