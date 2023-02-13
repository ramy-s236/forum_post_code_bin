
#include <iostream>
#include <gtkmm.h>
#include <exception>

#include "sample_window.h"


int main (
       int argc,
       char **argv)
{
   int result = 0;

   Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.bug_sample_app");
   sample_window sample_window_i;
   result = app->run(sample_window_i);

   return result;
}


