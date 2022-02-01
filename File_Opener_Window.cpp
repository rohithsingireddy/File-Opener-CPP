#include <set>
#include <iostream>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <giomm/propertyaction.h>
#include "File_Opener_Window.h"
#include "resources.c"

File_Opener_Window::File_Opener_Window(
    BaseObjectType *cobject,
    const Glib::RefPtr<Gtk::Builder> &refBuilder)
    : Gtk::ApplicationWindow(cobject),
      m_refBuilder(refBuilder),
      m_stack(nullptr),
      m_gears(nullptr),
      m_search(nullptr),
      m_searchbar(nullptr),
      m_searchentry(nullptr),
      m_words(nullptr),
      m_sidebar(nullptr),
      m_lines(nullptr),
      m_lines_label(nullptr),
      m_settings(),
      m_binding_search_enabled()
{
    m_stack = m_refBuilder->get_widget<Gtk::Stack>("stack");
    if (!m_stack)
    {
        throw std::runtime_error("No \"stack\" object in window.ui");
    }

    m_gears = m_refBuilder->get_widget<Gtk::MenuButton>("gears");
    if (!m_gears)
    {
        throw std::runtime_error("No \"gears\" object in window.ui");
    }

    m_search = m_refBuilder->get_widget<Gtk::ToggleButton>("search");
    if (!m_search)
    {
        throw std::runtime_error("No \"search\" object in window.ui");
    }

    m_searchentry = m_refBuilder->get_widget<Gtk::SearchEntry>("searchentry");
    if (!m_searchentry)
    {
        throw std::runtime_error("No \"searchentry\" object in window.ui");
    }

    m_searchbar = m_refBuilder->get_widget<Gtk::SearchBar>("searchbar");
    if (!m_searchbar)
    {
        throw std::runtime_error("No \"searchbar\" object in window.ui");
    }

    m_sidebar = m_refBuilder->get_widget<Gtk::Revealer>("sidebar");
    if (!m_sidebar)
    {
        throw std::runtime_error("No \"sidebar\" object in window.ui");
    }

    m_words = m_refBuilder->get_widget<Gtk::ListBox>("words");
    if (!m_words)
    {
        throw std::runtime_error("No \"words\" object in window.ui");
    }

    m_lines = m_refBuilder->get_widget<Gtk::Label>("lines");
    if(!m_lines)
    {
        throw std::runtime_error("No \"lines\" in window.ui");
    }

    m_lines_label = m_refBuilder->get_widget<Gtk::Label>("lines_label");
    if(!m_lines_label)
    {
        throw std::runtime_error("No \"lines_label\" in window.ui");
    }

    auto menu_builder = Gtk::Builder::create_from_resource("/org/mt/fileopener/gears_menu.ui");
    auto menu = menu_builder->get_object<Gio::MenuModel>("menu");
    if (!menu)
    {
        throw std::runtime_error("No \"menu\" object in gears_menu.ui");
    }
    m_gears->set_menu_model(menu);

    m_binding_search_enabled = Glib::Binding::bind_property(
        m_search->property_active(),
        m_searchbar->property_search_mode_enabled(),
        Glib::Binding::Flags::BIDIRECTIONAL);

    m_binding_lines_visible = Glib::Binding::bind_property(
        m_lines->property_visible(),
        m_lines_label->property_visible());

    m_searchentry->signal_search_changed().connect(
        sigc::mem_fun(
            *this,
            &File_Opener_Window::on_search_text_changed));

    m_sidebar->property_reveal_child().signal_changed().connect(
        sigc::mem_fun(
            *this,
            &File_Opener_Window::on_reveal_child_changed));

    m_stack->property_visible_child().signal_changed().connect(
        sigc::mem_fun(
            *this,
            &File_Opener_Window::on_visible_child_changed));

    m_settings = Gio::Settings::create("org.mt.fileopener");
    m_settings->bind("transition", m_stack->property_transition_type());
    m_settings->bind("show-words", m_sidebar->property_reveal_child());

    add_action(m_settings->create_action("show-words"));
    add_action(Gio::PropertyAction::create("show-lines", m_lines->property_visible()));
}

File_Opener_Window *File_Opener_Window::create()
{
    auto refBuilder = Gtk::Builder::create_from_resource("/org/mt/fileopener/window.ui");

    auto window = Gtk::Builder::get_widget_derived<File_Opener_Window>(refBuilder, "app_window");
    if (!window)
    {
        throw std::runtime_error("No \"app_window\" object in window.ui");
    }
    return window;
}

