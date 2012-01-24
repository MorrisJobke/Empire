
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
        Repository working_repo;
        working_repo.Load();
        std::list <GenPropertyBase*> propList = working_repo.GetPropertyList();

        std::list<GenPropertyBase*>::const_iterator it;
        std::list<GenPropertyBase*> used;
        std::list<GenPropertyBase*> unused;

        for (it = propList.begin(); it != propList.end(); it++)
        {
            std::string key = (*it)->GetKey();
            std::string type = (*it)->GetTypeN();
            
            if (Fs::FileExists(key))
                used.push_back(*it);
            else
                unused.push_back(*it);
        }

        std::cout << "Used Properties(" << used.size() << "):" << std::endl;
        for (it = used.begin(); it != used.end(); it++)
        {
            std::string key = (*it)->GetKey();
            std::string type = (*it)->GetTypeN();
            std::string value = Filesystem::FileReadString(key);

            std::cout << "\t";
            std::cout << key << "<" << type << "> = " << value << std::endl;;
        }

        std::cout << std::endl << "Unused Properties(" << unused.size() << "):" << std::endl;
        for (it = unused.begin(); it != unused.end(); it++)
        {
            std::string key = (*it)->GetKey();
            std::string type = (*it)->GetTypeN();
            std::cout << "\t";
            std::cout << key << "<" << type << ">" << std::endl;;
        }
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
        if (argc != 2)
        {
            std::cout << "You need to specify a template and an output path.\n"
                      << "Synopsis: emp render <path-to-template> <path-to-output>\n\n";
            return;
        }
        std::string file = *argv;
        argc--;
        argv++;

        if (!Fs::FileExists(file))
        {
            std::cout << file << " The specified template file could not be found." << std::endl;
            return;
        }

        // create template object
        SimpleTemplate* tmpl = new SimpleTemplate();
        // load all properties
        tmpl->AddProperties(working_repo.GetPropertyList());
        // parse input and write to variable
        std::string output;
        tmpl->ParseFile(file, output);

        // extract filename
        std::string filename = file;
        std::string search_for = "/";
        std::size_t found;
        found = filename.rfind(search_for);

        if (found != std::string::npos)
            filename.replace(0, found + 1,"");

        // getting output path
        std::string path = *argv;
        argc--;
        argv++;

        // directory OR file
        if (Fs::DirectoryExists(path))
        {
            // directory
            if (Fs::FileExists(path + "/" + filename))
            {
                // contains already the file
                std::cout << path + "/" + filename << " The specified output file exists." << std::endl;
                return;
            }
            if (path.substr(path.size() - 1, 1) == "/")
                path += filename;
            else
                path += "/" + filename;
        }
        else
        {
            // it's a file or directory doesn't exists
            // check if it's a file
            if (Fs::FileExists(path))
            {
                std::cout << path << " The specified output directory contains already a file named like the tmeplate file." << std::endl;
                return;
            }
            // extract directory
            std::string dir = path;
            // found and search_for are already declared above
            found = dir.rfind(search_for);

            if (found != std::string::npos)
                dir = dir.substr(0, found);
            // create dir if it doesn't exists
            if (!Fs::DirectoryExists(dir))
            {
                Fs::CreateDirectoryRec(dir);
            }
            if (path.substr(path.size() - 1, 1) == "/")
                path += "/" + filename;
        }
        Fs::FileWriteString(path, output);
    }

    /** remove command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void remove(int argc, char* argv[])
    {
        
    }
}
