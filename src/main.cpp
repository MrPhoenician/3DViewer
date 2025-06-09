#include "controller/Controller.h"
#include "desktop/View.h"

using namespace s21;

int main(int argc, char *argv[]) {
  Controller controller;
  QtView startApp(&controller, argc, *argv);

  return startApp.startView();
}
