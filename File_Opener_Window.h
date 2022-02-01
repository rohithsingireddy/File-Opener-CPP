#ifndef GTK_FILE_OPENER_WINDOW_GUARD
#define GTK_FILE_OPENER_WINDOW_GUARD

#include <iostream>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/stack.h>
#include <gtkmm/menubutton.h>
#include <giomm/settings.h>
#include <gtkmm/searchbar.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/searchentry.h>
#include <glibmm/binding.h>

class File_Opener_Window : public Gtk::ApplicationWindow
{
public:
    File_Opener_Window(
        BaseObjectType *cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder);

    static File_Opener_Window *create();
    void open_file_view(const Glib::RefPtr<Gio::File> &file);

protected:
    void on_search_text_changed();
    void on_visible_child_changed();
    
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Glib::RefPtr<Gio::Settings> m_settings;
    Glib::RefPtr<Glib::Binding> m_prop_binding;
    Gtk::Stack *m_stack;
    Gtk::MenuButton *m_gears;
    Gtk::ToggleButton *m_search;
    Gtk::SearchBar *m_searchbar;
    Gtk::SearchEntry *m_searchentry;
    
};

#endif /* GTK_FILE_OPENER_WINDOW_GUARD */