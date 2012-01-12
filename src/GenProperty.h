
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

#include "DefineException.h"

DEFINE_FAST_EXCEPTION(UnsetTypeError,"Property has unset type")
DEFINE_FAST_EXCEPTION(CannotOpenFileError,"Cannot open file")

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
    GenProperty(int value,              std::string const& rKey);
    GenProperty(double value,           std::string const& rKey);
    GenProperty(std::string value,      std::string const& rKey);
    GenProperty(FunctionProperty value, std::string const& rKey);
    GenProperty(PropertyTypes type, std::string const& rKey);
    //GenProperty(GenProperty const& original);



    void GetValue(int& value);
    void GetValue(double& value);
    void GetValue(std::string& value);
    void GetValue(double& value, std::list< std::list<GenProperty> > properties);

    std::string GetType() const;
    std::string GetKey() const;

    bool HasValue();

    void WriteMetadata(std::string const& rPath);
    void WriteData(std::string const& rPath);

    void ReadMetadata(std::string const& rPath);
    void ReadData(std::string const& rPath);
    bool ReadDataIfEmpty(std::string const& rPath);

    void PrintToStream(std::ostream& rOut) const;

    bool            operator==(GenProperty& rRight);
    GenProperty&    operator=(GenProperty const& rRight);


    //virtual ~GenProperty()
    //{
    //    if (mpIntValue)
    //        delete mpIntValue;
    //    if (mpFloatValue)
    //        delete mpFloatValue;
    //    if (mpStringValue)
    //        delete mpStringValue;
    //    if (mpFunctionValue)
    //        delete mpFunctionValue;
    //}
    //
    
    static PropertyTypes StringToEnumType(std::string const& type);
};

std::ostream&        operator<<(std::ostream& rOut, const GenProperty& rProp);


#endif
