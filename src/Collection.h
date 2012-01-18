
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


/** collection class
 */
class coll
{
    std::list<std::list<GenPropertyBase*>> mPropList;

    public:

    coll();
    coll(std::string const& rPath);

    ~coll();

    AddRow(std::list<GenPropertyBase*> const&);

    std::list<std::list<GenPropertyBase*>> GetList() const;

    WriteToDir(std::string const& rPath);

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
