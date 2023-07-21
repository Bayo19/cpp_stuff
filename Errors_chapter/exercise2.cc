#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

// exercises 2 to 5
void error (std::string s)
{
  throw std::runtime_error (s);
}

double ctok(double c)
{
    // Celsius to Kelvin
    if (c < -273.15){
        error("Temp given below absolute zero");
    }

    double k = c + 273.15;
    return k;
}

double ktoc(double k){
    if (k < 0){
        error("Temp given below absolute zero");
    }
    
    double c = k - 273.15;
    return c;
}


int main()
{
    double celsius{};
    std::cin >> celsius;
    double kelvin = ctok(celsius);
    std::cout << kelvin << "\n";
}
