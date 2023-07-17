#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int main(){
    // print the smaller, larger, sum, product, difference and ratio of two numbers

    int smaller, larger, sum, product, difference, val1, val2;
    double ratio;
    std::cout << "Enter two numbers: ";
    std::cin >> val1 >> val2;

    if (val1 > val2){
        smaller = val2;
        larger = val1;
    } else {
        smaller = val1;
        larger = val2;
    }

    sum = val1 + val1;
    product = val1 * val2;
    difference = larger - smaller;
    ratio = larger / smaller;

    std::cout << "Sum: " << sum << "\n";
    std::cout << "Product: " << product << "\n";
    std::cout << "Difference: " << difference << "\n";
    std::cout << "Ratio: " << ratio << "\n";

    return 0;
}