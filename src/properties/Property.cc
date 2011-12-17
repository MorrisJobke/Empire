
/* Property.cc
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-16.
 * @Editor:      Vim
 */

#include "Property.h"

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
Property<T>::Init(T value)
{
    mDescription = "";
    mKey = "";
    mValue = value;
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

/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////