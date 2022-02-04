#ifndef GTK_FILE_OPENER_WINDOW_GUARD
#define GTK_FILE_OPENER_WINDOW_GUARD

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/stack.h>
#include <gtkmm/stackswitcher.h>
#include <gtkmm/menubutton.h>
#include <giomm/settings.h>
#include <gtkmm/searchbar.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/searchentry.h>
#include <glibmm/binding.h>
#include <gtkmm/revealer.h>
#include <gtkmm/listbox.h>
#include <gtkmm/label.h>

class File_Opener_Window : public Gtk::ApplicationWindow
{
public:
    /**
     * Constructor
     */ 
    File_Opener_Window(
        BaseObjectType *cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder);

    /**
     * Creates a File_Opener_Window object 
     * and returns a pointer to it
     */ 
    static File_Opener_Window *create();

    /**
     * Opens a window with a buffer containing the contents 
     * of file in read-only mode.
     * The files should be UTF-8 compilant
     */ 
    void open_file_view(const Glib::RefPtr<Gio::File> &file);

    /**
     * Saves the contents of the file currently in view
     */
    void save_file_view(); 

protected:
    /**
     * Called whenever the text in search field is changed
     */ 
    void on_search_text_changed();

    /**
     * Called whenever tab with another file is selected
     * The child refers to view in m_stack
     */ 
    void on_visible_child_changed();

    /**
     * Called whenever a word in m_words is selected from m_sidebar
     * Indirectly highlights the first word in buffer with the label
     * of selected button
     */
    void on_find_word(const Gtk::Button *button);

    /**
     * Called whenever tab with another file is selected
     * The child refers to view in m_stack
     */ 
    void on_reveal_child_changed();

    /**
     * Updates the contents in m_words whenever a different 
     * file is selected for view
     */ 
    void update_words();

    /**
     * Updates the line number whenever a different file is
     * selected for view
     */ 
    void update_lines();

    /**
     * Updates the buffer font
     */
    void on_buffer_change(); 

    //Contains pointer to a builder object created from window.ui
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    //Contains pointer to the settings objecg which manages properties of application
    Glib::RefPtr<Gio::Settings> m_settings;
    //Contains pointer to a binding object that is connected to search box
    Glib::RefPtr<Glib::Binding> m_binding_search_enabled;
    //Contains pointer to a binding object that is connected to line label
    Glib::RefPtr<Glib::Binding> m_binding_lines_visible;
    //A stack widget that shows one object(widget or view) at a time.
    Gtk::Stack *m_stack;
    //Points to menu button that shows some options available to user.
    Gtk::MenuButton *m_gears;
    //Points to a button that activates and deactivates search feature
    Gtk::ToggleButton *m_search;
    //Points to a search bar which is activated by button *m_search
    Gtk::SearchBar *m_searchbar;
    //Contains text typed in the search box
    Gtk::SearchEntry *m_searchentry;
    //A widget for showing m_words in a list
    Gtk::Revealer *m_sidebar;
    //The words in file currently in view
    Gtk::ListBox *m_words;
    //Label for showing number of lines in a file currently in view
    Gtk::Label *m_lines;
    //Label for showing or hiding the 'Label text' 
    Gtk::Label *m_lines_label;
    
};

#endif /* GTK_FILE_OPENER_WINDOW_GUARD */