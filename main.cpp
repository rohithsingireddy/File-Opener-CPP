#include "File_Opener.h"

int main(int argc, char **argv)
{
    auto application = File_Opener::create();
    return application->run(argc, argv);
}