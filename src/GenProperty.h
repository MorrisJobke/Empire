
/* GenProperty.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-07.
 * @Editor:      Vim
 */

#ifndef GENPROPERTY_H
#define GENPROPERTY_H

#include <string>
#include <list>
#include <iostream>
#include <sstream>

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

enum PropertyTypes {INT_T, FLOAT_T, STRING_T, FUNCTION_T, UNDEFINED_T};

struct FunctionProperty {
    std::string map;
    std::string reduce;  
};

/** Class which implemets a generic property
 */
class GenProperty
{
    std::string mKey;

    PropertyTypes mType;

    int*                mpIntValue;
    double*             mpFloatValue;
    std::string*        mpStringValue;
    FunctionProperty*   mpFunctionValue;

    public:
    void InitPointers();

    GenProperty();
    GenProperty(int value,              std::string& rKey);
    GenProperty(double value,           std::string& rKey);
    GenProperty(std::string value,      std::string& rKey);
    GenProperty(FunctionProperty value, std::string& rKey);

    std::string GetKey();
    void GetValue(int& value);
    void GetValue(double& value);
    void GetValue(std::string& value);
    void GetValue(double& value, std::list< std::list<GenProperty> > properties);

    std::string GetType();

    void WriteMetadata(std::string const& rPath);
    void WriteData(std::string const& rPath);

    void ReadMetadata(std::string const& rPath);
    void ReadData(std::string const& rPath);
};



#endif
