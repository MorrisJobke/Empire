
/* GenProperty.cpp
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-14.
 * @Editor:      Vim
 */

#include "GenProperty.h"


/** define important types
 */
DEFINE_NEW_GETTYPENAME(int)
DEFINE_NEW_GETTYPENAME(int*)
DEFINE_NEW_GETTYPENAME(int&)
DEFINE_NEW_GETTYPENAME(float)
DEFINE_NEW_GETTYPENAME(float*)
DEFINE_NEW_GETTYPENAME(float&)
DEFINE_NEW_GETTYPENAME(double)
DEFINE_NEW_GETTYPENAME(double&)
DEFINE_NEW_GETTYPENAME(double*)
DEFINE_NEW_GETTYPENAME(std::string)
DEFINE_NEW_GETTYPENAME(std::string&)
DEFINE_NEW_GETTYPENAME(std::string*)
DEFINE_NEW_GETTYPENAME(FunctionType)
DEFINE_NEW_GETTYPENAME(FunctionType&)
DEFINE_NEW_GETTYPENAME(FunctionType*)
DEFINE_NEW_GETTYPENAME(Coll)
DEFINE_NEW_GETTYPENAME(Coll&)
DEFINE_NEW_GETTYPENAME(Coll*)




std::ostream& operator<<(std::ostream& rOut, GenPropertyBase& rProp)
{
    //std::cout << "Streaming property:\n" << rProp.GetKey() << std::endl;
    rProp.ToOutStream(rOut);
    return rOut;
};



namespace PropertyIo
{
    /** write type to a file with the name of the key
     *
     * @param rPath the directory to write the file to
     * @param rKey the key
     * @param rType the type
     */
    void WriteMetaDataToDir(std::string const& rPath, std::string const& rKey, std::string const& rType)
    {
        /* create and write metadata file */

        std::string path = rPath + "/" + rKey;
        std::ofstream meta_file;
        meta_file.open(path.c_str());

        if (meta_file.is_open())
        {
            meta_file << rType;
        }

        meta_file.close();
        /* TODO exception on file error */
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** wrapper function for the upper one
     *
     * @param rPath the directory to write the file to
     * @param pProp property to read type and key from
     */
    void WriteMetaDataToDir(std::string const& rPath, GenPropertyBase* pProp)
    {
        WriteMetaDataToDir(rPath, pProp->GetKey(), pProp->GetTypeN());
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** write the property data to file. Filename is determined by the key
     *
     * @param rPath the dir path
     * @param pProp property to read key and data from
     */
    void WriteDataToDir(std::string const& rPath, GenPropertyBase* pProp)
    {
        std::string file_path(rPath + "/" + pProp->GetKey());

        std::ofstream file(file_path.c_str());

        if (file.is_open())
        {
            file << pProp->ToString();
        }

        file.close();

        /* TODO check if whole file is written */

    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** method to read a metadatafile
     *
     * @param rPath filepath
     * @param rKey reference the key to be filled
     * @param rType reference the type to be filled
     */
    void ReadMetaDataFromFile(std::string const& rPath, std::string& rKey, std::string& rType)
    {
        if(Filesystem::GetFileType(rPath) == DT_DIR)
            rType = GetTypeName<Coll>();
        else
        {
            std::ifstream meta_file(rPath.c_str());

            if (meta_file.is_open())
            {
                if (meta_file.good())
                {
                    std::getline(meta_file, rType);
                }
            }
            meta_file.close();
        }

        /* extract key */
        std::string key = rPath;
        std::string search_for = "/";

        std::size_t found;
        found = key.rfind(search_for);

        if ( found != std::string::npos)
            key.replace(0, found + 1,"");

        rKey = key;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** read property data from Filesystem
     *
     * @param rPath complete file path
     * @param pProp pointer to the property the data is written to
     */
    void ReadDataFromFile(std::string const& rPath, GenPropertyBase* pProp)
    {
        std::ifstream file(rPath.c_str());

        std::string buffer;

        if (file.is_open())
        {
            if (file.good())
            {
                std::getline(file, buffer);
            }
        }
        file.close();

        //std::cout << "Try to set from string: " << buffer << std::endl;

        pProp->SetValueFromString(buffer);
    }

}

namespace PropertyHelpers
{
    /** create a property from type-string
    * @param rType string containing a type
    * @return returns created property
    */
    GenPropertyBase* CreatePropertyFromTypeString(std::string const& rType)
    {
        GenPropertyBase* p_new = NULL;

        if (rType == GetTypeName<int>())
            p_new = new GenProperty<int>();

        else if (rType == GetTypeName<double>())
            p_new = new GenProperty<double>();

        else if (rType == GetTypeName<float>())
            p_new = new GenProperty<float>();

        else if (rType == GetTypeName<std::string>() || rType == "string")
            p_new = new GenProperty<std::string>();

        else if (rType == GetTypeName<FunctionType>())
            p_new = new GenProperty<FunctionType>();

        else if (rType == GetTypeName<Coll>())
            p_new = new GenProperty<Coll>();

        else
            throw ErrorGenProperty("Not a supported type");

        return p_new;
    }

    /** create a property from type-string
    * @param pProp property where value should be set
    * @param rValue the value, that should be set
    */
    void SetValueFromString(GenPropertyBase* pProp, std::string const& rValue)
    {
        if (pProp->GetTypeN() == GetTypeName<int>())
        {
            GenProperty<int>* p_new = (GenProperty<int>*) pProp;

            int buffer;
            std::stringstream str(rValue);
            str >> buffer;
            p_new->SetValue(buffer);
        }
        else if (pProp->GetTypeN() == GetTypeName<double>())
        {
            GenProperty<double>* p_new = (GenProperty<double>*) pProp;

            double buffer;
            std::stringstream str(rValue);
            str >> buffer;
            p_new->SetValue(buffer);

        }
        else if (pProp->GetTypeN() == GetTypeName<float>())
        {
            GenProperty<float>* p_new = (GenProperty<float>*) pProp;

            double buffer;
            std::stringstream str(rValue);
            str >> buffer;
            float f = (float) buffer;
            p_new->SetValue(f);

        }
        else if (pProp->GetTypeN() == GetTypeName<std::string>() || pProp->GetTypeN() == "string")
        {
            GenProperty<std::string>* p_new = (GenProperty<std::string>*) pProp;
            p_new->SetValue(rValue);

        }
        else if (pProp->GetTypeN() == GetTypeName<FunctionType>())
        {
            GenProperty<FunctionType>* p_new = (GenProperty<FunctionType>*) pProp;

            std::list<std::string> list;
            std::string value = rValue;
            std::size_t found;

            found = value.find(";");
            while (found != std::string::npos)
            {
                list.push_back(value.substr(0,found+1));
                value.replace(0, found+1, "");
                found = value.find(";");
            }
            p_new->SetValue(list);

        }
        else if (pProp->GetTypeN() == GetTypeName<Coll>())
        {
            // GenProperty<Coll>* p_new = (GenProperty<Coll>*) pProp;
            // TODO ?
        }
        else
            throw ErrorGenProperty("Not a supported type");
    }
}

