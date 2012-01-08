
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
GenProperty::GenProperty()
:   mKey(""),
    mType(UNDEFINED_T)
{
    this->InitPointers();
}

GenProperty::GenProperty(int value, std::string& rKey)
:   mKey(rKey),
    mType(INT_T)
{
    this->InitPointers();
    
    mpIntValue = new int(value);
}
    
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

GenProperty::GenProperty(float value, std::string& rKey)
:   mKey(rKey),
    mType(FLOAT_T)
{
    this->InitPointers();
    
    mpFloatValue = new float(value);
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
<<<<<<< Updated upstream
=======

void GenProperty::WriteMetadata(std::string const& rPath)
{
    std::string value = mKey + " " + GetType() + "\n";
    Filesystem::FileAppendString(rPath, value);
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
            Filesystem::FileWriteString(rPath, temp);
            break;
        case FLOAT_T:
            double value_double;
            GetValue(value_double);
            out << value_double;
            temp = out.str();
            Filesystem::FileWriteString(rPath, temp);
            break;
        case STRING_T:
            std::string value_string;
            GetValue(value_string);
            out << value_string;
            temp = out.str();
            Filesystem::FileWriteString(rPath, temp);
        //case FUNCTION_T:
            //break;
    }
}

void GenProperty::ReadMetadata(std::string const& rPath)
{
    std::string line;
    std::ifstream myfile ((rPath + "/" + mKey).c_str());

    if (myfile.is_open())
    {
        if ( myfile.good() )
        {
            getline (myfile,line);
        }
        myfile.close();
    }
    //TODO: else
    
    if (!line.compare("Integer")){
        mpIntValue = new int(0);
    }
    else if (!line.compare("Float")) {
        mpFloatValue = new double(0.0);
    }    
    else if (!line.compare("String")) {
        mpStringValue = new std::string("");
    }

}

>>>>>>> Stashed changes
/*============================= ACESS      =================================*/

std::string GenProperty::GetKey()
{
    return mKey;
}

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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

PropertyTypes GenProperty::GetType()
{
    return mType;
}

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
