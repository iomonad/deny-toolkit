#include <gtkmm/application.h>

#include "gui.h"

int main(int argc, char** argv) {
  Glib::RefPtr<Gtk::Application> app =
      Gtk::Application::create(argc, argv, "org.gtkmm.example");
  HelloWorld helloworld;
  return app->run(helloworld);
}
