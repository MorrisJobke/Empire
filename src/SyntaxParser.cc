
/* SyntaxParser.cc
 * @Author:      rbs (rbs@hrz.tu-chemnitz.de)
 * @License:     GPL
 * @Created:     2012-01-22
 * @Editor:      Sublime Text 2
 */

#include "SyntaxParser.h"

namespace Fs = Filesystem;
namespace Ch = ConsoleHelper;
namespace Lh = ListHelper;

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
             << "  create       creates a property definition\n"
             << "  cadd         adds a collection property to the repository in working directory\n"
             << "  cfill        adds a collection row\n"
             << "  create       adds only the property type to the repository in working directory\n"
             << "  iadd         interactive adding of all properties in a given template\n"
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** collection add command
     *
     * create a collection in the current dir
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void coll_add(int argc, char* argv[])
    {
        Repository working_repo;
        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }
        if (argc < 2)
        {
            std::cout << "You need to specify a collection name and at least one key\n"
                      << "Synopsis: emp cadd <coll-name> <key1> [<key2> <key3> ...]\n\n";
            return;
        }

        /* load repo */
        working_repo.Load();

        /* check presence of the collection in the current dir */
        std::string coll_name = argv[0];

        if (Fs::DirectoryExists(coll_name))
        {
            if (working_repo.ContainsProperty(coll_name) == false)
                std::cout << "Collection dir already exists, but you have no collection property\n"
                          << "with the given name.\n";
            else
                std::cout << "Collection dir already.exists\n";

            return;
        }

        /* skip col name */
        argc--;
        argv++;

        /* iterate over keys, check existance and add them to list */
        std::list<GenPropertyBase*> props_to_declare;

        while (argc > 0)
        {
            std::string new_key = argv[0];

            if (working_repo.ContainsProperty(new_key) == false)
            {
                std::cout << "The following key is not declared in repository: " << new_key << std::endl;
                return;
            };

            GenPropertyBase* ext_prop = working_repo.GetPropertyByKey(new_key);
            GenPropertyBase* new_prop = PropertyHelpers::CreatePropertyFromTypeString(ext_prop->GetTypeN());
            new_prop->SetKey(new_key);

            props_to_declare.push_back(new_prop);

            argc--;
            argv++;
        }

        /* declare collection in repo, if not present */
        if (working_repo.ContainsProperty(coll_name) == false)
        {
            working_repo.CreatePropertyClass(coll_name, GetTypeName<Coll>());
        }


        Coll c(coll_name);
        c.Declare(props_to_declare);
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
    
    void coll_fill(int argc, char* argv[])
    {
        using namespace std;

        Repository working_repo;
        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }
        if (argc < 2)
        {
            std::cout << "You need to specify a collection name and at least one key with value\n"
                      << "Synopsis: emp cfill <coll-name> <key1>:<value1> [<key2>:<value2> ...]\n\n";
            return;
        }

        /* load repo */
        working_repo.Load();

        /* check presence of the collection in the current dir */
        std::string coll_name = argv[0];

        if (working_repo.ContainsProperty(coll_name) == false)
        {
                std::cout << "The Repository does not hold a collection called: " << coll_name << "\n";
                return;
        }

        GenPropertyBase* col_prop = working_repo.GetPropertyByKey(coll_name);
        
        if (col_prop->GetTypeN() != GetTypeName<Coll>())
        {
                std::cout << "The Repository does not hold a collection called: " << coll_name << "\n";
                return;
        }

        if (Fs::DirectoryExists(coll_name) == false)
        {
            std::cout << "You have no collection declared here called: " << coll_name << "\n";
            return;
        }

        /* skip col name */
        argc--;
        argv++;

        /* read entries */

        list<GenPropertyBase*> new_entries;
        while (argc > 0)
        {
            std::string new_pair = argv[0];
            
            //cout << "new pair-> " << new_pair << endl;

            /* split tthe pair */
            size_t found = new_pair.find_first_of(":");
            
            if (found == string::npos)
            {
                cout << "You have forgotten the splitting character : " << endl;
                return;
            }
            //cout << ": found at " << found << endl;
            
            string new_key = new_pair.substr(0,found);
            string new_value = new_pair.substr(found + 1, new_pair.length() - found);
            
            //cout << "new key-> " << new_key << endl;
            //cout << "new value-> " << new_value << endl;

            /* check presence of property */
            if (working_repo.ContainsProperty(new_key) == false)
            {
                cout << "Property not found in repository: " << new_key << endl;
                return;
            }
            
            GenPropertyBase* contained_prop = working_repo.GetPropertyByKey(new_key);
            GenPropertyBase* new_prop = PropertyHelpers::CreatePropertyFromTypeString(contained_prop->GetTypeN());
            new_prop->SetKey(new_key);
            new_prop->SetValueFromString(new_value);

            new_entries.push_back(new_prop);
        
            argc--;
            argv++;
        }
        
        /* Load collection */

        Coll c(coll_name);
        c.Load(coll_name);

        c.AddRow(new_entries);
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

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
                      << "emp iadd <template>\n\n";
            return;
        }
        try
        {
            if (argc == 3)
                working_repo.AddProperty(argv[0], argv[1], argv[2]);
            else if (argc == 2)
                working_repo.AddProperty(argv[0], "", argv[1]);
        }
        catch(PropClassExistsWithOtherKey)
        {
            std::cout << "This property is already defined with another type." << std::endl;
        }
        catch(PropExistentError)
        {
            std::cout << "This property exists already in this directory." << std::endl;
        }
        catch(PropClassCreateError)
        {
            std::cout << "An error occured on creation of the property class." << std::endl;
        }
        catch(...)
        {
            std::cout << "An unexpected error occured." << std::endl;
        }
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** add command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void interactive_add(int argc, char* argv[])
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
                      << "Synopsis: emp iadd <path-to-template>\n\n";
            return;
        }
        working_repo.Load();

        SimpleTemplate* tmpl = new SimpleTemplate();
        std::list<std::string> missing = tmpl->GetMissingProperties(argv[0], working_repo.GetAddedPropertiesInCwd());
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
        Repository working_repo;
        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }
        if (argc < 2 || argc > 3)
        {
            std::cout << "You need to specify a key and a value at least.\n"
                      << "Synopsis: emp modify <key> <value>\n";
            return;
        }
        try
        {
            working_repo.RemoveProperty(Fs::GetCwd() + "/" + argv[0]);
        }
        catch(PropNotExists)
        {
            std::cout << "Cannot find file ..." << std::endl;

            std::cout << "Property does not exists. Create instead? [Yn]:" << std::endl;
            std::string tmpValue;
            std::getline(std::cin, tmpValue);
            if (tmpValue == "n" || tmpValue == "N")
                return;
        }
        catch(...)
        {
            std::cout << "An unexpected error occured." << std::endl;
        }

        try
        {
            working_repo.AddProperty(argv[0], "", argv[1]);
        }
        catch(PropClassCreateError)
        {
            std::cout << "An error occured on creation of the property class." << std::endl;
        }
        catch(...)
        {
            std::cout << "An unexpected error occured." << std::endl;
        }
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
        if (argc > 0)
            if (argc > 1 || (strcmp(argv[0],"-h") == 0) || (strcmp(argv[0], "--help") == 0))
            {
                std::cout << "This command runs without any parameters.\n"
                          << "Specifying a template is optional and gives you\n"
                          << "some template specific information.\n"
                          << "Synopsis: emp show [<path-to-template>]\n\n";
                return;
            }

        working_repo.Load();

        if (argc != 0) //template mode
        {
            //TODO: replace by SimpleTemplate::GetMissingProperties
            SimpleTemplate* tmpl = new SimpleTemplate();
            std::list<std::string> unused, used, created, used_colls, unused_colls, needless, needless_colls;
            std::list<std::string>::const_iterator it;

            /*properties:*/
            used = tmpl->GetAvailableProperties(argv[0], working_repo.GetAddedPropertiesInCwd());
            unused = tmpl->GetMissingProperties(argv[0], working_repo.GetAddedPropertiesInCwd());
            created = tmpl->GetAvailableProperties(argv[0], working_repo.GetCreatedPropertiesInCwd());
            needless = tmpl->GetNeedLessProperties(argv[0],
                            Lh::ListMerge(working_repo.GetCreatedPropertiesInCwd(), 
                                                  working_repo.GetAddedPropertiesInCwd())
                                                  );
            /*collections:*/
            used_colls = tmpl->GetAvailableCollections(argv[0], working_repo.GetAddedCollectionsInCwd());
            unused_colls = tmpl->GetMissingCollections(argv[0], working_repo.GetAddedCollectionsInCwd());
            needless_colls =  tmpl->GetNeedLessCollections(argv[0], working_repo.GetAddedCollectionsInCwd());

            /**** PROPERTIES ****/
            if (unused.size() + used.size() + created.size() + needless.size() > 0)
            {
                Ch::printUnderlinedHeader("Properties:");
                /* print unused */
                if(unused.size() > 0)
                {
                    Ch::printHeaderWithCount("Used by template, but not added or defined(", unused.size());
                    Ch::printTripleList(unused, MISSING, 1);
                }

                /* print created */
                if(created.size() > 0)
                {
                    Ch::printHeaderWithCount("Used by template, but only defined(", created.size());
                    Ch::printValueList(created, CREATED, false, true, working_repo, 1);
                }

                /* print used */
                if (used.size() > 0)
                {
                    if(unused.size() == 0)
                        Ch::printHeaderWithCount("All values for your given template are available(", used.size());
                    else
                        Ch::printHeaderWithCount("Used by template and already added(", used.size());

                    Ch::printValueList(used, ADDED, true, true, working_repo, 1);
                }

                /* print needless */
                if (needless.size() > 0)
                {
                    Ch::printHeaderWithCount("Not used by template, but created/added(", needless.size());
                    Ch::printTripleList(needless, NEEDLESS, 1);
                }
            }

            /**** Collections ****/
            if (unused_colls.size() + used_colls.size() +  needless.size() > 0)
            {
                Ch::printUnderlinedHeader("Collections:");
                
                /* print used */
                if(used_colls.size() > 0)
                {
                    Ch::printHeaderWithCount("Used by template and defined(", used_colls.size());
                    Ch::printCollectionList(used_colls, ADDED, working_repo, 1, REPO, argv[0]);
                }
                
                /* print unused */
                if(unused_colls.size() > 0)
                {
                    Ch::printHeaderWithCount("Used by template and not defined(", unused_colls.size());
                    Ch::printCollectionList(unused_colls, MISSING, working_repo, 1, TEMPLATE, argv[0]);
                }

                /* print needless */
                if(needless_colls.size() > 0)
                {
                    Ch::printHeaderWithCount("Not used by template, but defined(", needless_colls.size());
                    Ch::printTripleList(needless_colls, NEEDLESS, 1);
                }
            }
        }
        else //normal mode
        {
            std::list<std::string>::const_iterator it;
            std::list<std::string> used, unused, used_colls;

            used = working_repo.GetAddedPropertiesInCwd();
            unused = working_repo.GetCreatedPropertiesInCwd();
            used_colls = working_repo.GetAddedCollectionsInCwd();

            std::cout << "Repository root path: " << working_repo.GetRepositoryPath() << std::endl << std::endl;

            if (used.size() > 0)
            {
                Ch::printHeaderWithCount("Added Properties(", used.size());

                Ch::printValueList(used, ADDED, true, true, working_repo, 1);
            }
            if (unused.size() > 0)
            {
                Ch::printHeaderWithCount("Created Properties(", unused.size());
                Ch::printTripleList(unused, CREATED, 1);
            }
            if (used_colls.size() > 0)
            {
                Ch::printHeaderWithCount("Created Collections(", used_colls.size());
                Ch::printCollectionList(used_colls, ADDED, working_repo, 1, REPO, NULL);
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
            std::cout << "There is already a repository in this or it's parent directories." << std::endl;
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
        if (!(argc == 2 || argc == 3))
        {
            dryHelpers::printRenderSynopsis();
            return;
        }

        /** variables */
        std::string file;       // template file
        std::string path;       // output file/dir
        bool force = false;     // force toggle

        /** parse input */
        if (argc == 3) // somewhere is a "-f"
        {
            if (strcmp(argv[0], "-f") == 0)
            {
                force = true;
                argc--;
                argv++;
            }
        }
        // template file
        file = *argv;
        argc--;
        argv++;
        if (argc == 2) // somewhere is a "-f"
        {
            if (strcmp(argv[0], "-f") == 0)
            {
                force = true;
                argc--;
                argv++;
            }
        }
        // getting output path
        path = *argv;
        argc--;
        argv++;
        if (argc == 1) // somewhere is a "-f"
        {
            if (strcmp(argv[0], "-f") == 0)
            {
                force = true;
                argc--;
                argv++;
            }
        }
        if (argc != 0)
        {
            std::cout << *argv << std::endl;
            dryHelpers::printRenderSynopsis();
            return;
        }

        if (!Fs::FileExists(file))
        {
            std::cout << file << " The specified template file could not be found." << std::endl;
            return;
        }

        working_repo.Load();
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
                if (force)
                {
                    Fs::FileDelete(path);
                }
                else
                {
                    std::cout << path << " The specified output directory contains already a file named like the tmeplate file." << std::endl;
                    return;
                }
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

namespace ConsoleHelper{

    void printColor(PrintMode mode)
    {
        std::cout << getColor(mode);
    }

    std::string getColor(PrintMode mode)
    {
        switch(mode)
        {
            case CREATED:   return COLOR_CLEAR;
            case MISSING:   return COLOR_RED;
            case ADDED:     return COLOR_GREEN;
            case NEEDLESS:  return COLOR_PURPLE;
        }
        return "";
    }

    void printTripleList(std::list<std::string> const& rList, PrintMode mode, int rTabSpace)
    {
        std::list<std::string> tmpList = rList;
        std::list<std::string>::const_iterator it;

        tmpList.sort();
        tmpList.unique();

        unsigned int maxLength = 0;
        for (it = tmpList.begin(); it != tmpList.end(); ++it)
            if ((*it).length() > maxLength)
                maxLength = (*it).length();

        maxLength += 2;

        printColor(mode);
        for (it = tmpList.begin(); it != tmpList.end();)
        {
            for(int i = 0; i < rTabSpace; ++i)
                std::cout << "\t";
            for(int i = 0; i < 3; ++i)
            {
                if (it == tmpList.end())
                    break;
                std::cout << *it;
                for (int j = maxLength - (*it).length(); j > 0; j--)
                    std::cout << " ";

                it++;
            }
            std::cout << std::endl;
        }
        std::cout << COLOR_CLEAR << std::endl;
    }
    void printCollElem(std::string rElem, int rTabSpace, int rows)
    {
        if(rows > 0)
            std::cout << COLOR_GREEN;
        else
            std::cout << COLOR_CLEAR;

        for(int i = 0; i < rTabSpace; ++i)
            std::cout << "\t";

        std::cout << rElem << " (" << rows << " rows), containing properties:"<< std::endl;
    }

    void printValueList(std::list<std::string> rList, PrintMode mode, bool rValues, bool rTypes, 
                        Repository working_repo, int rTabSpace)
    {
        std::list<std::string> tmpList = rList;
        std::list<std::string>::const_iterator it;

        tmpList.sort();
        tmpList.unique();

        for (it = tmpList.begin(); it != tmpList.end(); ++it)
        {
            std::string key = *it;
            std::string path, color, value, type;

            if (rValues)
                value = working_repo.GetFirstDefinedValueRec(key, Fs::GetCwd(), path);
            if (rTypes)
                type = working_repo.GetPropertyByKey(key)->GetTypeN();


            if (path == Fs::GetCwd() || !rValues)
                color = getColor(mode);
            else
                color = COLOR_CYAN;

            for(int i = 0; i < rTabSpace; ++i)
                std::cout << "\t";

            std::cout << color << key;

            if (rTypes)
                std::cout << COLOR_BLUE << "<" << type << ">";
            if (rValues)
                std::cout << color << " = " << value;

            std::cout << COLOR_CLEAR << std::endl;
        }
        std::cout << std::endl;
    }

    void printCollectionList(std::list<std::string> rList, PrintMode rMode, Repository working_repo, 
                            int rTabSpace, WorkingMode rWorkMode, std::string rTemplPath)
    {
        std::list<std::string> tmpList = rList;
        std::list<std::string>::const_iterator it;

        tmpList.sort();
        tmpList.unique();

        for (it = tmpList.begin(); it != tmpList.end(); ++it)
        {
            std::string key = *it;
            if (rWorkMode == REPO)
            {
                Coll coll;
                coll.Load(key);
                printCollElem(key, rTabSpace, coll.GetRowCount());
                printTripleList(Lh::PropertyList2KeyList(coll.GetPropertyList()), NEEDLESS, rTabSpace + 1);
            }
            else
            {
                for(int i = 0; i < rTabSpace; ++i)
                    std::cout << "\t";
                std::cout << key << ", containing elements (got from Template):" << std::endl;
                SimpleTemplate templ;
                printTripleList(templ.GetCollectionItemList(rTemplPath, key), MISSING, rTabSpace + 1);
            }
            std::cout << COLOR_CLEAR;
        }
    }

    void printHeaderWithCount(std::string header, int count)
    {
        std::cout << COLOR_BOLD << header << count << "):" << COLOR_CLEAR << std::endl;
    }

    void printHeader(std::string header)
    {
        std::cout << COLOR_BOLD << header << COLOR_CLEAR << std::endl;
    }

    void printUnderlinedHeader(std::string header)
    {
        std::cout << COLOR_BOLD << header << COLOR_CLEAR << std::endl;
        for(unsigned int i = 0; i < header.size(); i++)
            std::cout << "=";
        std::cout << std::endl;
    }
}


namespace dryHelpers {
    void printRenderSynopsis()
    {
        std::cout << "You need to specify a template and an output path.\n"
                  << "Synopsis: emp render [-f] <path-to-template> <path-to-output>\n"
                  << "                      -f   force to overwrite output\n\n";
    }
}
