//
// Created by 王宇 on 2022/1/22.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_TRANSFORMTOOL_H
#define RAYTRACERENDERWINDOWRELEASE_TRANSFORMTOOL_H

#include "../RenderParameters.h"

//As all transform parameters are stored in RenderParameters. like rotation and scale.
//so we only need to hold renderParameters from RenderController, and when transform
//data have been updated, we set renderParameters.transformHasUpdated = true.
//then in this class we recalculate the final transform matrix.
class TransformTool{

public:
    TransformTool();
    TransformTool(RenderParameters* renderParameters);
    auto recalculateLocalTransform() -> const Matrix4&;
    auto resetAllMatrix() -> void;
    auto getTransformMatrix() -> const Matrix4&;
    RenderParameters* renderParameters;
private:

    Matrix4 scale;

    Matrix4 localTransform;
    Cartesian3 position;

    Matrix4 rotationMatrix;

    Matrix4 rotation;

};


#endif //RAYTRACERENDERWINDOWRELEASE_TRANSFORMTOOL_H
