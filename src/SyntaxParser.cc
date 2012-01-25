
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
             << "  add          adds a given property to the repository in working directory\n"
             << "  remove       removes a given property from repository in working directory\n"
             << "  modify       modifies a given property from repository in working directory\n"
             << "  render       renders a file to ouput/ using repository in working directory\n"
             << "  show         prints used and unused variables\n"
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
        Repository working_repo;
        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }
        if (argc < 2 || argc > 3)
        {
            std::cout << "You need to specify a key and a value at least.\n"
                      << "Specifying a type is optional.\n"
                      << "Synopsis: emp add <key> [<type>] <value>\n\n";
            return;
        }

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

        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }
        if (argc > 1)
        {
            std::cout << "This command runs without any parameters.\n"
                      << "Specifying a template is optional and gives you\n"
                      << "some template specific information.\n"
                      << "Synopsis: emp show [<path-to-template>]\n\n";
            return;
        }

        working_repo.Load();
        std::list <GenPropertyBase*> propList = working_repo.GetPropertyList();

        if (argc != 0) //template mode
        {
            SimpleTemplate* tmpl = new SimpleTemplate();
            std::list<std::string> templateProperties = tmpl->GetKeyList(argv[0]);
            std::list<std::string> unused;
            std::list<std::string> used;
            std::list<std::string>::const_iterator stringIt;
            std::list<GenPropertyBase*>::const_iterator propIt;
            bool found;

            //get unused properties from template:
            for (stringIt = templateProperties.begin(); stringIt != templateProperties.end(); stringIt++)
            {
                found = false;
                for (propIt = propList.begin(); propIt != propList.end(); propIt++)
                {
                    if ((*propIt)->GetKey() == *stringIt)
                    {
                        found = true;
                        break;
                    }
                }
                if (found)
                    used.push_back(*stringIt);
                else
                    unused.push_back(*stringIt);
            }

            /* print unused */
            if(unused.size() > 0)
            {
                unused.sort();

                //get length of longest key
                unsigned int maxLength = 0;
                for (stringIt = unused.begin(); stringIt != unused.end(); stringIt++)
                    if ((*stringIt).length() > maxLength)
                        maxLength = (*stringIt).length();

                std::cout << "Used by template, but undefined(" << unused.size() << "):" << std::endl;
                for (stringIt = unused.begin(); stringIt != unused.end();)
                {
                    for(int i = 0; i < 3; i++)
                    {
                        if (stringIt == unused.end())
                            break;
                        std::cout << "\t" << *stringIt;
                        for (int j = maxLength - (*stringIt).length(); j > 0; j--)
                            std::cout << " ";

                        stringIt++;
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
            else
                std::cout << "All values for your given template are defined.";
            
            if (used.size() > 0 && unused.size() > 0)
            {
                /* print used*/
                used.sort();

                //get length of longest key
                unsigned int maxLength = 0;
                for (stringIt = used.begin(); stringIt != used.end(); stringIt++)
                    if ((*stringIt).length() > maxLength)
                        maxLength = (*stringIt).length();

                std::cout << "Used by template and defined(" << used.size() << "):" << std::endl;
                for (stringIt = used.begin(); stringIt != used.end();)
                {
                    for(int i = 0; i < 3; i++)
                    {
                        if (stringIt == used.end())
                            break;
                        std::cout << "\t" << *stringIt;
                        for (int j = maxLength - (*stringIt).length(); j > 0; j--)
                            std::cout << " ";

                        stringIt++;
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
        }
        else //normal mode
        {
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

            std::cout << "Repository root path: " << working_repo.GetRepositoryPath() << std::endl;

            if (used.size() != 0)
            {
                std::cout << std::endl << "Used Properties(" << used.size() << "):" << std::endl;
                for (it = used.begin(); it != used.end(); it++)
                {
                    std::string key = (*it)->GetKey();
                    std::string type = (*it)->GetTypeN();
                    std::string value = Filesystem::FileReadString(key);

                    std::cout << "\t";
                    std::cout << key << "<" << type << "> = " << value << std::endl;;
                }
            }

            if (unused.size() != 0)
            {
                std::cout << std::endl << "Unused Properties(" << unused.size() << "):" << std::endl;
                for (it = unused.begin(); it != unused.end(); it++)
                {
                    std::string key = (*it)->GetKey();
                    std::string type = (*it)->GetTypeN();
                    std::cout << "\t";
                    std::cout << key << "<" << type << ">" << std::endl;;
                }
            }
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
        if (working_repo.IsExistent())
        {
            std::cout << "There is a already a repository in this or it's parent directories." << std::endl;
            return;
        }

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
        Repository working_repo;
        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }
        if (argc != 1)
        {
            std::cout << "You need to specify a key.\n"
                      << "Synopsis: emp remove <key>\n\n";
            return;
        }
        else
        {
            working_repo.RemoveProperty(argv[0]);
        }
    }
}
