#include <gtkmm/application.h>
#include "File_Opener.cpp"

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create("org.mt.fileopener");
    return app->make_window_and_run<File_Opener>(argc, argv);
}
