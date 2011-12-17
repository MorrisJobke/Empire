
/* PropertyInteger.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-16.
 * @Editor:      Vim
 */

#ifndef PROPERTYFLOAT_H
#define PROPERTYFLOAT_H

#ifndef PROPERTY_H
#include "Property.cc"
#endif

#include <string>
using namespace std;

class PropertyFloat : public Property<double>
{
public:
    ~PropertyFloat();

    PropertyFloat(double value);
    PropertyFloat(string const& key, double value);
    PropertyFloat(string const& key, string const& description, double value);
};

#endif