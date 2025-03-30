cmake_minimum_required(VERSION 3.28)
project(CPP4_3DViewer C CXX)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(CPP4_3DViewer
        src/main.cpp
        src/desktop/OpenGL.cpp
        src/desktop/InitOpenGL.cpp
        src/desktop/InitOpenGL.h
        src/desktop/Singleton.h
        src/controller/Controller.cpp
        src/desktop/View.cpp
        src/api/MatrixData.cpp
        src/api/ObjData.cpp
        src/api/RawMatrixData.cpp
        src/desktop/OpenGLBuffers.cpp
        src/desktop/Shader.cpp
        src/desktop/ShaderProgram.cpp
        src/model/Model.cpp
        src/model/ObjLoader.cpp
        src/model/TransformationMatrix.cpp
        src/desktop/OpenGLFasad.cpp
        src/desktop/OpenGLFasad.h
)

target_link_libraries(CPP4_3DViewer PRIVATE Qt5::Widgets)
target_link_libraries(CPP4_3DViewer PRIVATE OpenGL::GL)
target_link_libraries(CPP4_3DViewer PRIVATE GLEW::GLEW)

set_target_properties(CPP4_3DViewer PROPERTIES AUTOMOC ON)