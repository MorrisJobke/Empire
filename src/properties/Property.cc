
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
    mValue = value; 
}

// template<class T> void
// Property<T>::Init(string const& key, T value)
// {
//     mKey = key;
//     mValue = value;
// }

// template<class T> void
// Property<T>::Init(string const& key, string const& description, T value)
// {
//     mKey = key;
//     mDescription = description;
//     mValue = value;
// }

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

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
