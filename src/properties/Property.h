
/* Property.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-16.
 * @Editor:      Vim
 */

#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
using namespace std;

class BaseProperty {};

template<class T> class Property
: public BaseProperty
{
protected:
    string mKey;
    string mDescription;
    T mValue;
    string mType;

    void Init(string const& key);
    void Init(string const& key, T value);
    void Init(string const& key, string const& description, T value);

public:
    Property();
    ~Property();

    T GetValue() const;
    void SetValue(T value);

    string GetKey() const;
    void SetKey(string value);
    string GetDescription() const;
    void SetDescription(string value);

    string GetType() const;
    void SetType(string value);
    void SaveMeta();
};

#endif
