#include <iostream>
#include <exception>
#include "File_Opener.h"
#include "File_Opener_Window.cpp"

File_Opener::File_Opener()
    : Gtk::Application(
          "org.mt.fileopener.app",
          Gio::Application::Flags::HANDLES_OPEN) {}

Glib::RefPtr<File_Opener> File_Opener::create()
{
    return Glib::make_refptr_for_instance<File_Opener>(new File_Opener());
}

File_Opener_Window *File_Opener::create_appwindow()
{
    auto app_window = File_Opener_Window::create();
    add_window(*app_window);

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

    add_action(
        "quit",
        sigc::mem_fun(
            *this,
            &File_Opener::on_action_quit));
    set_accel_for_action("app.quit", "<Ctrl>Q");
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

}

void File_Opener::on_action_quit()
{
    auto windows = get_windows();
    for( auto window : windows)
    {
        window->hide();
    }
    quit();
}
