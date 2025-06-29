#include "OpenGLFasad.h"

using namespace s21;

OpenGLFasad::OpenGLFasad() : openGL(OpenGL::getInstance()) {}
void OpenGLFasad::init() const { openGL.init(); }
void OpenGLFasad::draw() const { openGL.draw(); }