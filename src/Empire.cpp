
#include <string>
#include <iostream>

#include <cstring>

#include "Repository.h"

#ifndef NULL
#define NULL 0
#endif


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

    Repository* p_working_repo = NULL;
    

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
    

        /* help */

        if (strcmp(argv[0], "-h")    == 0 ||
            strcmp(argv[0], "-help") == 0)
        {
            usage();
            return 0;
        }


        /* create repository */
        if (strcmp(argv[0], "init") == 0)
        {
            try
            {
                p_working_repo = new Repository;
            }
            catch(RepoExistentError &exc)
            {
                std::cout << "You have already a repo here." << std::endl;
                return 0;
            }
            catch(CannotCreateRepoError &exc)
            {
                std::cout << "The repository can not be created, maybe you do not have" << std::endl
                     << "permissions." << std::endl;
                return 1;
            }

            argc--;
            argv++;

        }
    }


    /* delete garbage */

    if (p_working_repo != NULL)
        delete p_working_repo;


    return 0;
}
