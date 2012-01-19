
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



std::ostream& operator<<(std::ostream& rOut, GenPropertyBase& rProp)
{
   rProp.ToOutStream(rOut);
   return rOut;
};



namespace PropertyIo
{
    /** write type to a file with the name of the key
     *
     * @param rPath the directory to write the file to
     * @param key the key
     * @param rType the type
     */
    void WriteMetaDataToDir(std::string const& rPath, std::string const& key, std::string const& rType)
    {
        /* create and write metadata file */

        std::string path = rPath + "/" + key;
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
     * @param property to read type and key from
     */
    void WriteMetaDataToDir(std::string const& rPath, GenPropertyBase* rProp)
    {
        WriteMetaDataToDir(rPath, rProp->GetKey(), rProp->GetTypeN());
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** write the property data to file. Filename is determined by the key
     *
     * @param rPath the dir path
     * @param property to read key and data from
     */
    void WritePropDataToDir(std::string const& rPath, GenPropertyBase* pProp)
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
        std::ifstream meta_file(rPath.c_str());

        if (meta_file.is_open())
        {
            if (meta_file.good())
            {
                std::getline(meta_file, rType);
            }
        }
        meta_file.close();

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

        /* string exception */
        if (pProp->GetTypeN() == GetTypeName<std::string>())
            ((GenProperty<std::string>*)pProp)->SetValue(buffer);
        else
            pProp->SetValueFromString(buffer);
    }

}

