#ifndef GTK_FILE_OPENER_INCLUDE_GUARD
#define GTK_FILE_OPENER_INCLUDE_GUARD

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class File_Opener : public Gtk::Window
{
public:
    File_Opener();
    ~File_Opener() override;
protected:
    void on_button_clicked();
    Gtk::Button m_button;
};

#endif