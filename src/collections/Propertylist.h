
/* <+FILE NAME+>
 * @Author:      <+AUTHOR+> (<+EMAIL+>)
 * @License:     <+LICENSE+>
 * @Created:     <+DATE+>.
 * @Editor:      Vim
 */

#ifndef STRINGLIST_H
#define STRINGLIST_H

struct Propertylist
{
    Property prop;
    struct Propertylist *next;
};

#endif
