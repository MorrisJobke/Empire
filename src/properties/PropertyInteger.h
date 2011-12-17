
/* PropertyInteger.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-16.
 * @Editor:      Vim
 */

#ifndef PROPERTYINTEGER_H
#define PROPERTYINTEGER_H

#ifndef PROPERTY_H
#include "Property.cc"
#endif

#include <string>
using namespace std;

class PropertyInteger : public Property<int>
{
public:
    ~PropertyInteger();

    PropertyInteger(int value);
    PropertyInteger(string const& key, int value);
    PropertyInteger(string const& key, string const& description, int value);
};

#endif