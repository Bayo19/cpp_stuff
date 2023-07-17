#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


float add_(float x, float y){
    return x + y;
}

float subtract_(float x, float y){
    return x - y;
}

float multiply_(float x, float y){
    return x * y;
}

float divide_(float x, float y){
    return x / y;
}

int main()
{
    float first_number;
    float second_number;
    char operator_;
    float result;
    std::cout << "Enter two doubles and an operator, (e.g. +, -, *, /)\n";

    std::cin >> first_number >> second_number >> operator_;

    if (operator_ == '+')
    {
        result = add_(first_number, second_number);
    } else if (operator_ == '-')
    {
        result = subtract_(first_number, second_number);
    } else if (operator_ == '*')
    {
        result = multiply_(first_number, second_number);
    } else if (operator_ == '/')
    {
        result = divide_(first_number, second_number);
    }

    std::cout << "The result of " << first_number << " " << operator_ << " " << second_number << " is " << result << "\n";
    
}