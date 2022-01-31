#ifndef FILE_OPENER_PREFS_GUARD
#define FILE_OPENER_PREFS_GUARD

#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include <gtkmm/window.h>
#include <giomm/settings.h>
#include <gtkmm/fontbutton.h>
#include <gtkmm/comboboxtext.h>

class File_Opener_Prefs : public Gtk::Dialog
{
protected:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Glib::RefPtr<Gio::Settings> m_settings;
    Gtk::FontButton *m_font;
    Gtk::ComboBoxText *m_transition;

public:
    File_Opener_Prefs(
        BaseObjectType *cobject,
        const Glib::RefPtr<Gtk::Builder> &refBuilder);
    static File_Opener_Prefs *create(Gtk::Window &parent);
};

#endif /* FILE_OPENER_PREFS_GUARD */