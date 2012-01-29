
/* Template.cc
 * @Author:      Brainafk
 * @License:     GPL
 * @Created:     11.01.2012.
 * @Editor:      Sublime Text 2
 */

#include "Template.h"

using namespace std;


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/
/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/

/** add a property for use in the template
 *
 * @param property the property
 */
void SimpleTemplate::AddProperty(GenPropertyBase* property)
{
    if (mProperties.count(property->GetKey()) > 0)
    {
        mProperties.erase(property->GetKey());
    }

    mProperties.insert(pair<string, GenPropertyBase*>(property->GetKey(), property));
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** add a list of properties for use in the template
 *
 * @param properties the properties
 */
void SimpleTemplate::AddProperties(list<GenPropertyBase*> properties)
{
    list<GenPropertyBase*>::iterator it;
    for (it = properties.begin(); it != properties.end(); it++) {
        if ((*it)->HasValue())
        {
            this->AddProperty(*it);
        }
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** parse a string
 *
 * @param input the string to parse
 * @param output the parsed result
 */
void SimpleTemplate::ParseString(string const& input, string& output)
{
    ostringstream result;
    string gathered;
    std::list< std::list<GenPropertyBase*> > collection;
    SimpleTemplate::Behavior behavior = EAT;
    SimpleTemplate::Expectation expectation = ALPHANUM;
    LuaHelper* helper = new LuaHelper();

    string::const_iterator it;
    it = input.begin();
    // TODO: parse variable at end of string fails
    while (it < input.end()) {
        switch (behavior) {
            case EAT:
                // Variables in template start with @
                if (*it == '@') {
                    if (*(it + 1) == '@') {
                        it++;
                        result << '@';
                    } else {
                        behavior = GATHER;
                        expectation = ALPHANUM;
                    }
                } else {
                    result << *it;
                }

                it++;

                break;
            case GATHER:
                switch (expectation) {
                    case ALPHANUM:
                        if (isalnum(*it) || *it == '_') {
                            gathered += *it;
                            it++;
                        } else if (*it == '{' && mProperties[gathered] &&
                                   mProperties[gathered]->GetTypeN() == GetTypeName<Coll>()) { // Collection
                            Coll coll = ((GenProperty<Coll>*)mProperties[gathered])->GetValue();
                            collection = coll.GetList();
                            behavior = GATHER;
                            expectation = NONECOLLECTIONEND;
                            gathered = "";
                            it++;
                        } else { // variable found
                            GenPropertyBase* property = mProperties[gathered];
                            if (property) {
                                if (property->GetTypeN() == GetTypeName<FunctionType>())
                                {
                                    GenProperty<FunctionType>* funcProperty = (GenProperty<FunctionType>*) property;
                                    LuaContext* context = helper->CreateContext();

                                    // adding Properties to context - white list
                                    InjectPropertiesIntoLuaContext(mProperties, context);

                                    // execute function
                                    try
                                    {
                                        double value = 0;
                                        context->Execute(funcProperty->GetValue().GetMapFunction(), value);
                                        delete context;
                                        
                                        char r[100];
                                        sprintf(r, "%.2f", value);
                                        result << r;
                                    }
                                    catch (LuaException)
                                    {
                                        delete context;

                                        bool successfull_map = true;
                                        // search for collections
                                        GenPropertyBase* prop;
                                        std::map<std::string, GenPropertyBase*>::iterator mapit;

                                        for (mapit = mProperties.begin(); mapit != mProperties.end(); mapit++) {
                                            prop = mapit->second;
                                            if (prop != NULL)
                                            {
                                                if (prop->GetTypeN() == GetTypeName<Coll>())
                                                {
                                                    // list with map results to reduce
                                                    std::list<double> results;
                                                    // collection found - try to calculate function
                                                    std::list< std::list<GenPropertyBase*> > list = ((GenProperty<Coll>*)prop)->GetValue().GetList();
                                                    std::list< std::list<GenPropertyBase*> >::iterator properties;
                                                    for (properties = list.begin(); properties != list.end(); ++properties) {
                                                        // context for map function
                                                        LuaContext* context_map = helper->CreateContext();
                                                        // assign properties to it
                                                        InjectPropertiesIntoLuaContext(mProperties, context_map);
                                                        InjectPropertiesIntoLuaContext(*properties, context_map);

                                                        try
                                                        {
                                                            double value;
                                                            context_map->Execute(funcProperty->GetValue().GetMapFunction(), value);
                                                            results.push_back(value);
                                                        }
                                                        catch (LuaException)
                                                        {
                                                            successfull_map = false;
                                                            break;
                                                        }
                                                        
                                                        delete context_map;
                                                    }
                                                    
                                                    if (successfull_map)
                                                    {
                                                        // reduce results
                                                        std::list<double>::iterator it;
                                                        double value = 0;
                                                        for(it = results.begin(); it != results.end(); ++it) {
                                                            // context for reduce function
                                                            LuaContext* context = helper->CreateContext();
                                                            context->AddVariable("lhs", value);
                                                            context->AddVariable("rhs", *it);
                                                            context->Execute(funcProperty->GetValue().GetReduceFunction(), value);
                                                            delete context;
                                                        }

                                                        if (value != 0)
                                                        {
                                                            char r[100];
                                                            sprintf(r, "%.2f", value);
                                                            result << r;
                                                            break;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if (!successfull_map)
                                        {
                                            //TODO
                                            std::cout << "function (" << gathered << "): calculating function failed\n\tMay there a some missing properties to calculate it." << std::endl;
                                        }
                                    }
                                }
                                else if (property->GetTypeN() == GetTypeName<Coll>())
                                {
                                    // eat it :)
                                    std::cout << "[WARNING] property " << gathered << "is a collection, but the template contains a wrong syntax for this collection." << std::endl;
                                }
                                else
                                {
                                    std::string propertyValue = property->ToString();
                                    result << propertyValue;
                                }
                            }

                            // reset behavior
                            behavior = EAT;
                            gathered = "";

                            // btw do not increament it !
                            // because we have to eat this non alpha character
                        }
                        break;
                    case NONECOLLECTIONEND:
                        if (gathered == "" && *it == '\n') {
                            // swallow first \n
                        } else if (*it != '}') {
                            gathered += *it;
                        } else {
                            // for each list of properties
                            std::list< std::list<GenPropertyBase*> > list = collection;
                            std::list< std::list<GenPropertyBase*> >::iterator properties;
                            for (properties = list.begin(); properties != list.end(); properties++) {
                                // create new SimpleTemplate instance,
                                SimpleTemplate* tmpl = new SimpleTemplate();

                                // assign base properties to it
                                std::map<std::string, GenPropertyBase*>::iterator mapit;
                                GenPropertyBase* prop;
                                for (mapit = mProperties.begin(); mapit != mProperties.end(); mapit++) {
                                    prop = mapit->second;
                                    if (prop != NULL)
                                    {
                                        tmpl->AddProperty(prop);
                                    }
                                }

                                // assign collection properties to it
                                std::list<GenPropertyBase*>::iterator property;
                                for (property = properties->begin(); property != properties->end(); property++) {
                                    tmpl->AddProperty(*property);
                                }

                                // assign also all functions
                                for (mapit = mProperties.begin(); mapit != mProperties.end(); mapit++) {
                                    prop = mapit->second;
                                    if (prop != NULL && prop->GetTypeN() == GetTypeName<FunctionType>())
                                    {
                                        tmpl->AddProperty(prop);
                                    }
                                }

                                // and render it ...
                                string output;
                                tmpl->ParseString(gathered, output);
                                result << output;
                            }

                            // reset behavior
                            behavior = EAT;
                            gathered = "";
                        }

                        it++;
                        break;
                }
                break;
        }
    }

    output = result.str();
    delete helper;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** parse a string obtained from a file
 *
 * @param path the path to the file which content should be parsed
 * @param output the parsed result
 */
void SimpleTemplate::ParseFile(string const& path, string& output)
{
    string result;
    ParseString(Filesystem::FileReadString(path), result);
    output = result;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** get a list of properties in a given template
 *
 * @param path the path to the file which content should be parsed
 * @return list of properties
 */
std::list<std::string> SimpleTemplate::GetKeyList(std::string const& path)
{
    std::string propNameBuffer;
    std::list<std::string> propertyList;
    std::string input = Filesystem::FileReadString(path);

    string::const_iterator it;
    it = input.begin();
    // TODO: parse variable at end of string fails
    while (it < input.end())
    {
        if (*it == '@')
        {
            if (*(it + 1) == '@') //ignoring @@
            {
                it++;
            }
            else
            {
                it++;
                propNameBuffer = "";
                while(isalnum(*it) || *it == '_')
                {
                    propNameBuffer += *it;
                    it++;
                }
                if (*it == '{') //ignore Collections
                    while(*it != '}')
                        it++;
                else
                    propertyList.push_back(propNameBuffer);
            }
        }
        it++;
    }

    propertyList.sort();
    propertyList.unique();
    return propertyList;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** get a list of all keys of collections, properties and collection items
 *
 * @param rPath the path to the file of the template
 * @return list of keys
 */
std::list<std::string> SimpleTemplate::GetAllKeys(std::string const& rPath)
{
    std::list<std::string> result;
    std::list<std::string>::const_iterator it;
    std::list<std::string> colls = this->GetCollectionList(rPath);

    for (it = colls.begin(); it != colls.end(); it++)
        result = ListHelper::ListMerge(result, this->GetCollectionItemList(rPath, *it));

    result = ListHelper::ListMerge(result, colls);
    result = ListHelper::ListMerge(result, this->GetKeyList(rPath));

    return result;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** get a list of collections in a given template
 *
 * @param rPath the path to the file of the template
 * @return list of collection keys
 */
std::list<std::string> SimpleTemplate::GetCollectionList(std::string const& rPath)
{
    std::string collNameBuffer;
    std::list<std::string> collList;
    std::string input = Filesystem::FileReadString(rPath);

    string::const_iterator it;
    it = input.begin();
    // TODO: parse variable at end of string fails
    while (it < input.end())
    {
        if (*it == '@')
        {
            if (*(it + 1) == '@') //ignoring @@
            {
                it++;
            }
            else
            {
                it++;
                collNameBuffer = "";
                while(isalnum(*it) || *it == '_')
                {
                    collNameBuffer += *it;
                    it++;
                }
                if (*it == '{')
                    collList.push_back(collNameBuffer);
            }
        }
        it++;
    }

    collList.sort();
    collList.unique();
    return collList;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** get a list of properties that the given collection contains
 *
 * @param rPath the path to the file of the template
 * @param rName name of the collection
 * @return list of property-keys
 */
std::list<std::string> SimpleTemplate::GetCollectionItemList(std::string const& rPath, std::string const& rName)
{
    std::string collNameBuffer, propNameBuffer;
    std::list<std::string> propList;
    std::string input = Filesystem::FileReadString(rPath);

    string::const_iterator it;
    it = input.begin();
    // TODO: parse variable at end of string fails
    while (it < input.end())
    {
        if (*it == '@')
        {
            if (*(it + 1) == '@') //ignoring @@
                it++;
            else
            {
                it++;
                collNameBuffer = "";
                while(isalnum(*it) || *it == '_')
                {
                    collNameBuffer += *it;
                    it++;
                }
                if (*it == '{')
                    if (collNameBuffer == rName)    /* begin of collection found */
                        while (*it != '}' && it < input.end())
                        {
                            if (*it == '@')
                            {
                                if (*(it + 1) == '@') //ignoring @@
                                    it++;
                                else
                                {
                                    it++;
                                    propNameBuffer = "";
                                    while(isalnum(*it) || *it == '_')
                                    {
                                        propNameBuffer += *it;
                                        it++;
                                    }
                                    propList.push_back(propNameBuffer);
                                }
                            }
                            it++;
                        }
            }
        }
        it++;
    }
    propList.sort();
    propList.unique();
    return propList;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** get a list of properties that are used by the template, but not defined
 *
 * @param rPath the path to the file of the template
 * @param rAvailable already defined properties
 * @return list of property-keys
 */
std::list<std::string> SimpleTemplate::GetMissingProperties(std::string const& rPath, std::list<std::string> const& rAvailable)
{
    return ListHelper::ListCompare(this->GetKeyList(rPath), rAvailable, true);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** get a list of properties that are used by the template and also defined
 *
 * @param rPath the path to the file of the template
 * @param rAvailable already defined properties
 * @return list of property-keys
 */
std::list<std::string> SimpleTemplate::GetAvailableProperties(std::string const& rPath, std::list<std::string> const& rAvailable)
{
    return ListHelper::ListCompare(this->GetKeyList(rPath), rAvailable, false);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** get a list of properties that are not used by the template, but defined
 *
 * @param rPath the path to the file of the template
 * @param rAvailable already defined properties
 * @return list of property-keys
 */
std::list<std::string> SimpleTemplate::GetUnusedProperties(std::string const& rPath, std::list<std::string> const& rAvailable)
{
    return ListHelper::ListCompare(rAvailable, this->GetAllKeys(rPath), true);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** get a list of collections that are used by the template and also defined
 *
 * @param rPath the path to the file of the template
 * @param rAvailableColls list of already defined collections
 * @return list of collection keys
 */
std::list<std::string> SimpleTemplate::GetAvailableCollections(std::string const& rPath, std::list<std::string> const& rAvailableColls)
{
    return ListHelper::ListCompare(this->GetCollectionList(rPath), rAvailableColls, false);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** get a list of collections that are used by the template and undefined
 *
 * @param rPath the path to the file of the template
 * @param rAvailableColls list of already defined collections
 * @return list of collection keys
 */
std::list<std::string> SimpleTemplate::GetMissingCollections(std::string const& rPath, std::list<std::string> const& rAvailableColls)
{
    return ListHelper::ListCompare(this->GetCollectionList(rPath), rAvailableColls, true);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** get a list of collections that are not by the template, but available
 *
 * @param rPath the path to the file of the template
 * @param rAvailableColls list of already defined collections
 * @return list of collection keys
 */
std::list<std::string> SimpleTemplate::GetUnusedCollections(std::string const& rPath, std::list<std::string> const& rAvailableColls)
{
    return ListHelper::ListCompare(rAvailableColls, this->GetCollectionList(rPath), true);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** inject given properties into given Lua context
 *
 * @param properties the properties which should be injected
 * @param context the Lua context which got the fiven properties injected
 */
void SimpleTemplate::InjectPropertiesIntoLuaContext(std::map<std::string, GenPropertyBase*> properties, LuaContext* context)
{
    std::list<GenPropertyBase*> list;

    std::map<std::string, GenPropertyBase*>::iterator mapit;
    GenPropertyBase* prop;
    for (mapit = properties.begin(); mapit != properties.end(); mapit++) {
        prop = mapit->second;
        if (prop != NULL)
        {
            list.push_back(prop);
        }
    }

    InjectPropertiesIntoLuaContext(list, context);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** inject given properties into given Lua context
 *
 * @param properties the properties which should be injected
 * @param context the Lua context which got the fiven properties injected
 */
void SimpleTemplate::InjectPropertiesIntoLuaContext(std::list<GenPropertyBase*> properties, LuaContext* context)
{
    std::list<GenPropertyBase*>::iterator property;
    for (property = properties.begin(); property != properties.end(); property++) {
        std::string type = (*property)->GetTypeN();
        if (type == GetTypeName<int>())
        {
            GenProperty<int>* cast_prop = (GenProperty<int>*) (*property);
            context->AddVariable(cast_prop->GetKey(), cast_prop->GetValue());
        }
        if (type == GetTypeName<float>())
        {
            GenProperty<float>* cast_prop = (GenProperty<float>*) (*property);
            context->AddVariable(cast_prop->GetKey(), cast_prop->GetValue());
        }
        if (type == GetTypeName<double>())
        {
            GenProperty<double>* cast_prop = (GenProperty<double>*) (*property);
            context->AddVariable(cast_prop->GetKey(), cast_prop->GetValue());
        }
    }
}

/*============================= ACCESS     =================================*/
/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
