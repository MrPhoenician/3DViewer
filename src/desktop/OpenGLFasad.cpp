#include "OpenGLFasad.h"

using namespace s21;

OpenGLFasad::OpenGLFasad() : openGL(OpenGL::getInstance()) {}
void OpenGLFasad::init() { openGL.init(); }
void OpenGLFasad::draw() { openGL.draw(); };