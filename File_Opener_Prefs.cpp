#include "File_Opener_Prefs.h"
#include "File_Opener_Window.h"

File_Opener_Prefs::File_Opener_Prefs(
    BaseObjectType *cobject,
    const Glib::RefPtr<Gtk::Builder> &refBuilder)
    : Gtk::Dialog(cobject),
      m_refBuilder(refBuilder),
      m_settings(),
      m_font(nullptr),
      m_transition(nullptr)
{
    m_font = m_refBuilder->get_widget<Gtk::FontButton>("font");
    if(!m_font)
    {
        throw std::runtime_error("No \"font\" object in prefs.ui");
    }

    m_transition = m_refBuilder->get_widget<Gtk::ComboBoxText>("transition");
    if(!m_transition)
    {
        throw std::runtime_error("No \"transition\" object in prefs.ui");
    }

    m_settings = Gio::Settings::create("org.mt.fileopener");
    m_settings->bind("font", m_font->property_font());
    m_settings->bind("transition", m_transition->property_active_id());
}

File_Opener_Prefs *File_Opener_Prefs::create(Gtk::Window &parent)
{
    auto refBuilder = Gtk::Builder::create_from_resource("/org/mt/fileopener/prefs.ui");
    auto dialog = Gtk::Builder::get_widget_derived<File_Opener_Prefs>(refBuilder, "prefs_dialog");
    if(!dialog)
    {
        throw std::runtime_error("No \"prefs_dialog\" object in prefs.ui");
    }
    dialog->set_transient_for(parent);
    return dialog;
}