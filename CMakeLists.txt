cmake_minimum_required(VERSION 2.8)
project(RaytraceRenderWindowRelease)

set(CMAKE_CXX_STANDARD 11)

# 添加头文件
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.4/include/GLFW)
set(GLAD_H /usr/local/include/)
set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)
#包含上述头文件所在目录
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H})

# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(OPENMP_LIBRARIES "/usr/local/lib/") #这里写你的libomp路径, 通过brew安装的默认地址
set(OPENMP_INCLUDES "/usr/local/include")#这里写你的libomp路径

include_directories("/Users/wangyu/myownlibs/stb-master/") #换成头文件所在目录,引用外部库,不需要编译的一个开源库stb_image

message("here")
message("${CMAKE_CXX_COMPILER}")

OPTION (USE_OpenMP "Use OpenMP to enamble <omp.h>" ON)

# Find OpenMP
if(APPLE AND USE_OpenMP)
    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(OpenMP_C "${CMAKE_C_COMPILER}")
        set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp -lomp -Wno-unused-command-line-argument")
        #注意以上需要增加-Xpreprocessor 以及不能直接-llibomp 在这里不需要前缀lib只需要-lomp即可，下面相似的地方也是同个道理
        set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
        set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
        set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
        set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
        set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -lomp -Wno-unused-command-line-argument")
        set(OpenMP_CXX_LIB_NAMES "libomp" "libgomp" "libiomp5")
        set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
        set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
        set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})
    endif()
endif()

if(USE_OpenMP)
    find_package(OpenMP REQUIRED)
endif(USE_OpenMP)


if (OPENMP_FOUND)
    include_directories("${OPENMP_INCLUDES}")
    link_directories("${OPENMP_LIBRARIES}")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif(OPENMP_FOUND)


add_executable(RaytraceRenderWindowRelease main.cpp
        ArcBall.cpp
        ArcBall.h
        ArcBallWidget.cpp
        ArcBallWidget.h
        Cartesian3.cpp
        Cartesian3.h
        Homogeneous4.cpp
        Homogeneous4.h
        Matrix4.cpp
        Matrix4.h
        Quaternion.cpp
        Quaternion.h
        RaytraceRenderWidget.cpp
        RaytraceRenderWidget.h
        RenderController.cpp
        RenderController.h
        RenderParameters.h
        RenderWidget.cpp
        RenderWidget.h
        RenderWindow.cpp
        RenderWindow.h
        RGBAImage.cpp
        RGBAImage.h
        RGBAValue.cpp
        RGBAValue.h
        TexturedObject.cpp
        TexturedObject.h
        src/glad.c
        my_code/vec3.cpp my_code/vec3.h my_code/utility.cpp my_code/utility.h my_code/ray.cpp my_code/ray.h my_code/hittable_list.cpp my_code/hittable_list.h my_code/hittable.cpp my_code/hittable.h my_code/headers.h my_code/material.cpp my_code/material.h my_code/texture.cpp my_code/texture.h my_code/color.cpp my_code/color.h my_code/aabb.cpp my_code/aabb.h my_code/onb.cpp my_code/onb.h my_code/rtw_stb_image.h my_code/aarect.cpp my_code/aarect.h my_code/box.cpp my_code/box.h my_code/camera.cpp my_code/camera.h my_code/Raytracer.cpp my_code/Raytracer.h my_code/CornellBox.cpp my_code/CornellBox.h)



find_package(Qt5 COMPONENTS
        Core
        REQUIRED)

find_package(Qt5Widgets REQUIRED)

# mac下这步很重要
if (APPLE)
    target_link_libraries(RaytraceRenderWindowRelease "-framework OpenGL")
    target_link_libraries(RaytraceRenderWindowRelease "-framework GLUT")
endif()

target_link_libraries(RaytraceRenderWindowRelease
        Qt5::Core
        )
target_link_libraries(RaytraceRenderWindowRelease
        Qt5::Widgets
        )

target_link_libraries(RaytraceRenderWindowRelease
        Qt5::Gui
        )



