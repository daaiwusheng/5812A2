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
