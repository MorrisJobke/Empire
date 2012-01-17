
/* GenProperty.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-12.
 * @Editor:      Vim
 */

#include <iostream>
#include <string>

#ifndef GENPROPERTYBASE_H
#define GENPROPERTYBASE_H


/** declare the abstract base class
 */
class GenPropertyBase
{
    protected:
        std::string mKey;

        void* mpData;

    public:

        GenPropertyBase()
        :   mKey("NoKey"),
            mpData(NULL)
        {
        }

        bool HasValue() const
        {
            if (this->mpData)
                return true;
            else
                return false;
        }

        std::string GetKey()
        {
            return this->mKey;
        }

        virtual ~GenPropertyBase() {};

        void SetKey(std::string const& rKey) {this->mKey = rKey; };

        virtual void Print() = 0;
        virtual void ToOutStream(std::ostream& rOut) = 0;
        virtual std::string GetTypeN() = 0;

        virtual std::string ToString() = 0;
        virtual void SetValueFromString(std::string const& rValue) = 0;
};

#endif
