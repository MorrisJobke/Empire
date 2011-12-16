#include <string>
using namespace std;

template<class T> class Property 
{
protected:
    string key;
    string description;
    T value;

public:
    T GetValue() {
        return value;
    }

    void SetValue(T val) {
        value = val;
    }
};


// template<class T> T Stack<T>::GetValue()
// {
//     return value;
// }

class PropertyInteger : public Property<int>
{
};

class PropertyString  : public Property<string> 
{
};