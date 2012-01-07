
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

    PropertyTypes mType;

    int*            mpIntValue;
    double*          mpFloatValue;
    std::string*    mpStringValue;

    public:
    void InitPointers();

    GenProperty(int value,        std::string& rKey);
    GenProperty(double value,      std::string& rKey);
    GenProperty(std::string value, std::string& rKey);

    void GetValue(int& value);
    void GetValue(double& value);
    void GetValue(std::string& value);

    std::string GetType();

    void WriteMetadata(std::string const& rPath);
    void WriteData(std::string const& rPath);

    void ReadMetadata(std::string const& rPath);
    void ReadData(std::string const& rPath);
};



#endif
