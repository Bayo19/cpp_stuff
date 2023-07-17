#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


int add_(int x, int y){
    return x + y;
}

int subtract_(int x, int y){
    return x - y;
}

int multiply_(int x, int y){
    return x * y;
}

int divide_(int x, int y){
    return x / y;
}

int string_to_int(std::string string_number){
    std::vector <std::string> numbers = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for(int i = 0; i < numbers.size(); i++){
        if (string_number == numbers[i]){
            return i;
        }
    }
    return -1;
}


int main()
{
    int first_number, second_number;
    std::string first_word, second_word;
    char operator_;
    std::string option;
    float result;

    std::cout << "Enter 'text' to use the calculator with spelled out numbers or 'digit' to use digits:\n";
    std::cin >> option;

    if (option == "text")
    {
        std::cout << "Enter two single digit numbers (spelled out) and an operator, (e.g. +, -, *, /)\n";
        std::cin >> first_word >> second_word >> operator_;

        first_number = string_to_int(first_word);
        second_number = string_to_int(second_word);

    } else if (option == "digit")
    {
        std::cout << "Enter two single digit numbers (as digits) and an operator, (e.g. +, -, *, /)\n";
        std::cin >> first_number >> second_number >> operator_;
    }

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