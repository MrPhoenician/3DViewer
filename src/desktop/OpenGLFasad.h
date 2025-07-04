#ifndef CPP4_3DVIEWER_OPENGLFASAD_H
#define CPP4_3DVIEWER_OPENGLFASAD_H

#include "OpenGL.h"

namespace s21 {

class OpenGLFasad {
 private:
  OpenGL &openGL;

 public:
  OpenGLFasad();
  void init() const;
  void draw() const;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_OPENGLFASAD_H
