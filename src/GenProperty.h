
/* GenProperty.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-12.
 * @Editor:      Vim
 */

#ifndef GENPROPERTYNEW_H
#define GENPROPERTYNEW_H

#include <iostream>
#include <typeinfo>
#include <sstream>
#include <fstream>

#include "GenPropertyBase.h"
#include "DefineException.h"
#include "FunctionType.h"
#include "Collection.h"

/** typename templates
 */
template <typename typ>
std::string GetTypeName() { return "undefined"; };


/** typename macro
 */
#define DEFINE_NEW_GETTYPENAME(type) \
template <> \
std::string GetTypeName<type>() {return "" #type ""; }; \

/** exceptions
 */
DEFINE_VAR_EXCEPTION(ErrorGenProperty)

/** some helpers for Property related things
 */
namespace PropertyHelpers
{
    GenPropertyBase* CreatePropertyFromTypeString(std::string const& rType);
    void SetValueFromString(GenPropertyBase* prop, std::string const& rType);
    std::string GetPropertyValueAsString(GenPropertyBase* prop);
}

/* define a template for basic types
 */
template <typename typ>
class GenProperty : public GenPropertyBase
{
    public:

        /////////////////////////////// PUBLIC ///////////////////////////////////////

        /*============================= LIFECYCLE ==================================*/

        /* default constructor
         */
        GenProperty()
        :   GenPropertyBase()
        {
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        /** empty constructor with key
         *
         * @param rKey the key for the new property
         */
        GenProperty(std::string const& rKey)
        :   GenPropertyBase()
        {
            this->mKey = rKey;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        /** constructor with value and key
         *
         * @param value the value for the new property
         * @param rKey the key for the new property
         */
        GenProperty(typ value, std::string const& rKey)
        :   GenPropertyBase()
        {
            this->mKey = rKey;

            this->SetValue(value);
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        /** copy constructor
         *
         * @param rOrigin the property, which should be copied
         */
        GenProperty(GenProperty<typ>& rOrigin)
        :   GenPropertyBase()
        {
            this->mKey = rOrigin.GetKey();

            this->SetValue(rOrigin.GetValue());
        }

        /** destructor
         */
        ~GenProperty()
        {
            if (this->mpData)
                delete (typ*) this->mpData;
        };

        /*============================= ACCESS      ================================*/

        /** setter for the value of a property
         *
         * @param value the new value for the property
         */
        void SetValue(typ value)
        {
            if (!(this->mpData))
                this->mpData = (void*) new typ(value);
            else
                *((typ*)(this->mpData)) = value;
        };

        /** setter for the value of a property, if it's a string
         *
         * @param rValue the new value as string for the property
         */
        void SetValueFromString(std::string const& rValue)
        {
            PropertyHelpers::SetValueFromString(this, rValue);
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        /** getter for the value of the property
         *
         * @return returns the value of the property
         * @throws ErrorGenProperty("NO_PROP_VALUE ("+this->GetKey()+")")
         */
        typ GetValue()
        {
            if (this->HasValue())
                return *((typ*)this->mpData);
            else
                throw ErrorGenProperty("NO_PROP_VALUE ("+this->GetKey()+")");
        };

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        /** getter for the type of the property
         *
         * @return returns a string which contains the typename
         */
        std::string GetTypeN()
        {
            //std::cout << "printing type";
            return GetTypeName<typ>();
        };

        /** print function for the value of the property
         *
         */
        void Print()
        {
            std::cout << this->GetValue();
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/


        /*============================= OPERATIONS =================================*/

        /** method to print the type, key and value of the property to the outstream
         *
         * @param rOut the outstream where the data is printed
         */
        void ToOutStream(std::ostream& rOut)
        {
            if (this->HasValue())
            {
                rOut << "[PROP<" << this->GetTypeN() << ">"
                    << this->mKey << ":" << this->GetValue()<< "]";
            }
            else
            {
                rOut << "[PROP<" << this->GetTypeN() << ">"
                    << this->mKey << ":" << "NOVALUE" << "]";
            }
        }

        /** method to return the value of the property as string
         *
         * @return returns a string with the value of the property
         */
        std::string ToString()
        {
            std::stringstream out;

            out << this->GetValue();

            return out.str();
        }


        /*============================= INQUIRY    =================================*/

        /*============================= OPERATORS ==================================*/

        /** equal operator
         *
         * @param rRight property which should be compared with the current property
         * @return returns true, if rRight is the same property, else false
         */
        bool operator==(GenProperty<typ>& rRight)
        {
            if (this->GetValue() != rRight.GetValue())
                return false;

            if (this->GetTypeN() != rRight.GetTypeN())
                return false;

            if (this->GetKey() != rRight.GetKey())
                return false;

            return true;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        /** assignment operator
         *
         * @param rRight property which should be assigned to the current property
         * @return returns the current property
         */
        GenProperty<typ>& operator=(GenProperty<typ>& rRight)
        {
            if (this != &rRight)
            {
                if (this->HasValue())
                {
                    delete (typ*) this->mpData;
                    this->mpData = NULL;
                }

                this->SetValue(rRight.GetValue());

                this->mKey = rRight.GetKey();
            }

            return *this;
        }

};

/*============================= OPERATORS ==================================*/

std::ostream& operator<<(std::ostream& rOut, GenPropertyBase& rProp);


/** Property io functions
 */
namespace PropertyIo
{
    void WriteMetaDataToDir(std::string const& rPath, std::string const& key, std::string const& rType);
    void WriteMetaDataToDir(std::string const& rPath, GenPropertyBase* pProp);

    void WriteDataToDir(std::string const& rPath, GenPropertyBase* pProp);

    void ReadMetaDataFromFile(std::string const& rPath, std::string& rKey, std::string& rType);
    void ReadDataFromFile(std::string const& rPath, GenPropertyBase* pProp);
}
#endif
