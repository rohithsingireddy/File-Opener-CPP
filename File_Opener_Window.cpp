#include "File_Opener_Window.h"
#include "resources.c"

File_Opener_Window::File_Opener_Window(
    BaseObjectType *cobject,
    const Glib::RefPtr<Gtk::Builder> &refBuilder)
    : Gtk::ApplicationWindow(cobject),
      m_refBuilder(refBuilder)
{
}

File_Opener_Window *File_Opener_Window::create()
{
    auto refBuilder = Gtk::Builder::create_from_resource("/org/mt/fileopener/window.ui");

    auto window = Gtk::Builder::get_widget_derived<File_Opener_Window>(refBuilder, "app_window");
    if(!window)
    {
        throw std::runtime_error("No \"app_window\" object in window.ui");
    }
    return window;
}

void File_Opener_Window::open_file_view(const Glib::RefPtr<Gio::File> &)
{
}