#include <iostream>
#include "Calculator.h"


int main()
{
    int result= add(5, 5);
    cout << result << endl;
    saveResponse();
    std::cin;
}