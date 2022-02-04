#include "Custom_Text_View.h"

Custom_Text_View::Custom_Text_View(Glib::RefPtr<Gio::File> file)
    : file_pointer(file),
        old_etag(""),
        new_etag("")
{

}

void Custom_Text_View::set_file_pointer(Glib::RefPtr<Gio::File> file)
{
    file_pointer = file;
}

Glib::RefPtr<Gio::File> Custom_Text_View::get_file_pointer()
{
    return file_pointer;
}
