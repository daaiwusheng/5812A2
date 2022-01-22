//
// Created by 王宇 on 2022/1/22.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_TRANSFORMTOOL_H
#define RAYTRACERENDERWINDOWRELEASE_TRANSFORMTOOL_H

#include "../RenderParameters.h"

class TransformTool{

public:
    TransformTool();
    TransformTool(RenderParameters* renderParameters);
    auto recalculateLocalTransform() -> const Matrix4&;
    auto resetAllMatrix() -> void;
    auto getTransformMatrix() -> const Matrix4&;
private:
    RenderParameters* renderParameters;
    Matrix4 scale;

    Matrix4 localTransform;
    Cartesian3 position;

    Matrix4 rotationMatrix;

    Matrix4 rotation;

};


#endif //RAYTRACERENDERWINDOWRELEASE_TRANSFORMTOOL_H
