#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


int main()
{   
    double distance;
    double converted_distance_km;
    std::cout << "Please enter a number to convert from miles to kilometers\n";

    std::cin >> distance;
    converted_distance_km = distance * 1.609;

    std::cout << distance << " miles is " << converted_distance_km << " in km\n";
}