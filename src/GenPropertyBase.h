
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
        /** the key of the property */
        std::string mKey;

        /** the value of the property*/
        void* mpData;

    public:

        GenPropertyBase()
        :   
            mKey("NoKey"),
            mpData(NULL)
        {
        }

        /** returns if the property has a value
         *
         * @return true if property has value, otherwise false
         */
        bool HasValue() const
        {
            if (this->mpData)
                return true;
            else
                return false;
        }

        /** returns the key of the property
         *
         * @return property key
         */
        std::string GetKey()
        {
            //std::cout << "requesting key: ";
            //if (this == NULL)
            //{
            //    bool debug = false;
            //    std::cout << "Object is NULL\n";
            //}
            //std::cout << this->mKey << std::endl;
            return this->mKey;
        }

        virtual ~GenPropertyBase() {};

        /** set the key of the property
         *
         * @param rKey the key that should be set
         */
        void SetKey(std::string const& rKey) {this->mKey = rKey; };

        /** print function for the value of the property
         *
         */
        virtual void Print() = 0;

        /** method to print the type, key and value of the property to the outstream
         *
         * @param rOut the outstream where the data is printed
         */
        virtual void ToOutStream(std::ostream& rOut) = 0;

        /** getter for the type of the property
         *
         * @return returns a string which contains the typename
         */
        virtual std::string GetTypeN() = 0;

        /** method to return the value of the property as string
         *
         * @return returns a string with the value of the property
         */
        virtual std::string ToString() = 0;

        /** setter for the value of a property, if it's a string
         *
         * @param rValue the new value as string for the property
         */
        virtual void SetValueFromString(std::string const& rValue) = 0;
};

#endif
