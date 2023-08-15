#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

void print(std::string name, std::vector<int> numbers)
{
    for(int num : numbers)
    {
        std::cout << name << num << '\n';
    }
}


int main()
{   
    std::vector<int> digits = {1,3,4,7};
    print("label_name: ",  digits);
}