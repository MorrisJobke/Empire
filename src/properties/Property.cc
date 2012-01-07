
/* Property.cc
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-16.
 * @Editor:      Vim
 */
#ifndef PROPERTY_CC
#define PROPERTY_CC

#include "Property.h"
#include "../Filesystem.h"
#include <iostream>

/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/** Constructor
 *
 */
template<class T>
Property<T>::Property()
{
}

/** Destructor
 *
 */
template<class T>
Property<T>::~Property()
{
}

/** Init
 *
 */
template<class T> void
Property<T>::Init(string const& key)
{
    mDescription = "";
    mKey = key;
    mValue = NULL;
}

template<class T> void
Property<T>::Init(string const& key, T value)
{
    mDescription = "";
    mKey = key;
    mValue = value;
}

template<class T> void
Property<T>::Init(string const& key, string const& description, T value)
{
    mDescription = description;
    mKey = key;
    mValue = value;
}

/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/

template<class T> void 
Property<T>::SaveValue(string& rPath)
{
    std::ostringstream ss;
    ss << mValue;
    std::string value (ss.str());
    Filesystem::FileWriteString(rPath, value);
}

template<class T> void
Property<T>::SaveMeta()
{
    string path;
    //path = GetMainPath();
    path = path + "meta.txt";
    string value = mKey + " " + GetType() + "\n";
    Filesystem::FileAppendString(path, value);
}

/*============================= ACESS      =================================*/

template<class T> T
Property<T>::GetValue() const
{
    return mValue;
}

template<class T> void
Property<T>::SetValue(T value)
{
    mValue = value;
}

template<class T> string
Property<T>::GetKey() const
{
    return mKey;
}

template<class T> void
Property<T>::SetKey(string value)
{
    mKey = value;
}

template<class T> string
Property<T>::GetDescription() const
{
    return mDescription;
}

template<class T> void
Property<T>::SetDescription(string value)
{
    mDescription = value;
}

template<class T> string
Property<T>::GetType() const
{
    return mType;
}

template<class T> void
Property<T>::SetType(string value)
{
    mType = value;
}

template<class T> string
Property<T>::ToString() const
{
    ostringstream oss;
    oss << mValue;
    return oss.str();
}

/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////

#endif
