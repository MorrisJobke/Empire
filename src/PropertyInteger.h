
/* <+FILE NAME+>
 * @Author:      <+AUTHOR+> (<+EMAIL+>)
 * @License:     <+LICENSE+>
 * @Created:     <+DATE+>.
 * @Editor:      Vim
 */

#ifndef PROPERTYINTEGER_H
#define PROPERTYINTEGER_H

#include "Property.cc"

#include <string>
using namespace std;

class PropertyInteger : public Property<int>
{
public:
    PropertyInteger(int value);
    // PropertyInteger(string const& key, int value);
    // PropertyInteger(string const& key, string const& description, int value);
    ~PropertyInteger();
};

#endif
