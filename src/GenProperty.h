
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
        {
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        /* empty constructor with key
         */
        GenProperty(std::string const& rKey)
        {
            this->mKey = rKey;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        /* constructor with value and key
         */
        GenProperty(typ value, std::string const& rKey)
        {
            this->mKey = rKey;

            this->SetValue(value);
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        /* copy constructor
         */
        GenProperty(GenProperty<typ>& rOrigin)
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
        
        /*============================= ACESS      =================================*/

        void SetValue(typ value)
        {
            if (!(this->mpData))
                this->mpData = (void*) new typ(value); 
            else
                *((typ*)(this->mpData)) = value;
        };

        void SetValueFromString(std::string const& rValue)
        {
            typ buffer;

            std::stringstream str(rValue);

            str >> buffer;

            this->SetValue(buffer);
        }
    
        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        typ GetValue()
        {
            if (this->HasValue())
                return *((typ*)this->mpData);
            else
                throw ErrorGenProperty("NO_PROP_VALUE");
        };

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        std::string GetTypeN()
        {
            //std::cout << "printing type";
            return GetTypeName<typ>();
        };

        void Print()
        {
            std::cout << this->GetValue();
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/


        /*============================= OPERATIONS =================================*/

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

        std::string ToString()
        {
            std::stringstream out;

            out << this->GetValue();

            return out.str();
        }

        
        /*============================= INQUIRY    =================================*/
        
        /*============================= OPERATORS ==================================*/

        /** equal operator 
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
    void WriteMetaDataToDir(std::string const& rPath, GenPropertyBase* rProp);

    void WritePropDataToDir(std::string const& rPath, GenPropertyBase* pProp);

    void ReadMetaDataFromFile(std::string const& rPath, std::string& rKey, std::string& rType);

    void ReadDataFromFile(std::string const& rPath, GenPropertyBase* pProp);
}

#endif
