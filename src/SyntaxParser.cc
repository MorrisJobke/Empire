
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
             << "  cshow        shows data rows of a given collection\n"
             << "  find         searchs for keys and containing values\n"
             << "  iadd         interactive adding of all properties in a given template\n"
             << "  remove       removes a given property from repository in working directory\n"
             << "  modify       modifies a given property from repository in working directory\n"
             << "  render       renders a file to ouput/ using repository in working directory\n"
             << "  show         gives information about a single property or collection\n"
             << "  status       gives a summary containing properties and collections\n"
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

        if (working_repo.ContainsProperty(coll_name) && !working_repo.IsCollection(coll_name))
        {
            std::cout << "The following key is already declared in repository, but not a collection: " << coll_name << std::endl;
            return;
        };

        if (Fs::DirectoryExists(coll_name))
        {
            if (working_repo.ContainsProperty(coll_name) == false)
                std::cout << "Collection dir already exists, but you have no collection property\n"
                          << "with the given name.\n";
            else
                std::cout << "Collection dir already exists\n";

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

            while (working_repo.ContainsProperty(new_key) == false)
            {
                std::cout << "The following key is not declared in repository: " << new_key << std::endl
                          << "Please enter a type for this value or press [Enter] to abort:" << std::endl;
                std::string tmpType;
                std::getline(std::cin, tmpType);
                if (tmpType == "")
                    return;
                try
                {
                    working_repo.CreatePropertyClass(new_key, tmpType);
                }
                catch (ErrorGenProperty& e)
                {
                    std::cout << COLOR_RED << "[WARNING] You entered an invalid type: " << tmpType << COLOR_CLEAR << std::endl << std::endl;
                    continue;
                }
            }

            GenPropertyBase* ext_prop = working_repo.GetPropertyByKey(new_key);

            props_to_declare.push_back(ext_prop);

            argc--;
            argv++;
        }

        Coll c(coll_name);
        try
        {
            c.Declare(props_to_declare, working_repo.GetMetaPath());
        }
        catch (CollExists)
        {
            std::cout << "A collection with this key is alredy defined." << std::endl;
        }
        catch (CollDecExists)
        {
            std::cout << "A collection with this key is alredy defined." << std::endl;
        }

        //remove created properties:
        //std::list<GenPropertyBase*>::const_iterator it;
        //for (it = props_to_declare.begin(); it != props_to_declare.end(); it++)
        //    working_repo.RemovePropertyClass((*it)->GetKey());

    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** cfill command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void coll_fill(int argc, char* argv[])
    {
        using namespace std;

        Repository working_repo;
        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }
        if (argc < 1)
        {
            std::cout << "You need to specify a collection name and  optional at least one key with value\n"
                      << "If only the collection name is given you will get an interactive mode.\n"
                      << "Synopsis: emp cfill <coll-name> [<key1>:<value1> [<key2>:<value2> ...]]\n\n";
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

        if (Fs::DirectoryExists(working_repo.GetMetaPath() + "/" + coll_name) == false)
        {
            std::cout << "You have no collection declared here called: " << coll_name << "\n";
            return;
        }

        /* skip col name */
        argc--;
        argv++;

        /* Load collection */
        Coll c(coll_name);
        c.Load(coll_name, working_repo.GetMetaPath());

        /* read entries */
        list<GenPropertyBase*> new_entries;

        if (argc != 0) //manual mode
        {
            while (argc > 0)
            {
                std::string new_pair = argv[0];

                //cout << "new pair-> " << new_pair << endl;

                /* split the pair */
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
            c.AddRow(new_entries);
        }
        else //interactive mode
        {
            //get needed propertys
            std::list<GenPropertyBase*> needed = c.GetPropertyList();
            std::list<GenPropertyBase*>::const_iterator it;

            std::string tmpValue;
            bool stop = false;
            int count = 0;
            while(!stop)
            {
                std::cout << COLOR_BOLD << "Creating a new row. Press [Enter] to abort."
                          << COLOR_CLEAR << std::endl;
                for(it = needed.begin(); it != needed.end(); it++)
                {
                    std::string key = (*it)->GetKey();
                    std::string type = (*it)->GetTypeN();
                    if(!working_repo.ContainsProperty(key))
                    {
                        try
                        {
                            working_repo.CreatePropertyClass(key, type);
                        }
                        catch(PropExistentError &exc)
                        {
                            std::cout << "PropertyClass exists." << std::endl;
                        }
                        std::cout << COLOR_RED << "[WARNING] Property " << key
                                  << " automatically redefined!" << COLOR_CLEAR << std::endl;
                    }

                    //already global defined?
                    if(working_repo.GetPropertyByKey((*it)->GetKey())->HasValue())
                        continue;

                    std::cout << "Please enter an value for " << key  << COLOR_BLUE
                              << "<" << type << ">"
                              << COLOR_CLEAR << std::endl;
                    std::getline(std::cin, tmpValue);
                    if(tmpValue == "")
                    {
                        stop = true;
                        break;
                    }
                    else
                    {
                        GenPropertyBase* new_prop = PropertyHelpers::CreatePropertyFromTypeString(type);
                        new_prop->SetKey(key);
                        new_prop->SetValueFromString(tmpValue);
                        new_entries.push_back(new_prop);
                    }
                }
                if (!stop)
                {
                    count ++;
                    c.AddRow(new_entries);
                }

            }
            std::cout << COLOR_BOLD << count << " rows added." << COLOR_CLEAR << std::endl;
        }

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
            std::cout << "This property is defined with another type." << std::endl;
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
        std::list<std::string> stringList = Lh::PropertyList2KeyList(working_repo.GetAddedProperties());
        std::list<std::string> missing = tmpl->GetMissingProperties(argv[0], stringList);
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
        if (argc != 2)
        {
            std::cout << "You need to specify a key and a value at least.\n"
                      << "Synopsis: emp modify <key> <value>\n";
            return;
        }
        try
        {
            working_repo.RemoveProperty(argv[0]);
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

    /** status command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void status(int argc, char* argv[])
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
                          << "Synopsis: emp status [<path-to-template>]\n\n";
                return;
            }

        working_repo.Load();
        std::list <std::string> addedProps = Lh::PropertyList2KeyList(working_repo.GetAddedProperties());
        std::list <std::string> createdProps = Lh::PropertyList2KeyList(working_repo.GetCreatedProperties());
        std::list <std::string> allProps = Lh::ListMerge(createdProps, addedProps);
        std::list <std::string> definedColls = Lh::PropertyList2KeyList(working_repo.GetCollections());

        if (argc != 0) //template mode
        {
            if(!Fs::FileExists(argv[0]))
            {
                std::cout << "The given paramater is not a file. Aborting." << std::endl;
                return;
            }

            SimpleTemplate* tmpl = new SimpleTemplate();
            std::list<std::string> unused, used, created, used_colls, unused_colls, needless, needless_colls;
            std::list<std::string>::const_iterator it;

            /*properties:*/
            used = tmpl->GetAvailableProperties(argv[0], addedProps);
            unused = tmpl->GetMissingProperties(argv[0], allProps);
            created = tmpl->GetAvailableProperties(argv[0], createdProps);
            needless = tmpl->GetUnusedProperties(argv[0], allProps);

            /*collections:*/
            used_colls = tmpl->GetAvailableCollections(argv[0], definedColls);
            unused_colls = tmpl->GetMissingCollections(argv[0], definedColls);
            needless_colls =  tmpl->GetUnusedCollections(argv[0], definedColls);

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
                    Ch::printValueList(created, CREATED, false, true, false, working_repo, 1);
                }

                /* print used */
                if (used.size() > 0)
                {
                    if(unused.size() == 0)
                        Ch::printHeaderWithCount("All values for your given template are available(", used.size());
                    else
                        Ch::printHeaderWithCount("Used by template and already added(", used.size());

                    Ch::printValueList(used, ADDED, true, true, true, working_repo, 1);
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
                    Ch::printCollectionList(used_colls, CREATED, working_repo, 1, REPO, argv[0]);
                }

                /* print unused */
                if(unused_colls.size() > 0)
                {
                    Ch::printHeaderWithCount("Used by template and not defined(", unused_colls.size());
                    Ch::printCollectionList(unused_colls, CREATED, working_repo, 1, TEMPLATE, argv[0]);
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
            std::cout << "Repository root path: " << working_repo.GetRepositoryPath() << std::endl << std::endl;

            if (addedProps.size() > 0)
            {
                Ch::printHeaderWithCount("Added Properties(", addedProps.size());

                Ch::printValueList(addedProps, ADDED, true, true, true, working_repo, 1);
            }
            if (createdProps.size() > 0)
            {
                Ch::printHeaderWithCount("Created Properties(", createdProps.size());
                Ch::printTripleList(createdProps, CREATED, 1);
            }
            if (definedColls.size() > 0)
            {
                Ch::printHeaderWithCount("Defined Collections(", definedColls.size());
                Ch::printCollectionList(definedColls, CREATED, working_repo, 1, REPO, "");
            }
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
        if (argc != 1)
        {
            std::cout << "This command needs a key as parameter.\n"
                      << "Synopsis: emp show <key>\n\n";
            return;
        }
        std::string key = argv[0];
        working_repo.Load();
        if(!working_repo.ContainsProperty(key))
        {
            std::cout << "The given key is not a property or collection." << std::endl;
            return;
        }

        GenPropertyBase* prop = working_repo.GetPropertyByKey(key);
        bool isCollection = prop->GetTypeN() == GetTypeName<Coll>();

        std::cout << "Key            = " << prop->GetKey() << std::endl;
        std::cout << "Type           = " << prop->GetTypeN() << std::endl;

        if (prop->HasValue() && !isCollection)
        {
            std::cout << "Value          = " << working_repo.GetPropertyValue(key) << std::endl;
            std::cout << "value path     = " << prop->GetPath() << std::endl;
            std::cout << "Creation time  = " << Ch::TimeToString(Fs::GetFileCreationDate(prop->GetPath())) << std::endl;
        }
        else if (isCollection)
        {
            GenProperty<Coll>* collProp = (GenProperty<Coll>*) prop;
            Coll collection = collProp->GetValue();
            std::cout << "Data row count = " << collection.GetRowCount() << std::endl;
            std::cout << std::endl << "Containing Propertys:" << std::endl;
            Ch::printTripleList(Lh::PropertyList2KeyList(collection.GetPropertyList()), CREATED, 1);
            std::cout << "Use the cshow command to get a list of the collection items." << std::endl;
        }
        else
            std::cout << "Value         = " << "NO VALUE SET" << std::endl;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** cshow command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void coll_show(int argc, char* argv[])
    {
        Repository working_repo;

        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }

        if (argc == 0)
        {
            std::cout << "This command needs a collection key as parameter.\n"
                      << "Optionally you could specify a key and a value and it only prints\n"
                      << "collection rows where the specified value matches\n"
                      << "Synopsis: emp cshow <collection> [<key1>:<value1> [<key2>:<value2>] ...]\n\n";
            return;
        }

        std::string collKey = argv[0];

        working_repo.Load();
        if (!working_repo.ContainsProperty(collKey))
        {
            std::cout << "There is no collection with this name." << std::endl;
            return;
        }

        GenPropertyBase* prop = working_repo.GetPropertyByKey(collKey);
        if(prop->GetTypeN() != GetTypeName<Coll>())
        {
            std::cout << "Key exists in repository, but is no collection." << std::endl;
            return;
        }

        GenProperty<Coll>* collProp = (GenProperty<Coll>*) prop;
        Coll collection = collProp->GetValue();

        argc --;
        argv ++;

        std::list<std::string> showProp;
        std::list<std::string> wanted_val;

        while(argc > 0)
        {
            std::string keyValueComb = argv[0];
            argc --;
            argv ++;

            int found = keyValueComb.find(':');
            if (found == std::string::npos) //no value given
            {
                showProp.push_back(keyValueComb);
                wanted_val.push_back("");
            }
            else
            {
                showProp.push_back(keyValueComb.substr(0, found));
                wanted_val.push_back(keyValueComb.substr(found + 1, keyValueComb.size()));
            }
        }

        std::list< std::list<GenPropertyBase*> > itemList = collection.GetList();
        std::list< std::list<GenPropertyBase*> >::const_iterator rows;
        std::list<GenPropertyBase*>::const_iterator items;
        std::list<std::string>::const_iterator showPropIt, wanted_valIt;
        std::list< std::list<GenPropertyBase*> > matches;

        for(rows = itemList.begin(); rows != itemList.end(); ++rows)
        {
            std::string rowPrint = "";
            std::list<GenPropertyBase*> actRow = *rows;
            for(items = actRow.begin(); items != actRow.end(); ++items)
            {
                bool printTrig = true;
                std::string itemKey = (*items)->GetKey();
                std::string itemVal;
                if((*items)->HasValue())
                    itemVal = PropertyHelpers::GetPropertyValueAsString((*items));

                wanted_valIt = wanted_val.begin();
                for (showPropIt = showProp.begin(); showPropIt != showProp.end() && printTrig; showPropIt ++)
                {
                    if((*showPropIt) == itemKey)
                    {
                        if((*wanted_valIt) == itemVal)
                            matches.push_back(*rows);
                    }
                    wanted_valIt++;
                }
            }
        }

        /* printing: */
        int row = 0;
        matches.unique(); //ignore double found
        for(rows = matches.begin(); rows != matches.end(); rows++)
        {
            std::cout << "Result Row " << row << ":" << std::endl;

            std::list<GenPropertyBase*> actRow = *rows;
            for(items = actRow.begin(); items != actRow.end(); ++items)
            {
                std::cout << (*items)->GetKey();
                std::cout << COLOR_BLUE << "<" << (*items)->GetTypeN() << ">";
                std::cout << COLOR_CLEAR << " = " << PropertyHelpers::GetPropertyValueAsString(*items)
                          << std::endl;
            }
            row ++;
            std::cout << std::endl;
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
        if (argc < 1 || argc > 3)
        {
            DryHelpers::printRenderSynopsis();
            return;
        }

        /** variables */
        std::string file;       // template file
        std::string path = ".";       // output file/dir
        bool force = false;     // force toggle

        /** parse input */
        if (strcmp(argv[0], "-f") == 0)
        {
            force = true;
            argc--;
            argv++;
        }
        if (argc == 0)
        {
            DryHelpers::printRenderSynopsis();
            return;
        }
        // template file
        file = *argv;
        argc--;
        argv++;
        if (argc != 0) // somewhere is a "-f"
        {
            if (strcmp(argv[0], "-f") == 0)
            {
                force = true;
                argc--;
                argv++;
            }
            if (argc != 0)
            {
                // getting output path
                path = *argv;
                argc--;
                argv++;
            }
        }

        if (argc != 0) // somewhere is a "-f"
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
            DryHelpers::printRenderSynopsis();
            return;
        }

        if (!Fs::FileExists(file))
        {
            std::cout << file << ": The specified template file could not be found." << std::endl;
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
                if (force)
                {
                    Fs::FileDelete(path + "/" + filename);
                }
                else
                {
                    std::cout << path + "/" + filename << ": The specified output file exists." << std::endl;
                    return;
                }
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
                    std::cout << path << ": The specified output directory contains already a file named like the tmeplate file." << std::endl;
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
        bool isTexFile = RegexHelper::MatchesRegex(path,".*\\.tex");

        if (isTexFile)
        {
            /*run pdflatex*/
            bool pdfLatexInstalled = system("which pdflatex &> /dev/null") == 0;
            if(pdfLatexInstalled)
            {
                std::string executeLine = "pdflatex -interaction batchmode -no-shell-escape " + path
                                    + ">" + path + ".log";
                std::cout << "pdflatex was found, created pdf from rendered .tex file" << std::endl;
                system(executeLine.c_str());
            }
            else
                std::cout << "pdflatex was not found, no pdf created..." << std::endl;
        }
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
            working_repo.Load();
            try
            {
                if(argc == 2)
                    working_repo.RemovePropertyClassAndInstances(argv[1]);
                else
                    working_repo.RemoveProperty(argv[0]);
            }
            catch (PropNotExists& e)
            {
                std::cout << "The specified property doesn't exist in this directory.\n";
                return;
            }
           catch (PropClassNotExists& e)
            {
                std::cout << "The specified property doesn't exist in this repository.\n";
                return;
            }
        }
    }


    /** find command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void find(int argc, char* argv[])
    {
        Repository working_repo;
        if (!working_repo.IsExistent())
        {
            std::cout << "There isn't any repository in this or it's parent directories." << std::endl;
            return;
        }
        if (argc < 1 || argc > 2)
        {
            std::cout << "You need to specify a key (use ALL if you want to search all keys).\n"
                      << "Optionally you could specify a part of the\n"
                      << "value you are searching for.\n"
                      << "Synopsis: emp find <key> [<part of value>]\n\n";
            return;
        }
        else
        {
            std::string exeQuery;
            std::string key, value;

            key = argv[0];

            if(argc == 2)
            {
                value = argv[1];
                if(key == "ALL")
                    exeQuery = "find . \\! -path \"*/*.*\" -type f -print0 | xargs -0 grep \"" + value + "\"";
                else
                    exeQuery = "find . \\! -path \"*/*.*\" -type f -name \"" + key + "\" -print0 | xargs -0 grep \"" + value + "\"";
            }
            else
            {
                if(key == "ALL")
                    exeQuery = "find . \\! -path \"*/*.*\"";
                else
                    exeQuery = "find . \\! -path \"*/*.*\" -name \"" + key + "\"";
            }

            //std::cout << exeQuery << std::endl;
            system(exeQuery.c_str());
        }
    }
}

