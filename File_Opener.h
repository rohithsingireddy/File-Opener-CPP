#ifndef GTK_FILE_OPENER_INCLUDE_GUARD
#define GTK_FILE_OPENER_INCLUDE_GUARD

#include <gtkmm/application.h>
#include <gtkmm/filechooserdialog.h>

class File_Opener_Window;

class File_Opener : public Gtk::Application
{
private:
    /**
     * Creates a File_Opener_Window object and returns
     * a pointer to that object
     */ 
    File_Opener_Window *create_appwindow();

    /**
     * Deletes the window when the application is hidden 
     * from user view( Not to be confused with minimize window)
     */ 
    void on_hide_window(Gtk::Window *window);

    /**
     * Method which is bound to the preferences button on menu settings
     * Opens a Preference dialog which presents options related to presentation
     * of text in buffer.
     * Called whenever Preferences option is clicked or "<Ctrl>P" is pressed
     */ 
    void on_action_preferences();

    /**
     * Method which is bound to the quit button on menu settings
     * Called whenever Quit option is clicked or "<Ctrl>Q" is pressed
     */ 
    void on_action_quit();

    /**
     * Opens a file in the application
     */
    void open_file(); 

    /**
     * Opens the file selected through
     * FileChooserDialog
     */
    void on_file_choose(int response_id, Gtk::FileChooserDialog *dialog); 

protected:
    /**
     * Default Constructor
     */ 
    File_Opener();

    /**
     * Overriedes the parent Gtk::Application on_startup
     * and is called at startup of application before activate
     */ 
    void on_startup() override;
    
    /**
     * Overrides the parent Gtk::Application on_activate
     * and is called whenever the application is called or
     * activated
     */ 
    void on_activate() override;
    
    /**
     * Overrides the on_open function of Gtk::Application 
     * and is called whenever the application is called with command line arguments
     * Opens the text files given through the command line
     */ 
    void on_open(
        const Gio::Application::type_vec_files &files,
        const Glib::ustring &hint) override;

public:
    /**
     * Creates a File_Opener_Window object and 
     * returns a smart pointer of that object
     */ 
    static Glib::RefPtr<File_Opener> create();
};

#endif /* GTK_FILE_OPENER_INCLUDE_GUARD */