CONFIG += c++20
QT += widgets openglwidgets

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

SOURCES_TEST += \
    ../tests/test.cpp\
    ../tests/test_units.cpp\
    ../model/objloader.cpp \
    ../model/Model.cpp \
    ../model/TransformationMatrix.cpp \
    ../api/RawMatrixData.cpp \
    ../api/MatrixData.cpp \
    ../api/ObjData.cpp \

HEADERS_TEST += \
    ../tests/test.h\
    ../model/objloader.h \
    ../model/Model.h\
    ../model/TransformationMatrix.h \
    ../api/ControllerApi.h \
    ../api/ModelApi.h \
    ../api/RawMatrixData.h \
    ../api/MatrixData.h \
    Singleton.h

SOURCES = $$SOURCES_TEST
HEADERS = $$HEADERS_TEST

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage 
QMAKE_LFLAGS += -fprofile-arcs -ftest-coverage

LIBS += -lgtest_main -lgtest -lpthread
}