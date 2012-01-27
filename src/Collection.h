
/* Collection.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-17.
 * @Editor:      Vim
 */

#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include <sstream>
#include <list>

//#include <unistd.h>
//#include <sys/stat.h>
//#include <dirent.h>

#include "Filesystem.h"
#include "GenPropertyBase.h"
#include "GenProperty.h"

DEFINE_VAR_EXCEPTION(ErrorColl)

/** collection class
 */
class Coll
{
    private:
    std::list< std::list<GenPropertyBase*> > mPropList;
    std::list<GenPropertyBase*> mMetaList;
    std::string mKey;

    public:

    Coll();
    Coll(std::string const& rPath);

    ~Coll();

    void Load(std::string const& rPath, std::string const& rMetaPath);
    void Declare(std::list<GenPropertyBase*> const&, std::string const& rMetaPath);
    void AddRow(std::list<GenPropertyBase*> const&);

    std::list< std::list<GenPropertyBase*> > GetList() const;
    std::list< GenPropertyBase* > GetPropertyList();
    int GetRowCount();
    void ToOutStream(std::ostream& rOut);

    void DebugPrint();



    /* NOTES:
     *
     * - beim initialisieren laden von festplatte
     * - alle aktionen schreiben sofort auf die platte
     * - mehrere ordner 0 - n, die nullten sind meta files --> declare methode
     * - fill methode propertie liste mit zeigern werte extrahieren
     *
     * - destructor
     *
     *
     */
};

std::ostream& operator<<(std::ostream& rOut, Coll rColl);
std::istream& operator>>(std::istream& rIn, Coll rColl);


#endif
