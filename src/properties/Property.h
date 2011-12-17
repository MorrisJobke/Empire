
/* <+FILE NAME+>
 * @Author:      <+AUTHOR+> (<+EMAIL+>)
 * @License:     <+LICENSE+>
 * @Created:     <+DATE+>.
 * @Editor:      Vim
 */

#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
using namespace std;


template<class T> class Property 
{
protected:
    string mKey;
    string mDescription;
    T mValue;

    void Init(T value);
    void Init(string const& key, T value);
    void Init(string const& key, string const& description, T value);

public:
    Property();
    ~Property();

    T GetValue() const;
    void SetValue(T value);
};

#endif
