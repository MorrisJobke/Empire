
#include <string>
#include <iostream>

#include <cstring>

#include "Repository.h"
#include "SyntaxParser.h"

#ifndef NULL
#define NULL 0
#endif

namespace Sp = SyntaxParser;

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
        if (working_repo.IsExistent())
            std::cout << "You have a repository here" << std::endl;

        Sp::usage();

        return 0;
    }


    /* command line parser loop */

    while (argc > 0)
    {
        if (strcmp(argv[0], "-h")    == 0 ||
            strcmp(argv[0], "-help") == 0)
        {
            Sp::usage();
            return 0;
        }
        else if (strcmp(argv[0], "init") == 0)
        {
            argc--;
            argv++;
            Sp::init(argc, argv);
            return 0;
        }
        else if (strcmp(argv[0], "create") == 0)
        {
            argc--;
            argv++;
            Sp::create(argc, argv);
            return 0;
        }
        else if (strcmp(argv[0], "add") == 0)
        {
            argc--;
            argv++;
            Sp::add(argc, argv);
            return 0;
        }
        else if (strcmp(argv[0], "addi") == 0)
        {
            argc--;
            argv++;
            Sp::addi(argc, argv);
            return 0;
        }
        else if (strcmp(argv[0], "cadd") == 0)
        {
            argc--;
            argv++;
            Sp::coll_add(argc, argv);
            return 0;
        }
        else if (strcmp(argv[0], "modify") == 0)
        {
            argc--;
            argv++;
            Sp::modify(argc, argv);
            return 0;
        }
        else if (strcmp(argv[0], "render") == 0)
        {
            argc--;
            argv++;
            Sp::render(argc, argv);
            return 0;
        }
        else if (strcmp(argv[0], "show") == 0)
        {
            argc--;
            argv++;
            Sp::show(argc, argv);
            return 0;
        }
        else if (strcmp(argv[0], "remove") == 0)
        {
            argc--;
            argv++;
            Sp::remove(argc, argv);
            return 0;
        }
        else
        {
            Sp::usage();
            return 0;
        }
    }
    return 0;
}
