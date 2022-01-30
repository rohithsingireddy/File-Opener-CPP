#ifndef GTK_FILE_OPENER_WINDOW_GUARD
#define GTK_FILE_OPENER_WINDOW_GUARD

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>

class File_Opener_Window : public Gtk::ApplicationWindow
{
public:
    File_Opener_Window(
        BaseObjectType *cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder);

    static File_Opener_Window *create();
    void open_file_view(const Glib::RefPtr<Gio::File> &file);

protected:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
};

#endif /* GTK_FILE_OPENER_WINDOW_GUARD */