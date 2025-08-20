cmake_minimum_required(VERSION 3.28)
project(CPP4_3DViewer C CXX)

set(CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu/qt6)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets OpenGLWidgets) # for Ubuntu 24.04
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # гарантирует, что если компилятор не поддерживает C++20 — сборка прервётся с ошибкой
set(CMAKE_CXX_EXTENSIONS OFF) # отключает gnu++20, делает std=c++20
set(CMAKE_AUTOMOC ON)

add_executable(CPP4_3DViewer
        src/main.cpp
        src/desktop/View.h
        src/desktop/View.cpp
        src/desktop/OpenGL.h
        src/desktop/OpenGL.cpp
        src/desktop/InitOpenGL.h
        src/desktop/InitOpenGL.cpp
        src/desktop/Singleton.h
        src/controller/Controller.cpp
        src/desktop/OpenGLBuffers.h
        src/desktop/OpenGLBuffers.cpp
        src/desktop/Shader.h
        src/desktop/Shader.cpp
        src/desktop/ShaderProgram.h
        src/desktop/ShaderProgram.cpp
        src/model/Model.h
        src/model/Model.cpp
        src/model/ObjLoader.h
        src/model/ObjLoader.cpp
        src/model/TransformationMatrix.h
        src/model/TransformationMatrix.cpp
        src/desktop/OpenGLFasad.h
        src/desktop/OpenGLFasad.cpp
        src/api/MatrixData.h
        src/api/MatrixData.cpp
        src/api/RawMatrixData.h
        src/api/RawMatrixData.cpp
        src/api/ObjData.h
        src/api/ObjData.cpp
)

target_include_directories(CPP4_3DViewer PRIVATE src)

target_link_libraries(CPP4_3DViewer PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::OpenGLWidgets
        OpenGL::GL
        GLEW::GLEW
)