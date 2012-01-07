
/* GenProperty.cc<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-07.
 * @Editor:      Vim
 */

#include "GenProperty.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

void GenProperty::InitPointers()
{
    mpIntValue = NULL;
    mpFloatValue = NULL;
    mpStringValue = NULL;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

GenProperty::GenProperty(int value, std::string& rKey, std::string& rDesc)
:   mKey(rKey),
    mDesc(rDesc),
    mType(INT_T)
{
    this->InitPointers();
    
    mpIntValue = new int(value);
}
    
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

GenProperty::GenProperty(float value, std::string& rKey, std::string& rDesc)
:   mKey(rKey),
    mDesc(rDesc),
    mType(FLOAT_T)
{
    this->InitPointers();
    
    mpFloatValue = new float(value);
}
    
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

GenProperty::GenProperty(std::string value, std::string& rKey, std::string& rDesc)
:   mKey(rKey),
    mDesc(rDesc),
    mType(STRING_T)
{
    this->InitPointers();
    
    mpStringValue = new std::string(value);
}
    

/*============================= OPERATORS ==================================*/

/*============================= OPERATIONS =================================*/
/*============================= ACESS      =================================*/

void GenProperty::GetValue(int& value)
{
    value = *mpIntValue;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void GenProperty::GetValue(float& value)
{
    value = *mpFloatValue;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void GenProperty::GetValue(std::string& value)
{
    value = *mpStringValue;
}

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
