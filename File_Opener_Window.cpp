#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include "File_Opener_Window.h"
#include "resources.c"

File_Opener_Window::File_Opener_Window(
    BaseObjectType *cobject,
    const Glib::RefPtr<Gtk::Builder> &refBuilder)
    : Gtk::ApplicationWindow(cobject),
      m_refBuilder(refBuilder),
      m_stack(nullptr)
{
    m_stack = m_refBuilder->get_widget<Gtk::Stack>("stack");
    if (!m_stack)
    {
        throw std::runtime_error("No \"stack\" object in window.ui");
    }
}

File_Opener_Window *File_Opener_Window::create()
{
    auto refBuilder = Gtk::Builder::create_from_resource("/org/mt/fileopener/window.ui");

    auto window = Gtk::Builder::get_widget_derived<File_Opener_Window>(refBuilder, "app_window");
    if (!window)
    {
        throw std::runtime_error("No \"app_window\" object in window.ui");
    }
    return window;
}

void File_Opener_Window::open_file_view(const Glib::RefPtr<Gio::File> &file)
{
    const Glib::ustring basename = file->get_basename();
    
    auto view = Gtk::make_managed<Gtk::TextView>();
    view->set_editable(false);
    view->set_cursor_visible(false);
    view->set_margin(5);
    
    auto scrolled = Gtk::make_managed<Gtk::ScrolledWindow>();
    scrolled->set_expand(true);
    scrolled->set_child(*view);
    m_stack->add(*scrolled, basename, basename);

    try 
    {
        char *contents = nullptr;
        gsize length = 0;
        file->load_contents(contents, length);
        view->get_buffer()->set_text(contents, contents + length);
        g_free(contents);
    }
    catch(const Glib::Error &er)
    {
        std::cerr << "File_Opener_Window::open_file_view(\"" << file->get_parse_name()
                    << "\"): " << er.what() << std::endl;
    }
}