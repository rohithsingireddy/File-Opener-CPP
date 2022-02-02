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
    //Contains a pointer to builder object created from prefs.ui
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    //Contains a pointer to setting object managing the settings of application
    Glib::RefPtr<Gio::Settings> m_settings;
    //Contains a pointer to font that should be used by buffer
    Gtk::FontButton *m_font;
    //Contains a pointer to transition type that should be used by m_stack
    Gtk::ComboBoxText *m_transition;

public:
    /**
    * Constructor
    */ 
    File_Opener_Prefs(
        BaseObjectType *cobject,
        const Glib::RefPtr<Gtk::Builder> &refBuilder);
    /**
     * Creates a File_Opener_Prefs object and
     * returns a pointer to that
     */ 
    static File_Opener_Prefs *create(Gtk::Window &parent);
};

#endif /* FILE_OPENER_PREFS_GUARD */