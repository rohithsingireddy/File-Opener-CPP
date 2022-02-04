#include <iostream>
#include <exception>
#include "File_Opener.h"
#include "File_Opener_Window.h"
#include "File_Opener_Prefs.h"

File_Opener::File_Opener()
    : Gtk::Application(
          "org.mt.fileopener.application",
          Gio::Application::Flags::HANDLES_OPEN) {}

Glib::RefPtr<File_Opener> File_Opener::create()
{
    return Glib::make_refptr_for_instance<File_Opener>(new File_Opener());
}

File_Opener_Window *File_Opener::create_appwindow()
{
    auto app_window = File_Opener_Window::create();
    add_window(*app_window);

    // Makes it possible for on_hide_window to be called
    // for the current window when it is hidden
    app_window->signal_hide().connect(
        sigc::bind(
            sigc::mem_fun(
                *this,
                &File_Opener::on_hide_window),
            app_window));

    return app_window;
}

void File_Opener::on_activate()
{
    try
    {
        create_appwindow()->present();
    }
    catch (const Glib::Error &ex)
    {
        std::cerr << "File_Opener::on_activate(): " << ex.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "File_Opener::on_activate(): " << e.what() << std::endl;
    }
}

void File_Opener::on_startup()
{
    Gtk::Application::on_startup();

    add_action(
        "preferences",
        sigc::mem_fun(
            *this,
            &File_Opener::on_action_preferences));
    set_accel_for_action("app.preferences", "<Ctrl>P");

    add_action(
        "quit",
        sigc::mem_fun(
            *this,
            &File_Opener::on_action_quit));
    set_accel_for_action("app.quit", "<Ctrl>Q");

    add_action(
        "open",
        sigc::mem_fun(
            *this,
            &File_Opener::open_file));
    set_accel_for_action("app.open", "<Ctrl>O");

    set_accel_for_action("win.save", "<Ctrl>S");
}

void File_Opener::on_open(
    const Gio::Application::type_vec_files &files,
    const Glib::ustring &)
{
    File_Opener_Window *app_window = nullptr;
    auto windows = get_windows();
    if (windows.size() > 0)
    {
        app_window = dynamic_cast<File_Opener_Window *>(windows[0]);
    }

    try
    {
        if (!app_window)
        {
            app_window = create_appwindow();
        }

        for (const auto &file : files)
        {
            app_window->open_file_view(file);
        }
        app_window->present();
    }
    catch (const Glib::Error &er)
    {
        std::cerr << "File_Opener::on_open(): " << er.what() << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "File_Opener::on_open(): " << ex.what() << std::endl;
    }
}

void File_Opener::on_hide_window(Gtk::Window *window)
{
    delete window;
}

void File_Opener::on_action_preferences()
{
    try
    {
        auto prefs_dialog = File_Opener_Prefs::create(*get_active_window());
        prefs_dialog->present();

        prefs_dialog->signal_hide().connect(
            sigc::bind(
                sigc::mem_fun(
                    *this,
                    &File_Opener::on_hide_window),
                prefs_dialog));
    }
    catch (const Glib::Error &er)
    {
        std::cerr << "File_Opener::on_action_preferences(): " << er.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "File_Opener::on_action_preferences(): " << e.what() << std::endl;
    }
}

void File_Opener::on_action_quit()
{
    auto windows = get_windows();
    for (auto window : windows)
    {
        window->hide();
    }
    quit();
}

void File_Opener::open_file()
{
    Gtk::FileChooserDialog *dialog = new Gtk::FileChooserDialog("Choose a text file", Gtk::FileChooser::Action::OPEN);

    dialog->set_transient_for(*get_active_window());
    dialog->set_modal(true);

    dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
    dialog->add_button("_Open", Gtk::ResponseType::OK);
    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files");
    filter_text->add_mime_type("text/plain");
    dialog->add_filter(filter_text);

    auto filter_cpp = Gtk::FileFilter::create();
    filter_cpp->set_name("C/C++ files");
    filter_cpp->add_mime_type("text/x-c");
    filter_cpp->add_mime_type("text/x-c++");
    filter_cpp->add_mime_type("text/x-c-header");
    dialog->add_filter(filter_cpp);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->signal_response().connect(
        sigc::bind(
            sigc::mem_fun(
                *this,
                &File_Opener::on_file_choose),
            dialog));

    dialog->show();
}

void File_Opener::on_file_choose(int response_id, Gtk::FileChooserDialog *dialog)
{
    switch (response_id)
    {
    case Gtk::ResponseType::OK:
    {
        auto file = dialog->get_file();
        File_Opener_Window *app_window = nullptr;
        auto windows = get_windows();
        if (windows.size() > 0)
        {
            app_window = dynamic_cast<File_Opener_Window *>(windows[0]);
        }

        try
        {
            if (!app_window)
            {
                app_window = create_appwindow();
            }
            app_window->open_file_view(file);
            app_window->present();
        }
        catch (const Glib::Error &er)
        {
            std::cerr << "File_Opener::on_open(): " << er.what() << std::endl;
        }
        catch (const std::exception &ex)
        {
            std::cerr << "File_Opener::on_open(): " << ex.what() << std::endl;
        }
        break;
    }
    case Gtk::ResponseType::CANCEL:
    {
        break;
    }
    default:
    {
        break;
    }
    }
    delete dialog;
}