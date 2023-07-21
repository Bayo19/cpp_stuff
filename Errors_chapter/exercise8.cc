#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

void error (std::string s)
{
  throw std::runtime_error (s);
}

void print_numbers(int n, std::vector<float> list){
    std::cout << "( ";
    for(int i = 0; i < n; i++){
        std::cout << list[i] << " ";
    }
    std::cout << ") ";
}

int main()
{   
    int num_of_vals_to_sum{};
    double sum_of_vals{};
    double number{};
    std::vector<float> list_of_values;
    std::cout << "Please enter the number of values you want to sum: \n";
    std::cin >> num_of_vals_to_sum;
    
    std::cout << "Please enter asome integers (press '|' to stop): ";
    while(std::cin >> number){
        list_of_values.push_back(number);
    }

    if (list_of_values.size() < num_of_vals_to_sum){
        error("Not enough values entered.\n");
    }

    for(int i = 0; i < num_of_vals_to_sum; i++){
        sum_of_vals += list_of_values[i];
    }

    std::cout << "The sum of the first " << num_of_vals_to_sum << " numbers "; 
    print_numbers(num_of_vals_to_sum, list_of_values);
    std::cout << "is " << sum_of_vals << '\n';
}