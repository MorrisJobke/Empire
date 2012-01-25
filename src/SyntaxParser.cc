
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
             << "  addi         interactive adding of all properties in a given template\n"
             << "  remove       removes a given property from repository in working directory\n"
             << "  modify       modifies a given property from repository in working directory\n"
             << "  render       renders a file to ouput/ using repository in working directory\n"
             << "  show         prints used and unused variables\n"
             << std::endl
             << "  --help, -h   print this help\n";
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
    
    /** create command
     *
     * only creates a property instance, useful for collections
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void create(int argc, char* argv[])
    {
        Repository working_repo;
        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }
        if (argc != 2)
        {
            std::cout << "You need to specify a key and a value.\n"
                      << "Synopsis: emp create <key> <type>\n\n";
            return;
        }

        try
        {
            working_repo.CreatePropertyClass(argv[0], argv[1]);
        }
        catch(PropExistentError &exc)
        {
            std::cout << "Property exists." << std::endl;
            return;
        }
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
                      << "Synopsis: emp add <key> [<type>] <value>\n"
                      << "For an interactive add use:\n"
                      << "emp addi <template>\n\n";
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
    
    /** add command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void addi(int argc, char* argv[])
    {
        Repository working_repo;
        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }
        if (argc != 1)
        {
            std::cout << "You need to specify a template.\n"
                      << "Synopsis: emp addi <path-to-template>\n\n";
            return;
        }
        working_repo.Load();

        SimpleTemplate* tmpl = new SimpleTemplate();
        std::list<std::string> missing = tmpl->GetMissingProperties(argv[0], working_repo.GetPropertyList());
        if (missing.size() == 0)
        {
            std::cout << "There are no properties missing. You are ready to render." << std::endl;
            return;
        }
        std::cout << "missing elements: " << missing.size() << std::endl;
        
        std::list<std::string>::const_iterator it;
        std::string tmpValue;

        for(it = missing.begin(); it != missing.end(); it++)
        {
            std::cout << "Please enter a value for \"" << *it << "\", press [Enter] to skip:" << std::endl; 
            std::getline(std::cin, tmpValue);
            if (tmpValue != "")
                working_repo.AddProperty(*it, "", tmpValue);
            else
                std::cout << "[SKIPPED]" << std::endl;
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
            //TODO: replace by SimpleTemplate::GetMissingProperties
            SimpleTemplate* tmpl = new SimpleTemplate();
            std::list<std::string> templateProperties = tmpl->GetKeyList(argv[0]);
            std::list<std::string> unused;
            std::list<std::string> used;
            std::list<std::string>::const_iterator stringIt;
            std::list<GenPropertyBase*>::const_iterator propIt;
            bool found;

            used = working_repo.GetDefindedValuesInCwd();
            unused = working_repo.GetUnDefindedValuesInCwd();
            
            /* print unused */
            if(unused.size() > 0)
            {
                unused.sort();
                unused.unique();
                //get length of longest key
                unsigned int maxLength = 0;
                for (stringIt = unused.begin(); stringIt != unused.end(); stringIt++)
                    if ((*stringIt).length() > maxLength)
                        maxLength = (*stringIt).length();

                std::cout << COLOR_BOLD << "Used by template, but undefined(" << unused.size() << "):" << COLOR_CLEAR << std::endl;
                std::cout << COLOR_RED;
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
                std::cout << COLOR_CLEAR << std::endl;
            }
            /* print used */
            if (used.size() > 0)
            {
                /* print used*/
                used.sort();
                used.unique();

                //get length of longest key
                unsigned int maxLength = 0;
                for (stringIt = used.begin(); stringIt != used.end(); stringIt++)
                    if ((*stringIt).length() > maxLength)
                        maxLength = (*stringIt).length();
                if(unused.size() == 0)
                    std::cout << COLOR_BOLD << "All values for your given template are defined(" << used.size() << "):" << COLOR_CLEAR << std::endl;
                else
                    std::cout << COLOR_BOLD << "Used by template and defined(" << used.size() << "):" << COLOR_CLEAR << std::endl;
                std::cout << COLOR_GREEN;
                for (stringIt = used.begin(); stringIt != used.end(); stringIt++)
                {
                    std::cout   << "\t" << (*stringIt) << COLOR_BLUE
                                << "<" << working_repo.GetPropertyByKey(*stringIt)->GetTypeN()
                                << ">" << COLOR_GREEN << " = " << Fs::FileReadString(*stringIt) << std::endl;
                }
                std::cout << COLOR_CLEAR << std::endl;
            }
        }
        else //normal mode
        {
            std::list<std::string>::const_iterator it;
            std::list<GenPropertyBase*> usedProperties;
            std::list<std::string> used;
            std::list<std::string> unused;

            used = working_repo.GetDefindedValuesInCwd();
            unused = working_repo.GetUnDefindedValuesInCwd();

            std::cout << "Repository root path: " << working_repo.GetRepositoryPath() << std::endl << std::endl;

            if (used.size() != 0)
            {
                std::cout << COLOR_BOLD << "Used Properties(" << used.size() 
                          << "):" << COLOR_CLEAR << std::endl;
                for (it = used.begin(); it != used.end(); it++)
                {
                    std::string key = *it;
                    std::string type = working_repo.GetPropertyByKey(key)->GetTypeN();
                    std::string loc;
                    std::string value = working_repo.getFirstDefinedValueRec(key, Fs::GetCwd(), loc);
                    std::string color;
                    if (loc == Fs::GetCwd())
                        color = COLOR_GREEN;
                    else
                        color = COLOR_CYAN;
                                           
                    std::cout << color << "\t";
                    std::cout << key << COLOR_BLUE << "<" << type 
                    << "> " << color << "= " << value << std::endl;;
                }
                std::cout << COLOR_CLEAR << std::endl;
            }

            if (unused.size() != 0)
            {
                std::cout << COLOR_BOLD << "Unused Properties(" << unused.size() 
                          << "):" << COLOR_CLEAR << std::endl;
                std::cout << COLOR_RED;
                
                for (it = unused.begin(); it != unused.end(); it++)
                {
                    std::string key = *it;
                    std::string type = working_repo.GetPropertyByKey(key)->GetTypeN();
                    std::cout << "\t";
                    std::cout << key << COLOR_BLUE << "<" << type << ">" << COLOR_CLEAR << std::endl;;
                }
                std::cout << COLOR_CLEAR << std::endl;
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
        if (argc != 1 && !((argc == 2) && strcmp(argv[0], "--all") == 0))
        {
            std::cout << "You need to specify a key.\n"
                      << "Synopsis: emp remove [--all] <key>\n\n";
            return;
        }
        else
        {
            if(argc == 2)
                working_repo.RemovePropertyClassAndInstances(argv[1]);
            else
                working_repo.RemoveProperty(argv[0]);
        }
    }
}
