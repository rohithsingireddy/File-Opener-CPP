#include <gtkmm/application.h>
#include "File_Opener.h"

File_Opener::File_Opener() : m_button("Open")
{
    m_button.set_margin(5);
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &File_Opener::on_button_clicked));
    set_child(m_button);
}

File_Opener::~File_Opener() {}

void File_Opener::on_button_clicked()
{
    char temp[] = "Where will this print?";
    printf("%.*s\n", (int)sizeof(temp) * 8, temp);
}


int main(int argc, char **argv)
{
    auto app = Gtk::Application::create("org.mt.fileopener");
    return app->make_window_and_run<File_Opener>(argc, argv);
}