namespace ConsoleHelper{

    /** prints a color for given mode
     *
     * @param mode given mode
     */
    void printColor(PrintMode mode)
    {
        std::cout << getColor(mode);
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** returns a color for given mode
     *
     * @param mode given mode
     * @return a color
     */

    std::string getColor(PrintMode mode)
    {
        switch(mode)
        {
            case CREATED:   return COLOR_CLEAR;
            case MISSING:   return COLOR_RED;
            case ADDED:     return COLOR_GREEN;
            case NEEDLESS:  return COLOR_PURPLE;
        }
        return COLOR_CLEAR;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** prints a list with 3 colls
     *
     * @param rList list of the strings, that should be printed
     * @param rTabSpace count of tab spaces the output should have at begin of the lines
     * @param mode the mode for printing
     */
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** prints a line with the collection key
     *
     * @param rElem key of the collection
     * @param rTabSpace count of tab spaces the output should have at begin of the lines
     * @param rows count of data-rows of the collection
     */
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** prints a list of values (with different options)
     *
     * @param rList list of property keys
     * @param mode the mode for printing
     * @param rValues should it print values?
     * @param rTypes should it print types?
     * @param rTypes should it print the count of dirs to value definition?
     * @param working_repo the repository
     * @param rTabSpace count of tab spaces the output should have at begin of the lines
     */
    void printValueList(std::list<std::string> rList, PrintMode mode, bool rValues, bool rTypes, bool rDirDiff,
                        Repository working_repo, int rTabSpace)
    {
        std::list<std::string> tmpList = rList;
        std::list<std::string>::const_iterator it;

        tmpList.sort();
        tmpList.unique();

        for (it = tmpList.begin(); it != tmpList.end(); ++it)
        {
            std::string key = *it;
            std::string color, value, type;
            int dirDiff;

            GenPropertyBase* prop = working_repo.GetPropertyByKey(key);

            bool path = working_repo.IsPropertyInCwd(key);
            if (rValues)
                value = working_repo.GetPropertyValue(key);
            if (rTypes)
                type = prop->GetTypeN();
            if (rDirDiff)
                dirDiff = Fs::GetDirectoryDifference(Fs::GetCwd(), prop->GetPath());
            if (path == true)
                color = getColor(mode);
            else
                color = COLOR_CYAN;

            for(int i = 0; i < rTabSpace; ++i)
                std::cout << "\t";

            std::cout << color << key;

            if (rTypes)
            {
                if(type == "std::string"){ type = "string"; }
                std::cout << COLOR_BLUE << "<" << type << ">";
            }
            if (rDirDiff && !path)
                std::cout << color << "(" << '^' << dirDiff << ") ";
            if (rValues)
                std::cout << COLOR_CLEAR << " = " << value;

            std::cout << COLOR_CLEAR << std::endl;
        }
        std::cout << std::endl;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** prints a list of collections
     *
     * @param rList list of class keys
     * @param rMode the mode for printing
     * @param rTabSpace count of tab spaces the output should have at begin of the lines
     * @param rWorkMode the WorkingMode
     * @param working_repo the repository
     * @param rTemplPath the path of the template
     */
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
                coll.Load(key, working_repo.GetMetaPath());
                printCollElem(key, rTabSpace, coll.GetRowCount());
                printTripleList(Lh::PropertyList2KeyList(coll.GetPropertyList()), rMode, rTabSpace + 1);
            }
            else
            {
                SimpleTemplate templ;
                std::list<std::string> tmp = templ.GetCollectionItemList(rTemplPath, key);
                std::list<std::string> out;
                std::list<std::string>::const_iterator it2;
                for (it2 = tmp.begin(); it2 != tmp.end(); it2++)
                    if(working_repo.ContainsProperty(*it2))
                    {
                        GenPropertyBase* prop = working_repo.GetPropertyByKey(*it2);
                        if(prop->GetTypeN() != GetTypeName<FunctionType>())
                            out.push_back(*it2);
                    }
                    else
                        out.push_back(*it2);

                for(int i = 0; i < rTabSpace; ++i)
                    std::cout << "\t";
                std::cout << key << ", containing elements (got from Template):" << std::endl;
                printTripleList(out, rMode, rTabSpace + 1);
            }
            std::cout << COLOR_CLEAR;
        }
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** prints a header for a list with count
     *
     * @param header the title of the header
     * @param count count of the elements in the following list
     */
    void printHeaderWithCount(std::string header, int count)
    {
        std::cout << COLOR_BOLD << header << count << "):" << COLOR_CLEAR << std::endl;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** prints a header for a list without count
     *
     * @param header the title of the header
     */
    void printHeader(std::string header)
    {
        std::cout << COLOR_BOLD << header << COLOR_CLEAR << std::endl;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** prints a underlinde header
     *
     * @param header the title of the header
     */
    void printUnderlinedHeader(std::string header)
    {
        std::cout << COLOR_BOLD << header << COLOR_CLEAR << std::endl;
        for(unsigned int i = 0; i < header.size(); i++)
            std::cout << "=";
        std::cout << std::endl;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** converts time to string
     *
     * @param time the given time
     * @return time string
     */

    std::string TimeToString(struct tm* time)
    {
        std::stringstream ss;
        ss << time->tm_year + 1900 << "-";
        int month = time->tm_mon;
        if (month < 10)
            ss << "0";
        ss << month << "-";

        int day = time->tm_mday;
        if (day < 10)
            ss << "0";

        ss << day;

        return ss.str();
    }
}


namespace DryHelpers {
    /** prints synopsis of emp render subfunction
     */
    void printRenderSynopsis()
    {
        std::cout << "You need to specify a template.\n"
                  << "Synopsis: emp render [-f] <path-to-template> [<path-to-output>]\n"
                  << "                      -f   force to overwrite output\n\n";
    }
}
