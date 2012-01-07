
/* GenProperty.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-07.
 * @Editor:      Vim
 */

#ifndef GENPROPERTY_H
#define GENPROPERTY_H

#include <string>
#include <iostream>

enum PropertyTypes {INT_T, FLOAT_T, STRING_T};

/** Class which implemets a generic property
 */
class GenProperty
{
    std::string mKey;
    std::string mDesc;

    PropertyTypes mType;

    int*            mpIntValue;
    float*          mpFloatValue;
    std::string*    mpStringValue;

    public:
    void InitPointers();

    GenProperty(int value,        std::string& rKey, std::string& rDesc);
    GenProperty(float value,      std::string& rKey, std::string& rDesc);
    GenProperty(std::string value, std::string& rKey, std::string& rDesc);

    void GetValue(int& value);
    void GetValue(float& value);
    void GetValue(std::string& value);

    PropertyTypes GetType();
};



#endif
