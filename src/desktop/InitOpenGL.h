#ifndef CPP4_3DVIEWER_INITOPENGL_H
#define CPP4_3DVIEWER_INITOPENGL_H

#include <QOpenGLExtraFunctions>

#include "Singleton.h"

namespace s21 {

class InitOpenGL : public QOpenGLExtraFunctions, public Singleton<InitOpenGL> {
  friend class Singleton<InitOpenGL>;

 public:
  void initialize();

 private:
  InitOpenGL();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_INITOPENGL_H
