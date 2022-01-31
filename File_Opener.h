#ifndef GTK_FILE_OPENER_INCLUDE_GUARD
#define GTK_FILE_OPENER_INCLUDE_GUARD

#include <gtkmm/application.h>

class File_Opener_Window;

class File_Opener : public Gtk::Application
{
private:
    File_Opener_Window *create_appwindow();
    void on_hide_window(Gtk::Window *window);
    void on_action_preferences();
    void on_action_quit();

protected:
    File_Opener();

    void on_startup() override;
    void on_activate() override;
    void on_open(
        const Gio::Application::type_vec_files &files,
        const Glib::ustring &hint) override;

public:
    static Glib::RefPtr<File_Opener> create();
};

#endif /* GTK_FILE_OPENER_INCLUDE_GUARD */