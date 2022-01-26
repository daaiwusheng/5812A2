/////////////////////////////////////////////////////////////////
//
//  University of Leeds
//  COMP 5812M Foundations of Modelling & Rendering
//  User Interface for Coursework
//
//  September, 2020
//
//  -----------------------------
//  Render Controller
//  -----------------------------
//  
//  We're using the Model-View-Controller pattern
//  so most of the control logic goes here
//  which means we need a slot for substantially
//  every possible UI manipulation
//
/////////////////////////////////////////////////////////////////

#include "RenderController.h"
#include <stdio.h>

// constructor
RenderController::RenderController
        (
        // the geometric theObject to show
        TexturedObject      *newTexturedObject,
        // the render parameters to use
        RenderParameters    *newRenderParameters,
        // the render window that it controls
        RenderWindow        *newRenderWindow
        )
    :
    texturedObject  (newTexturedObject),
    renderParameters(newRenderParameters),
    renderWindow    (newRenderWindow),
    dragButton      (Qt::NoButton)
    { // RenderController::RenderController()
    
    // connect up signals to slots

    // signals for arcballs
    QObject::connect(   renderWindow->modelRotator,                 SIGNAL(RotationChanged()),
                        this,                                       SLOT(objectRotationChanged()));
    QObject::connect(   renderWindow->lightRotator,                 SIGNAL(RotationChanged()),
                        this,                                       SLOT(lightRotationChanged()));

    // signals for main widget to control arcball
    QObject::connect(   renderWindow->renderWidget,                 SIGNAL(BeginScaledDrag(int, float, float)),
                        this,                                       SLOT(BeginScaledDrag(int, float, float)));
    QObject::connect(   renderWindow->renderWidget,                 SIGNAL(ContinueScaledDrag(float, float)),
                        this,                                       SLOT(ContinueScaledDrag(float, float)));
    QObject::connect(   renderWindow->renderWidget,                 SIGNAL(EndScaledDrag(float, float)),
                        this,                                       SLOT(EndScaledDrag(float, float)));

    // signals for raytrace widget to control arcball
    QObject::connect(   renderWindow->raytraceRenderWidget,         SIGNAL(BeginScaledDrag(int, float, float)),
                        this,                                       SLOT(BeginScaledDrag(int, float, float)));
    QObject::connect(   renderWindow->raytraceRenderWidget,         SIGNAL(ContinueScaledDrag(float, float)),
                        this,                                       SLOT(ContinueScaledDrag(float, float)));
    QObject::connect(   renderWindow->raytraceRenderWidget,         SIGNAL(EndScaledDrag(float, float)),
                        this,                                       SLOT(EndScaledDrag(float, float)));

    // signal for zoom slider
    QObject::connect(   renderWindow->zoomSlider,                   SIGNAL(valueChanged(int)),
                        this,                                       SLOT(zoomChanged(int)));

    // signal for x Translate sliders
    QObject::connect(   renderWindow->xTranslateSlider,             SIGNAL(valueChanged(int)),
                        this,                                       SLOT(xTranslateChanged(int)));
    QObject::connect(   renderWindow->secondXTranslateSlider,       SIGNAL(valueChanged(int)),
                        this,                                       SLOT(xTranslateChanged(int)));

    // signal for y Translate slider
    QObject::connect(   renderWindow->yTranslateSlider,             SIGNAL(valueChanged(int)),
                        this,                                       SLOT(yTranslateChanged(int)));

    // signal for emissive lighting change
    QObject::connect(   renderWindow->emissiveLightSlider,          SIGNAL(valueChanged(int)),
                        this,                                       SLOT(emissiveLightChanged(int)));

    // signal for ambient lighting change
    QObject::connect(   renderWindow->ambientLightSlider,           SIGNAL(valueChanged(int)),
                        this,                                       SLOT(ambientLightChanged(int)));

    // signal for diffuse lighting change
    QObject::connect(   renderWindow->diffuseLightSlider,           SIGNAL(valueChanged(int)),
                        this,                                       SLOT(diffuseLightChanged(int)));

    // signal for is_specular lighting change
    QObject::connect(   renderWindow->specularLightSlider,          SIGNAL(valueChanged(int)),
                        this,                                       SLOT(specularLightChanged(int)));

    // signal for is_specular exponent change
    QObject::connect(   renderWindow->specularExponentSlider,       SIGNAL(valueChanged(int)),
                        this,                                       SLOT(specularExponentChanged(int)));

    // signal for check Box for colour choice
    QObject::connect(   renderWindow->mapUVWToRGBBox,               SIGNAL(stateChanged(int)),
                        this,                                       SLOT(mapUVWToRGBCheckChanged(int)));

    // signal for check Box for lighting
    QObject::connect(   renderWindow->lightingBox,                  SIGNAL(stateChanged(int)),
                        this,                                       SLOT(useLightingCheckChanged(int)));

    // signal for check Box for textured rendering
    QObject::connect(   renderWindow->texturedRenderingBox,         SIGNAL(stateChanged(int)),
                        this,                                       SLOT(texturedRenderingCheckChanged(int)));

    // signal for check Box for texture modulation
    QObject::connect(   renderWindow->textureModulationBox,         SIGNAL(stateChanged(int)),
                        this,                                       SLOT(textureModulationCheckChanged(int)));

    // signal for check Box for depth test
    QObject::connect(   renderWindow->depthTestBox,                 SIGNAL(stateChanged(int)),
                        this,                                       SLOT(depthTestCheckChanged(int)));

    // signal for check Box for axes
    QObject::connect(   renderWindow->showAxesBox,                  SIGNAL(stateChanged(int)),
                        this,                                       SLOT(showAxesCheckChanged(int)));

    // signal for check Box for objectsInScene
    QObject::connect(   renderWindow->showObjectBox,                SIGNAL(stateChanged(int)),
                        this,                                       SLOT(showObjectCheckChanged(int)));

    // signal for check Box for centring
    QObject::connect(   renderWindow->centreObjectBox,              SIGNAL(stateChanged(int)),
                        this,                                       SLOT(centreObjectCheckChanged(int)));

    // signal for check Box for scaling
    QObject::connect(   renderWindow->scaleObjectBox,               SIGNAL(stateChanged(int)),
                        this,                                       SLOT(scaleObjectCheckChanged(int)));

    QObject::connect(renderWindow->generateRayTraceImageButton, SIGNAL(pressed()),
                     this, SLOT(raytraceButtonClick()));
    // copy the rotation matrix from the widgets to the model
    renderParameters->rotationMatrix = renderWindow->modelRotator->RotationMatrix();
    renderParameters->lightMatrix = renderWindow->lightRotator->RotationMatrix();
    } // RenderController::RenderController()

