
/* PropertyInteger.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-16.
 * @Editor:      Vim
 */

#ifndef PROPERTYFLOAT_H
#define PROPERTYFLOAT_H

#include "Property.cc"

#include <string>
using namespace std;

class PropertyFloat : public Property<float>
{
public:
    ~PropertyFloat();

    PropertyFloat(float value);
    PropertyFloat(string const& key, float value);
    PropertyFloat(string const& key, string const& description, float value);
};

#endif