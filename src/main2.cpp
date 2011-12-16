#include "PropertyInteger.h"
#include <string>
#include <iostream>

int main() {
    PropertyInteger intProp = PropertyInteger(42);

    std::cout << "PropertyInteger: " << intProp.GetValue() << std::endl;

    return 0;
}