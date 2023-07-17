#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int main()
{   
    std::vector <std::string> numbers = {"zero", "one", "two", "three", 
                                        "four", "five", "six", "seven", 
                                        "eight", "nine"};
    int value;
    
    std::cout << "Enter a value from 0 to 9 as a digit of text value: \n";

    while(std::cin >> value){
        if(value >=0 && value <= 9){
            std::cout << value << ": " << numbers[value] << "\n";
        } else {
            std::cout << value << " is an invalid value.\n";
        }
    }

}