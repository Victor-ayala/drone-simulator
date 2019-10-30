//

#include "key2drone.h"

int main(int argc, char *argv[]) {

  ros::init(argc, argv, "keyboard_controller");
  QApplication app(argc, argv);

  KeyPress window;

  window.resize(300, 150);
  window.setWindowTitle("Keyboard Controller");
  window.show();

  return app.exec();
}
