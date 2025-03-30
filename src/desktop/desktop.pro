QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++20
QT += opengl

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = 3DViewer
SOURCES += \
    ../main.cpp \
    View.cpp \
    ../controller/Controller.cpp \
    ../model/ObjLoader.cpp \
    Shader.cpp \
    ShaderProgram.cpp \
    OpenGLBuffers.cpp \
    OpenGL.cpp \
    OpenGLFasad.cpp \
    ../model/Model.cpp \
    ../model/TransformationMatrix.cpp \
    ../api/RawMatrixData.cpp \
    ../api/MatrixData.cpp \
    ../api/ObjData.cpp \
    InitOpenGL.cpp


HEADERS += \
    View.h \
    ../controller/Controller.h \
    ../model/ObjLoader.h \
    Shader.h \
    ShaderProgram.h \
    OpenGL.h \
    OpenGLFasad.h \
    OpenGLBuffers.h\
    ../model/Model.h\
    ../model/TransformationMatrix.h \
    ../api/ControllerApi.h \
    ../api/ModelApi.h \
    ../api/RawMatrixData.h \
    ../api/MatrixData.h \
    ../api/ObjData.h \
    InitOpenGL.h \
    Singleton.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS += -Wall -Werror -Wextra


test {

TARGET = 3DViewer_test

SOURCES =
SOURCES += \
    ../tests/test.cpp\
    ../tests/test_units.cpp\
 #   widget.cpp \
 #   controller.cpp \
    ../model/objloader.cpp \
#    shader.cpp \
 #   shaderProgram.cpp \
#    openGLbuffers.cpp \
#    OpenGL.cpp \
    ../model/Model.cpp \
    ../model/TransformationMatrix.cpp \
    ../api/RawMatrixData.cpp \
    ../api/MatrixData.cpp \
    ../api/ObjData.cpp \
 #   InitOpenGL.cpp

HEADERS =
HEADERS += \
    ../tests/test.h\
 #   widget.h \
 #   controller.h \
    ../model/objloader.h \
 #   shader.h \
 #   shaderProgram.h \
 #   OpenGL.h \
 #   openGLbuffers.h\
    ../model/Model.h\
    ../model/TransformationMatrix.h \
    ../api/ControllerApi.h \
    ../api/ModelApi.h \
    ../api/RawMatrixData.h \
    ../api/MatrixData.h \
 #   InitOpenGL.h \
    Singleton.h


QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage 
QMAKE_LFLAGS += -fprofile-arcs -ftest-coverage

LIBS += -lgtest_main -lgtest -lpthread

}