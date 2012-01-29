
/* Template.h
 * @Author:      Brainafk
 * @License:     GPL
 * @Created:     11.01.2012.
 * @Editor:      Sublime Text 2
 */

#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <string>
#include <list>
#include <map>
#include <sstream>

#include "GenProperty.h"
#include "FunctionType.h"
#include "LuaHelper.h"
#include "ListHelper.h"
#include "Filesystem.h"

/** interface of template
 */
class ITemplate
{
public:
    virtual ~ITemplate() {}

    /** add a property for use in the template
     *
     * @param property the property
     */
    virtual void AddProperty(GenPropertyBase* property) = 0;
    /** add a list of properties for use in the template
     *
     * @param properties the properties
     */
    virtual void AddProperties(std::list<GenPropertyBase*> properties) = 0;

    /** parse a string
     *
     * @param input the string to parse
     * @param output the parsed result
     */
    virtual void ParseString(std::string const& input, std::string& output) = 0;
    /** parse a string obtained from a file
     *
     * @param path the path to the file which content should be parsed
     * @param output the parsed result
     */
    virtual void ParseFile(std::string const& path, std::string& output) = 0;

};

/** simple implementation of template
 */
class SimpleTemplate : public ITemplate
{
private:
    enum Behavior { EAT, GATHER };
    enum Expectation { ALPHANUM, NONECOLLECTIONEND };

    std::map<std::string, GenPropertyBase*> mProperties;

    void InjectPropertiesIntoLuaContext(std::map<std::string, GenPropertyBase*> properties, LuaContext* context);
    void InjectPropertiesIntoLuaContext(std::list<GenPropertyBase*> properties, LuaContext* context);

public:
    virtual void AddProperty(GenPropertyBase* property);
    virtual void AddProperties(std::list<GenPropertyBase*> properties);

    virtual void ParseString(std::string const& input, std::string& output);
    virtual void ParseFile(std::string const& path, std::string& output);
    std::list<std::string> GetKeyList(std::string const& path);
    std::list<std::string> GetCollectionList(std::string const& rPath);
    std::list<std::string> GetCollectionItemList(std::string const& rPath, std::string const& rName);
    std::list<std::string> GetAvailableProperties(std::string const& rPath, std::list<std::string> const& rAvailable);
    std::list<std::string> GetMissingProperties(std::string const& rPath, std::list<std::string> const& rAvailable);
    std::list<std::string> GetUnusedProperties(std::string const& rPath, std::list<std::string> const& rAvailable);
    std::list<std::string> GetAvailableCollections(std::string const& rPath, std::list<std::string> const& rAvailableColls);
    std::list<std::string> GetMissingCollections(std::string const& rPath, std::list<std::string> const& rAvailableColls);
    std::list<std::string> GetUnusedCollections(std::string const& rPath, std::list<std::string> const& rAvailableColls);
    std::list<std::string> GetAllKeys(std::string const& rPath);

};

#endif
