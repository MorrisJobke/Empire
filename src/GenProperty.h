
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

enum PropertyTypes {INT_T, FLOAT_T, STRING_T, UNDEFINED_T};

/** Class which implemets a generic property
 */
class GenProperty
{
    std::string mKey;

    PropertyTypes mType;

    int*            mpIntValue;
    float*          mpFloatValue;
    std::string*    mpStringValue;

    public:
    void InitPointers();

    GenProperty();
    GenProperty(int value,        std::string& rKey);
    GenProperty(float value,      std::string& rKey);
    GenProperty(std::string value, std::string& rKey);

    std::string GetKey();
    void GetValue(int& value);
    void GetValue(float& value);
    void GetValue(std::string& value);

    PropertyTypes GetType();

    void WriteMetadata(std::string const& rPath);
    void WriteData(std::string const& rPath);

    void ReadMetadata(std::string const& rPath);
    void ReadData(std::string const& rPath);
};



#endif
