
/* GenProperty.cc<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-07.
 * @Editor:      Vim
 */

#include "GenProperty.h"
#include "Filesystem.h"
#include <sstream>


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

void GenProperty::InitPointers()
{
    mpIntValue = NULL;
    mpFloatValue = NULL;
    mpStringValue = NULL;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

GenProperty::GenProperty(int value, std::string& rKey)
:   mKey(rKey),
    mType(INT_T)
{
    this->InitPointers();
    
    mpIntValue = new int(value);
}
    
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

GenProperty::GenProperty(double value, std::string& rKey)
:   mKey(rKey),
    mType(FLOAT_T)
{
    this->InitPointers();
    
    mpFloatValue = new double(value);
}
    
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

GenProperty::GenProperty(std::string value, std::string& rKey)
:   mKey(rKey),
    mType(STRING_T)
{
    this->InitPointers();
    
    mpStringValue = new std::string(value);
}
    

/*============================= OPERATORS ==================================*/

/*============================= OPERATIONS =================================*/

void GenProperty::WriteMetadata(std::string const& rPath)
{
    std::string value = mKey + " " + GetType() + "\n";
    Filesystem::FileAppendString(rPath + "/" + mKey, value);
}

void GenProperty::WriteData(std::string const& rPath)
{
    std::string temp;
    std::stringstream out;
    switch(mType)
    {
        case INT_T:
            int value_int;
            GetValue(value_int);          
            out << value_int;
            temp = out.str();
            Filesystem::FileWriteString(rPath + "/" + mKey, temp);
            break;
        case FLOAT_T:
            double value_double;
            GetValue(value_double);
            out << value_double;
            temp = out.str();
            Filesystem::FileWriteString(rPath + "/" + mKey, temp);
            break;
        case STRING_T:
            std::string value_string;
            GetValue(value_string);
            out << value_string;
            temp = out.str();
            Filesystem::FileWriteString(rPath + "/" + mKey, temp);
        //case FUNCTION_T:
            //break;
    }
}

/*============================= ACESS      =================================*/

void GenProperty::GetValue(int& value)
{
    value = *mpIntValue;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void GenProperty::GetValue(double& value)
{
    value = *mpFloatValue;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void GenProperty::GetValue(std::string& value)
{
    value = *mpStringValue;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

std::string GenProperty::GetType()
{
    switch(mType)
    {
        case INT_T: return "Integer"; break;
        case FLOAT_T: return "Float"; break;
        case STRING_T: return "String"; break;
        //case FUNCTION_T: return "Function"; break;
        // fix warning
        default: return "";
    }
}

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
