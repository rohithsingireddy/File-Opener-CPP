#include <gtkmm/textview.h>

class Custom_Text_View: public Gtk::TextView 
{
    private:
        Glib::RefPtr<Gio::File> file_pointer; // Might be bad
    public:
        std::string old_etag, new_etag;
        /**
         * Constructor with file pointer argument
         */ 
        Custom_Text_View(const Glib::RefPtr<Gio::File> file);

        /**
         * Sets the pointer to file whose 
         * contents are shown by text view
         */ 
        void set_file_pointer(const Glib::RefPtr<Gio::File> file);

        /**
         * Gets the pointer to file whose 
         * contents are shown by text view
         */ 
        Glib::RefPtr<Gio::File> get_file_pointer();
};