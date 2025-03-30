#ifndef CPP4_3DVIEWER_SINGLETON_H
#define CPP4_3DVIEWER_SINGLETON_H

namespace s21 {

template <typename T>
class Singleton {
 protected:
  Singleton() = default;
  virtual ~Singleton() = default;

 public:
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;

  static T &getInstance() {
    static T instance;

    return instance;
  }
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_SINGLETON_H