void File_Opener_Window::open_file_view(const Glib::RefPtr<Gio::File> &file)
{
    const Glib::ustring basename = file->get_basename();

    auto view = Gtk::make_managed<Gtk::TextView>();
    view->set_editable(false);
    view->set_cursor_visible(false);
    view->set_margin(5);

    auto scrolled = Gtk::make_managed<Gtk::ScrolledWindow>();
    scrolled->set_expand(true);
    scrolled->set_child(*view);
    m_stack->add(*scrolled, basename, basename);

    try
    {
        char *contents = nullptr;
        gsize length = 0;
        file->load_contents(contents, length);
        view->get_buffer()->set_text(contents, contents + length);
        g_free(contents);
    }
    catch (const Glib::Error &er)
    {
        std::cerr << "File_Opener_Window::open_file_view(\"" << file->get_parse_name()
                  << "\"): " << er.what() << std::endl;
    }

    auto buffer = view->get_buffer();
    auto tag = buffer->create_tag();
    m_settings->bind("font", tag->property_font());
    buffer->apply_tag(
        tag,
        buffer->begin(),
        buffer->end());

    m_search->set_sensitive(true);
    update_words();
    update_lines();
}

void File_Opener_Window::on_search_text_changed()
{
    const auto text = m_searchentry->get_text();
    if (text.empty())
    {
        return;
    }

    auto tab = dynamic_cast<Gtk::ScrolledWindow *>(m_stack->get_visible_child());
    if (!tab)
    {
        std::cerr << "File_Opener_Window::on_search_text_changed(): No visible child" << std::endl;
        return;
    }

    auto view = dynamic_cast<Gtk::TextView *>(tab->get_child());
    if (!view)
    {
        std::cerr << "File_Opener_Window::on_search_text_changed(): No visible text view. " << std::endl;
        return;
    }

    // Can be done with a suffix tree
    auto buffer = view->get_buffer();
    Gtk::TextIter match_start, match_end;
    if (buffer->begin().forward_search(
            text,
            Gtk::TextSearchFlags::CASE_INSENSITIVE,
            match_start,
            match_end))
    {
        buffer->select_range(match_start, match_end);
        view->scroll_to(match_start);
    }
}

void File_Opener_Window::on_visible_child_changed()
{
    m_searchbar->set_search_mode(false);
    update_words();
    update_lines();
}

void File_Opener_Window::on_find_word(const Gtk::Button *button)
{
    m_searchentry->set_text(button->get_label());
}

void File_Opener_Window::on_reveal_child_changed()
{
    update_words();
}

void File_Opener_Window::update_words()
{
    auto tab = dynamic_cast<Gtk::ScrolledWindow *>(m_stack->get_visible_child());
    if(!tab)
    {
        return;
    }

    auto view = dynamic_cast<Gtk::TextView*>(tab->get_child());
    if(!view)
    {
        std::cerr << "File_Opener_Window::update_words(): No visible text view" << std::endl;
        return;
    }

    auto buffer = view->get_buffer();

    std::set<Glib::ustring> words;
    auto start = buffer->begin();
    Gtk::TextIter end;
    while (start)
    {
        while( start && !start.starts_word())
        {
            ++start;
        }

        if(!start)
        {
            break;
        }

        end = start;
        end.forward_word_end();
        if( start == end )
        {
            break;
        }

        auto word = buffer->get_text(start, end, false);
        words.insert(word.lowercase());
        start = end;
    }

    while( auto child = m_words->get_first_child() )
    {
        m_words->remove(*child);
    }

    for(const auto &word: words )
    {
        auto row = Gtk::make_managed<Gtk::Button>(word);
        row->signal_clicked().connect(
            sigc::bind(
                sigc::mem_fun(
                    *this,
                    &File_Opener_Window::on_find_word
                ),
                row
            )
        );
        m_words->append(*row);
    }
}

void File_Opener_Window::update_lines()
{
    auto tab = dynamic_cast<Gtk::ScrolledWindow *>(m_stack->get_visible_child());
    if(!tab)
    {
        return;
    }

    auto view = dynamic_cast<Gtk::TextView*>(tab->get_child());
    if(!view)
    {
        std::cerr << "File_Opener_Window::update_lines(): No visible text view" << std::endl;
    }

    auto buffer = view->get_buffer();

    int count = 0;
    auto iter = buffer->begin();
    while(iter)
    {
        ++count;
        if(!iter.forward_line())
        {
            break;
        }
    }

    m_lines->set_text(Glib::ustring::format(count));
}
