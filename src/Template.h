
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


class ITemplate
{
public:
    virtual ~ITemplate() {}

    virtual void AddProperty(GenProperty* property) = 0;
    virtual void AddProperties(std::list<GenProperty*> properties) = 0;

    virtual void ParseString(std::string const& input, std::string& output) = 0;
    virtual void ParseFile(std::string const& path, std::string& output) = 0;
};

class SimpleTemplate : public ITemplate
{
private:
  enum Behavior { EAT, GATHER };
  enum Expectation { ALPHANUM };

  std::map<std::string, GenProperty*> mProperties;

public:
    virtual void AddProperty(GenProperty* property);
    virtual void AddProperties(std::list<GenProperty*> properties);

    virtual void ParseString(std::string const& input, std::string& output);
    virtual void ParseFile(std::string const& path, std::string& output);
};

#endif
