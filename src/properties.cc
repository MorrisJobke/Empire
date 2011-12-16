#include "properties.h"
#include <string>
#include <iostream>


int main() {
    PropertyInteger intProp = PropertyInteger();
    intProp.SetValue(42);
    PropertyString stringProp = PropertyString();
    stringProp.SetValue("Lorem Ipsum");

    std::cout << "PropertyInteger: " << intProp.GetValue() << std::endl;
    std::cout << "PropertyString: " << stringProp.GetValue() << std::endl;

    return 0;
}