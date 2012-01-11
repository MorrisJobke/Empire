
/* GenProperty.cc<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-07.
 * @Editor:      Vim
 */

#include "GenProperty.h"
#include "Filesystem.h"
#include "LuaHelper.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/** method, which initializes the pointers to null
 */
void GenProperty::InitPointers()
{
    mpIntValue = NULL;
    mpFloatValue = NULL;
    mpStringValue = NULL;
    mpFunctionValue = NULL;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** untyped constructor of the GenProperty-class
 */
GenProperty::GenProperty()
:   mKey(),
    mType(UNDEFINED_T)
{
    this->InitPointers();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** constructor for meta properties
 *
 * @param the type
 * @param the key
 */
GenProperty::GenProperty(PropertyTypes type, std::string const& rKey)
:   mKey(rKey),
    mType(type)
{
    this->InitPointers();
}
    
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** constructor for integer-values of the GenProperty-class
 *
 * @param value integer-value for the new instance of the GenProperty-class
 * @param rKey key for the new instance of the GenProperty-class
 */
GenProperty::GenProperty(int value, std::string const& rKey)
:   mKey(rKey),
    mType(INT_T)
{
    this->InitPointers();
    
    mpIntValue = new int(value);
}
    
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** constructor for float-values of the GenProperty-class
 *
 * @param value float-value for the new instance of the GenProperty-class
 * @param rKey key for the new instance of the GenProperty-class
 */
GenProperty::GenProperty(double value, std::string const& rKey)
:   mKey(rKey),
    mType(FLOAT_T)
{
    this->InitPointers();
    
    mpFloatValue = new double(value);
}
    
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** constructor for string-values of the GenProperty-class
 *
 * @param value string-value for the new instance of the GenProperty-class
 * @param rKey key for the new instance of the GenProperty-class
 */
GenProperty::GenProperty(std::string value, std::string const& rKey)
:   mKey(rKey),
    mType(STRING_T)
{
    this->InitPointers();
    
    mpStringValue = new std::string(value);
}
    
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** constructor for functions of the GenProperty-class
 *
 * @param value function for the new instance of the GenProperty-class
 * @param rKey key for the new instance of the GenProperty-class
 */
GenProperty::GenProperty(FunctionProperty value, std::string const& rKey)
:   mKey(rKey),
    mType(FUNCTION_T)
{
    this->InitPointers();
    
    mpFunctionValue = new FunctionProperty(value);
}
    

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** copy constructor
 */
//GenProperty::GenProperty(GenProperty const& original)
//{
//    *this = original;
//}

/*============================= OPERATORS ==================================*/

/** method, which defines the ==-comparison operator for the GenProperty-class
 *
 * @param rRight second operator, which should compare the committed GenProperty to the own GenProperty
 * @return returns true, when the committed GenProperty is the same as the own, otherwise false
 */
bool GenProperty::operator==(GenProperty& rRight)
{
    if (this->mType != rRight.mType)
        return false;

    if (this->mKey != rRight.mKey)
        return false;

    if (this->mpIntValue)
        if (*(this->mpIntValue) != *(rRight.mpIntValue))
            return false;

    if (this->mpFloatValue)
        if (*(this->mpFloatValue) != *(rRight.mpFloatValue))
            return false;

    if (this->mpStringValue)
        if (*(this->mpStringValue) != *(rRight.mpStringValue))
            return false;

    return true;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** assignment opearator
 */
GenProperty& GenProperty::operator=(GenProperty const& rRight)
{
    if (this != &rRight)
    {
        if (this->mpIntValue)
            delete mpIntValue;
        if (this->mpFloatValue)
            delete mpFloatValue;
        if (this->mpStringValue)
            delete mpStringValue;

        this->InitPointers();

        if (rRight.mpIntValue)
            this->mpIntValue = new int(*(rRight.mpIntValue));
        if (rRight.mpFloatValue)
            this->mpFloatValue = new double(*(rRight.mpFloatValue));
        if (rRight.mpStringValue)
            this->mpStringValue = new std::string(*(rRight.mpStringValue));

        this->mKey = rRight.mKey;
        this->mType = rRight.mType;
    }

    return *this;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** define the << OPERATORS
 *
 * @relates GenProperty
 * @param output stream
 * @param rProp reference to property
 */
std::ostream& operator<<(std::ostream& rOut, GenProperty const& rProp)
{
   rProp.PrintToStream(rOut); 
   return rOut;
}

/*============================= OPERATIONS =================================*/

/** helper function for debugging 
 */
void GenProperty::PrintToStream(std::ostream& rOut) const
{
    rOut << "[PROP<" << this->GetType() << ">" << this->GetKey() << ":";

    if (mpIntValue)
        rOut << *mpIntValue;
    if (mpFloatValue)
        rOut << *mpFloatValue;
    if (mpStringValue)
        rOut << *mpStringValue;

    rOut << "]";
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** method, which writes the metadata of the GenProperty into a file
 *
 * @param rPath path, where the metafile should stored
 */
void GenProperty::WriteMetadata(std::string const& rPath)
{
    std::string value = GetType() + "\n";
    Filesystem::FileWriteString(rPath + "/" + mKey, value);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** method, which writes the data of the GenProperty into a file
 *
 * @param rPath path, where the file should stored
 */
void GenProperty::WriteData(std::string const& rPath)
{
    std::string temp;
    std::stringstream out;
    switch(mType)
    {
        case INT_T:
            {
                int value_int;
                GetValue(value_int);          
                out << value_int;
                temp = out.str();
                Filesystem::FileWriteString(rPath + "/" + mKey, temp);
            }
            break;
        case FLOAT_T:
            {
                double value_double;
                GetValue(value_double);
                out << value_double;
                temp = out.str();
                Filesystem::FileWriteString(rPath + "/" + mKey, temp);
            }
            break;
        case STRING_T:
            {
                std::string value_string;
                GetValue(value_string);
                Filesystem::FileWriteString(rPath + "/" + mKey, value_string);
            }
            break;
        case FUNCTION_T:
            break;
        case UNDEFINED_T:
            break;
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** method, which reads the property metadata from the given file
 *
 * @param rPath path of the file
 */
void GenProperty::ReadMetadata(std::string const& rPath)
{
    std::string line;
    std::ifstream myfile(rPath.c_str());

    /* extract key */
    std::string key = rPath;
    std::string search_for = "/";

    std::size_t found;
    found = key.rfind(search_for);

    if ( found != std::string::npos)
        key.replace(0, found + 1,"");
    
    //std::cout << found << " Stripped key: --" << key << "--" << std::endl;


    if (myfile.is_open())
    {
        if (myfile.good())
        {
            getline (myfile,line);
            //std::cout << "read metatdata type: " << line << std::endl;
        }
        myfile.close();
    }
    //TODO: else
    
    if (line == "Integer")
    {
        this->mType = INT_T;
    }
    if (line == "Float")
    {
        this->mType = FLOAT_T;
    }
    if (line == "String")
    {
        this->mType = STRING_T;
    }

    this->mKey = key;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** method, which reads the property data from the given file
 *
 * @param rPath path of the file
 */
void GenProperty::ReadData(std::string const& rPath)
{
    /*TODO: throw exceptions if type not set*/

    std::ifstream f(rPath.c_str());

    if (f.is_open())
    {
        if (f.good())
        {
            switch(mType)
            {
                case INT_T:
                    {
                        int value_int;
                        f >> value_int;
                        mpIntValue = new int(value_int);
                    }
                    break;
                case FLOAT_T:
                    {
                        double value_double;
                        f >> value_double;
                        mpFloatValue = new double(value_double);
                    }
                    break;
                case STRING_T:
                    {
                        std::string value_string;
                        std::getline(f, value_string);
                        mpStringValue = new std::string(value_string);
                    }
                    break;
                case FUNCTION_T:
                    break;
                case UNDEFINED_T:
                    break;
            }
        }
        f.close();
    }
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** same method as above, but only reads data if the propertiy have not
 *
 * @param file path
 * 
 * @return false if no data was written to the property instance
 */
bool GenProperty::ReadDataIfEmpty(const std::string &rPath)
{
    /*TODO: throw exceptions if type not set*/

    std::ifstream f(rPath.c_str());

    if (f.is_open())
    {
        if (f.good())
        {
            switch(mType)
            {
                case INT_T:
                    {
                        if (this->mpIntValue)
                            return false;
                        int value_int;
                        f >> value_int;
                        mpIntValue = new int(value_int);
                    }
                    break;
                case FLOAT_T:
                    {
                        if (this->mpFloatValue)
                            return false;
                        double value_double;
                        f >> value_double;
                        mpFloatValue = new double(value_double);
                    }
                    break;
                case STRING_T:
                    {
                        if (this->mpStringValue)
                            return false;
                        std::string value_string;
                        std::getline(f, value_string);
                        mpStringValue = new std::string(value_string);
                    }
                    break;
                case FUNCTION_T:
                    break;
                case UNDEFINED_T:
                    break;
            }
        }
        f.close();
    }
    return true;
}

/*============================= ACESS      =================================*/

/** getter for the key of the instance of the GenProperty
 *
 * @return returns the key
 */
std::string GenProperty::GetKey() const
{
    return mKey;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** getter for the value of the instance of the GenProperty, if it's an integer-property
 *
 * @param value for storing the return-value
 */
void GenProperty::GetValue(int& value)
{
    value = *mpIntValue;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** getter for the value of the instance of the GenProperty, if it's a float-property
 *
 * @param value for storing the return-value
 */
void GenProperty::GetValue(double& value)
{
    value = *mpFloatValue;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** getter for the value of the instance of the GenProperty, if it's a string-property
 *
 * @param value for storing the return-value
 */
void GenProperty::GetValue(std::string& value)
{
    std::ostringstream oss;
    switch (mType) {
        case INT_T:
            oss << *mpIntValue;
            break;
        case FLOAT_T:
            oss << *mpFloatValue;
        case STRING_T:
            oss << *mpStringValue;
        case FUNCTION_T:
            break;
        case UNDEFINED_T:
            break;
    }
    value = oss.str();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** getter for the value of the instance of the GenProperty, if it's a function-property
 *
 * @param value for storing the return-value of the exexuted function
 * @param properties list of a list of the properties on which the function is executed
 */
void GenProperty::GetValue(double& value, std::list< std::list<GenProperty> > properties)
{
    LuaHelper* helper = new LuaHelper();
    std::list<double> results;

    std::list< std::list<GenProperty> >::iterator list;
    for(list = properties.begin(); list != properties.end(); ++list) {
        LuaContext* context = helper->CreateContext();
        std::list<GenProperty>::iterator property;

        for (property = (*list).begin(); property != (*list).end(); ++property) {
            std::ostringstream oss;

            if (property->GetType() == "Integer") {
                int int_value;
                property->GetValue(int_value);
                context->AddVariable(property->GetKey(), int_value);
            } else if (property->GetType() == "Float") {
                double double_value;
                property->GetValue(double_value);
                context->AddVariable(property->GetKey(), double_value);
            }
        }
        
        double result;
        context->Execute(mpFunctionValue->map, result);
        results.push_back(result);
    }

    std::list<double>::iterator result;
    std::string lhs = "lhs";
    std::string rhs = "rhs";
    value = 0;
    for(result = results.begin(); result != results.end(); ++result) {
        LuaContext* context = helper->CreateContext();
        context->AddVariable(lhs, value);
        context->AddVariable(rhs, *result);
        context->Execute(mpFunctionValue->reduce, value);
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** getter for the type of the instance of the GenProperty
 *
 * @return returns a string with the type of the instance
 */
std::string GenProperty::GetType() const
{
    switch(mType)
    {
        case INT_T: return "Integer"; break;
        case FLOAT_T: return "Float"; break;
        case STRING_T: return "String"; break;
        case FUNCTION_T: break;
        case UNDEFINED_T: break;
        default: return "";
    }
}

/*============================= INQUIRY    =================================*/

/** check if our instance has a values
 */
bool GenProperty::HasValue()
{
    if (mpIntValue)
        return true;
    if (mpFloatValue)
        return true;
    if (mpStringValue)
        return true;
    if (mpFunctionValue)
        return true;

    return false;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////

/////////////////////////////// STATICS    ///////////////////////////////////

/** "convert" a string to the enum type
 */
PropertyTypes GenProperty::StringToEnumType(std::string const& type)
{
    if (type == "Integer")
        return INT_T;
    if (type == "Float")
        return FLOAT_T;
    if (type == "String")
        return STRING_T;
    if (type == "Function")
        return FUNCTION_T;

    return UNDEFINED_T;
}
