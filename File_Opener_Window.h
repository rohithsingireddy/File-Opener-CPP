#ifndef GTK_FILE_OPENER_WINDOW_GUARD
#define GTK_FILE_OPENER_WINDOW_GUARD

#include <gtkmm/applicationwindow.h>

class File_Opener_Window : public Gtk::ApplicationWindow
{
public:
    File_Opener_Window();
    void open_file_view(const Glib::RefPtr<Gio::File> &file);
};

#endif /* GTK_FILE_OPENER_WINDOW_GUARD */