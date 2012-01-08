
/* GenProperty.cc<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-07.
 * @Editor:      Vim
 */

#include "GenProperty.h"
#include "Filesystem.h"


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
    
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

GenProperty::GenProperty(FunctionProperty value, std::string& rKey)
:   mKey(rKey),
    mType(FUNCTION_T)
{
    this->InitPointers();
    
    mpFunctionValue = new FunctionProperty(value);
}
    

/*============================= OPERATORS ==================================*/

/*============================= OPERATIONS =================================*/

void GenProperty::WriteMetadata(std::string const& rPath)
{
    std::string value = GetType() + "\n";
    Filesystem::FileWriteString(rPath + "/" + mKey, value);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

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

std::string GenProperty::GetKey() const
{
    return mKey;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

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

void GenProperty::GetValue(double& value, std::list< std::list<GenProperty> > properties)
{
    lua_State *L = lua_open();
    std::list<double> results;

    std::list< std::list<GenProperty> >::iterator it;
    for(it = properties.begin(); it != properties.end(); ++it) {
        std::list<GenProperty> layer = *it;
        std::string variables = "";
        
        std::list<GenProperty>::iterator it2;
        for (it2 = layer.begin(); it2 != layer.end(); ++it2) {
            GenProperty property = *it2;
            std::ostringstream oss;

            if (property.GetType() == "Integer") {
                int int_value;
                property.GetValue(int_value);
                oss << property.GetKey() << "=" << int_value << ";";

                variables += oss.str();
            } else if (property.GetType() == "Float") {
                double double_value;
                property.GetValue(double_value);

                std::ostringstream oss;
                oss << property.GetKey() << "=" << double_value << ";";

                variables += oss.str();
            }
        }

        std::string lua = variables + "return " + (*mpFunctionValue).map + ";";
        luaL_dostring(L, lua.c_str());
        
        std::string result = lua_tostring(L, -1);

        std::istringstream i(result);
        double x;
        if ((i >> x))
            results.push_back(x);
    }

    std::list<double>::iterator it3;
    double lhs = 0;
    for(it3 = results.begin(); it3 != results.end(); ++it3) {
        std::ostringstream oss;
        oss << "lhs = " << lhs << "; rhs = " << *it3 << "; return " << (*mpFunctionValue).reduce << ";";
        std::string result = oss.str();
        luaL_dostring(L, result.c_str());

        std::istringstream i(lua_tostring(L, -1));
        double x;
        if ((i >> x))
            lhs = x;
    }

    lua_close(L);

    value = lhs;
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
