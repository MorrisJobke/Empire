
/* PropertyString.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-16.
 * @Editor:      Vim
 */

#ifndef PROPERTYSTRING_H
#define PROPERTYSTRING_H

#include "Property.cc"

#include <string>
using namespace std;

class PropertyString : public Property<string>
{
public:
    ~PropertyString();

    PropertyString(string value);
    PropertyString(string const& key, string value);
    PropertyString(string const& key, string const& description, string value);
};

#endif