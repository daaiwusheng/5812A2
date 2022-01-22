//
// Created by 王宇 on 2022/1/22.
//

#include "TransformTool.h"
#include "../Quaternion.h"
#include "../Matrix4.h"

TransformTool::TransformTool() {

}

TransformTool::TransformTool(RenderParameters* renderParameters)
{
    this->renderParameters = renderParameters;
    localTransform.SetIdentity();
    scale.SetIdentity();
    rotation.SetIdentity();
}
auto TransformTool::recalculateLocalTransform() -> const Matrix4&
{
    if (renderParameters->transformHasUpdated){
        //重新计算
        resetAllMatrix();
        localTransform.SetTranslation(position);
        localTransform *= rotationMatrix;
        localTransform *= scale;
        renderParameters->transformHasUpdated = false;
        return localTransform;
    }

    return localTransform;
}

auto TransformTool::resetAllMatrix() -> void
{
    //在这里更新所有变化矩阵
    //1. scale
    auto scaleFactor = renderParameters->realScale;
    scale.SetScale(scaleFactor,scaleFactor,scaleFactor);
    //2. rotation
    rotationMatrix = renderParameters->rotationMatrix;
    //3. translation
    Cartesian3 translation = Cartesian3(renderParameters->xTranslate,renderParameters->yTranslate,0);
    position = translation;
}

auto TransformTool::getTransformMatrix() -> const Matrix4 & {
    recalculateLocalTransform();
    return localTransform;
}









