#include "File_Opener.cpp"
#include <glibmm.h>

int main(int argc, char **argv)
{
    //Setting the schema directory
    Glib::setenv("GSETTINGS_SCHEMA_DIR", "./schemas/", false);
    
    auto application = File_Opener::create();
    return application->run(argc, argv);
}