void RenderController::raytraceButtonClick() {
    renderWindow->raytraceRenderWidget->Raytrace();
    renderWindow->ResetInterface();
}

// slot for responding to arcball rotation for theObject
void RenderController::objectRotationChanged()
    { // RenderController::objectRotationChanged()
    // copy the rotation matrix from the widget to the model
    renderParameters->rotationMatrix = renderWindow->modelRotator->RotationMatrix();
    renderParameters->transformHasUpdated = true;
    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::objectRotationChanged()

// slot for responding to arcball rotation for light
void RenderController::lightRotationChanged()
    { // RenderController::lightRotationChanged()
    // copy the rotation matrix from the widget to the model
    renderParameters->lightMatrix = renderWindow->lightRotator->RotationMatrix();
    
    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::lightRotationChanged()

// slot for responding to zoom slider
void RenderController::zoomChanged(int value)
    { // RenderController::zoomChanged()
    // compute the new scale
    float newZoomScale = pow(10.0, (float) value / 100.0);

    // clamp it
    if (newZoomScale < ZOOM_SCALE_MIN)
        newZoomScale = ZOOM_SCALE_MIN;
    else if (newZoomScale > ZOOM_SCALE_MAX)
        newZoomScale = ZOOM_SCALE_MAX;

    // and reset the value  
    renderParameters->zoomScale = newZoomScale;
    renderParameters->transformHasUpdated = true;
    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::zoomChanged()

// slot for responding to x Translate sliders
void RenderController::xTranslateChanged(int value)
    { // RenderController::xTranslateChanged()
    // reset the model's x translation (slider ticks are 1/100 each)
    renderParameters->xTranslate = (float) value / 100.0;

    // clamp it
    if (renderParameters->xTranslate < TRANSLATE_MIN)
        renderParameters->xTranslate = TRANSLATE_MIN;
    else if (renderParameters->xTranslate > TRANSLATE_MAX)
        renderParameters->xTranslate = TRANSLATE_MAX;
    renderParameters->transformHasUpdated = true;
    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::xTranslateChanged()

// slot for responding to y Translate slider
void RenderController::yTranslateChanged(int value)
    { // RenderController::tTranslateChanged()
    // reset the model's y translation (slider ticks are 1/100 each)
    renderParameters->yTranslate =  (float) value / 100.0;

    // clamp it
    if (renderParameters->yTranslate < TRANSLATE_MIN)
        renderParameters->yTranslate = TRANSLATE_MIN;
    else if (renderParameters->yTranslate > TRANSLATE_MAX)
        renderParameters->yTranslate = TRANSLATE_MAX;
    renderParameters->transformHasUpdated = true;
    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::yTranslateChanged()

// slot for responding to emissive light slider
void RenderController::emissiveLightChanged(int value)
    { // RenderController::emissiveLightChanged()
    // reset the value (slider ticks are 1/100 each)
    renderParameters->emissive = (float) value / 100.0;
    
    // clamp it
    if (renderParameters->emissive < LIGHTING_MIN)
        renderParameters->emissive = LIGHTING_MIN;
    else if (renderParameters->emissive > LIGHTING_MAX)
        renderParameters->emissive = LIGHTING_MAX;

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::emissiveLightChanged()

// slot for responding to ambient albedo slider
void RenderController::ambientLightChanged(int value)
    { // RenderController::ambientLightChanged()
    // reset the value (slider ticks are 1/100 each)
    renderParameters->ambient = (float) value / 100.0;
    
    // clamp it
    if (renderParameters->ambient < LIGHTING_MIN)
        renderParameters->ambient = LIGHTING_MIN;
    else if (renderParameters->ambient > LIGHTING_MAX)
        renderParameters->ambient = LIGHTING_MAX;
    
    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::ambientLightChanged()

// slot for responding to diffuse albedo slider
void RenderController::diffuseLightChanged(int value)
    { // RenderController::diffuseLightChanged()
    // reset the value (slider ticks are 1/100 each)
    renderParameters->diffuse = (float) value / 100.0;
    
    // clamp it
    if (renderParameters->diffuse < LIGHTING_MIN)
        renderParameters->diffuse = LIGHTING_MIN;
    else if (renderParameters->diffuse > LIGHTING_MAX)
        renderParameters->diffuse = LIGHTING_MAX;
    
    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::diffuseLightChanged()

// slot for responding to is_specular albedo slider
void RenderController::specularLightChanged(int value)
    { // RenderController::specularLightChanged()
    // reset the value (slider ticks are 1/100 each)
    renderParameters->specular = (float) value / 100.0;
    
    // clamp it
    if (renderParameters->specular < LIGHTING_MIN)
        renderParameters->specular = LIGHTING_MIN;
    else if (renderParameters->specular > LIGHTING_MAX)
        renderParameters->specular = LIGHTING_MAX;
    
    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::specularLightChanged()

// slot for responding to is_specular exponent slider
void RenderController::specularExponentChanged(int value)
    { // RenderController::specularExponentChanged()
    // reset the value (slider ticks are 1/100 each)
    renderParameters->specularExponent = pow(10.0, (float) value / 100.0);
    
    // clamp it
    if (renderParameters->specularExponent < SPECULAR_EXPONENT_MIN)
        renderParameters->specularExponent = SPECULAR_EXPONENT_MIN;
    else if (renderParameters->specularExponent > SPECULAR_EXPONENT_MAX)
        renderParameters->specularExponent = SPECULAR_EXPONENT_MAX;
    
    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::specularExponentChanged()

// slot for toggling lighting
void RenderController::mapUVWToRGBCheckChanged(int state)
    { // RenderController::mapUVWToRGBCheckChanged()
    // reset the model's flag
    renderParameters->mapUVWToRGB = (state == Qt::Checked); 

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::mapUVWToRGBCheckChanged()

// slot for toggling lighting
void RenderController::useLightingCheckChanged(int state)
    { // RenderController::useLightingCheckChanged()
    // reset the model's flag
    renderParameters->useLighting = (state == Qt::Checked); 

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::useLightingCheckChanged()

// slot for toggling textures
void RenderController::texturedRenderingCheckChanged(int state)
    { // RenderController::texturedRenderingCheckChanged()
    // reset the model's flag
    renderParameters->texturedRendering = (state == Qt::Checked); 

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::texturedRenderingCheckChanged()
    
// slot for toggling texture modulation
void RenderController::textureModulationCheckChanged(int state)
    { // RenderController::textureModulationCheckChanged()
    // reset the model's flag
    renderParameters->textureModulation = (state == Qt::Checked); 

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::textureModulationCheckChanged()
    

// slot for toggling depth test
void RenderController::depthTestCheckChanged(int state)
    { // RenderController::depthTestCheckChanged()
    // reset the model's flag
    renderParameters->depthTestOn = (state == Qt::Checked); 

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::depthTestCheckChanged()
    
// slot for toggling axes
void RenderController::showAxesCheckChanged(int state)
    { // RenderController::showAxesCheckChanged()
    // reset the model's flag
    renderParameters->showAxes = (state == Qt::Checked); 

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::showAxesCheckChanged()
    
// slot for toggling theObject
void RenderController::showObjectCheckChanged(int state)
    { // RenderController::showObjectCheckChanged()
    // reset the model's flag
    renderParameters->showObject = (state == Qt::Checked); 

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::showObjectCheckChanged()
    
// slot for toggling theObject centring
void RenderController::centreObjectCheckChanged(int state)
    { // RenderController::centreObjectCheckChanged()
    // reset the model's flag
    renderParameters->centreObject = (state == Qt::Checked); 

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::centreObjectCheckChanged()
    
// slot for toggling theObject scaling
void RenderController::scaleObjectCheckChanged(int state)
    { // RenderController::scaleObjectCheckChanged()
    // reset the model's flag
    renderParameters->scaleObject = (state == Qt::Checked);
    renderParameters->transformHasUpdated = true;
    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::scaleObjectCheckChanged()
    
// slots for responding to arcball manipulations
// these are general purpose signals which pass the mouse moves to the controller
// after scaling to the notional unit Sphere
void RenderController::BeginScaledDrag(int whichButton, float x, float y)
    { // RenderController::BeginScaledDrag()
    // depends on which button was depressed, so save that for the duration
    dragButton = whichButton;

    // now switch on it to determine behaviour
    switch (dragButton)
        { // switch on the drag button
        // left button drags the model
        case Qt::LeftButton:
            renderWindow->modelRotator->BeginDrag(x, y);
            break;
        // right button drags the light
        case Qt::RightButton:
            renderWindow->lightRotator->BeginDrag(x, y);
            break;
        // middle button drags visually
        case Qt::MiddleButton:
            break;
        } // switch on the drag button

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::BeginScaledDrag()
    
// note that Continue & End assume the button has already been set
void RenderController::ContinueScaledDrag(float x, float y)
    { // RenderController::ContinueScaledDrag()
    // switch on the drag button to determine behaviour
    switch (dragButton)
        { // switch on the drag button
        // left button drags the model
        case Qt::LeftButton:
            renderWindow->modelRotator->ContinueDrag(x, y);
            break;
        // right button drags the light
        case Qt::RightButton:
            renderWindow->lightRotator->ContinueDrag(x, y);
            break;
        // middle button drags visually
        case Qt::MiddleButton:
            break;
        } // switch on the drag button

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::ContinueScaledDrag()

void RenderController::EndScaledDrag(float x, float y)
    { // RenderController::EndScaledDrag()
    // now switch on it to determine behaviour
    switch (dragButton)
        { // switch on the drag button
        // left button drags the model
        case Qt::LeftButton:
            renderWindow->modelRotator->EndDrag(x, y);
            break;
        // right button drags the light
        case Qt::RightButton:
            renderWindow->lightRotator->EndDrag(x, y);
            break;
        // middle button drags visually
        case Qt::MiddleButton:
            break;
        } // switch on the drag button

    // and reset the drag button
    dragButton = Qt::NoButton;

    // reset the interface
    renderWindow->ResetInterface();
    } // RenderController::EndScaledDrag()

