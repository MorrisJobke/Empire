
/* Collection.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-17.
 * @Editor:      Vim
 */

#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include <list>

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
    
    std::string mPath;

    void WriteToDir(std::string const& rPath);

    public:

    Coll();
    Coll(std::string const& rPath);

    ~Coll();

    void Declare(std::list<GenPropertyBase*> const&);
    void AddRow(std::list<GenPropertyBase*> const&);

    std::list< std::list<GenPropertyBase*> > GetList() const;


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


#endif
