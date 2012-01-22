
#include <string>
#include <iostream>

#include <cstring>

#include "Repository.h"
//#include "SyntaxParser.h"

#ifndef NULL
#define NULL 0
#endif

//namespace Sp = SyntaxParser;

/** function to print the help
 */
static void usage()
{
    std::cout << "Synopsis: emp <actions> [<action-arguments>] [<action-options>]\n\n"
         << "  init         initialize a repository in the working directory\n"
         << std::endl
         << "  --help, -h   print this help\n";
}


/** this is the main function of the program
 *
 * to keep things simple all control flow happens here
 * which means command line parsing with all functions
 * the program can do
 *
 * @param argc the count of arguments
 * @param argv the 2-dimensional array to hold command line args
 */
int main(int argc, char* argv[])
{

    Repository working_repo;
    

    /* Skip over command name */

    argv++;
    argc--;

    if (argc == 0)
    {
        if (Repository::IsExistent())
            std::cout << "You have a repository here" << std::endl;

        usage();

        return 0;
    }


    /* command line parser loop */

    while (argc > 0)
    {
        if (strcmp(argv[0], "-h")    == 0 ||
            strcmp(argv[0], "-help") == 0)
        {
            usage();
            return 0;
        }
        else if (strcmp(argv[0], "init") == 0)
        {
            //Sp::init();
            argc--;
            argv++;
        }
        else if (strcmp(argv[0], "add") == 0)
        {
            argc--;
            argv++;
            //Sp::add(argc, argv);
        }
        else if (strcmp(argv[0], "modify") == 0)
        {
            argc--;
            argv++;
            //Sp::modify(argc, argv);
        }
        else if (strcmp(argv[0], "render") == 0)
        {
            argc--;
            argv++;
            //Sp::render(argc, argv);
        }
        else if (strcmp(argv[0], "show") == 0)
        {
            argc--;
            argv++;
            //Sp::show(argc, argv);
        }
        else
        {
            usage();
            return 0;
        }
    }
    return 0;
}
