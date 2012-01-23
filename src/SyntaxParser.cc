
/* SyntaxParser.cc
 * @Author:      rbs (rbs@hrz.tu-chemnitz.de)
 * @License:     GPL
 * @Created:     2012-01-22
 * @Editor:      Sublime Text 2
 */

#include "SyntaxParser.h"

namespace Fs = Filesystem;

//////////////////////////////////////////////////////////////////////////////
namespace SyntaxParser
{
    /** function to print the help
     */
    void usage()
    {
        std::cout << "Synopsis: emp <actions> [<action-arguments>] [<action-options>]\n\n"
             << "  init         initialize a repository in the working directory\n"
             << "  render       renders a file to ouput/ using repository in working directory\n"
             << std::endl
             << "  --help, -h   print this help\n";
    }

    /** add command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void add(int argc, char* argv[])
    {
        //Check if collection with name exists
        if(Fs::DirectoryExists(argv[0]) == true)
        {
            //add as Collection
        }
        else
        {
            Repository working_repo;
            if (argc == 3)
                working_repo.AddProperty(argv[0], argv[1], argv[2]);
            else if (argc == 2)
                working_repo.AddProperty(argv[0], "", argv[1]);
            else
                throw NotEnoughArgs();
        }
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
    
    /** modify command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void modify(int argc, char* argv[])
    {
        
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** show command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void show(int argc, char* argv[])
    {
        
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** init command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void init(int argc, char* argv[])
    {
        Repository working_repo;
        try
        {
            working_repo.Init();
        }
        catch(RepoExistentError &exc)
        {
            std::cout << "You have already a repo here." << std::endl;
            return;
        }
        catch(CannotCreateRepoError &exc)
        {
            std::cout << "The repository can not be created, maybe you do not have" << std::endl
                 << "permissions." << std::endl;
            return;
        }
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
    
    /** render command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void render(int argc, char* argv[])
    {
        Repository working_repo;
        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }
        if (argc == 0)
        {
            std::cout << "You need to specify a template." << std::endl;
            std::cout << "Synopsis: emp render <path-to-template>\n\n"
                 << "  --help, -h   print this help\n";
            return;
        }
        while (argc > 0)
        {
            if (!Fs::FileExists(*argv))
            {
                std::cout << *argv << " The specified file could not be found." << std::endl;
            }

            // create template object
            SimpleTemplate* tmpl = new SimpleTemplate();
            // load all properties
            tmpl->AddProperties(working_repo.GetPropertyList());
            // parse input and write to variable
            string output;
            tmpl-ParseFile(*argv, output);

            // extract filename
            std::string key = rPath;
            std::string search_for = "/";

            std::size_t found;
            found = key.rfind(search_for);

            if ( found != std::string::npos)
                key.replace(0, found + 1,"");

            // write file
            Fs::FileWriteString()


            argc--;
            argv++;
        }
    }
}
