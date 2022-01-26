//
// Created by 王宇 on 2022/1/25.
//

#include "ProDenFunction.h"

ProDenF::~ProDenF() {

}

CosineProDenF::CosineProDenF(const Cartesian3 &w) {
    uvw.buildFromNormal(w);
}

double CosineProDenF::value(const Cartesian3 &direction) const {
    auto cosine = dot(unit_vector(direction), uvw.w());
    return (cosine <= 0) ? 0 : cosine/pi;
}

Cartesian3 CosineProDenF::generate() const {
    return uvw.local(randomCosineDirection());
}

hittable_pdf::hittable_pdf(shared_ptr<HittableObject> p, const Cartesian3 &origin) : ptr(p), o(origin) {

}

double hittable_pdf::value(const Cartesian3 &direction) const {
    return ptr->pdf_value(o, direction);
}

Cartesian3 hittable_pdf::generate() const {
    return ptr->random(o);
}

mixture_pdf::mixture_pdf(shared_ptr<ProDenF> p0, shared_ptr<ProDenF> p1) {
    p[0] = p0;
    p[1] = p1;
}

double mixture_pdf::value(const Cartesian3 &direction) const {
    return 0.5 * p[0]->value(direction) + 0.5 *p[1]->value(direction);
}

Cartesian3 mixture_pdf::generate() const {
    if (randomDouble() < 0.5)
        return p[0]->generate();
    else
        return p[1]->generate();
}
