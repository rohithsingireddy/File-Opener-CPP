#include "File_Opener.cpp"
#include <glibmm.h>

int main(int argc, char **argv)
{
    Glib::setenv("GSETTINGS_SCHEMA_DIR", ".", false);
    auto application = File_Opener::create();
    return application->run(argc, argv);
}