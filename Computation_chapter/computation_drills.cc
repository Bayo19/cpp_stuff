#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


int main()
{
    // Read in two ints
    std::vector <int> numbers;
    double num;
    std::cout << "Please enter any number of integers: \n";

    while(std::cin >> num){
        numbers.push_back(num);
    }
    
    int min = numbers[0], max = numbers[0];

    for(int i = 1; i < numbers.size(); ++i){
        int prev = numbers[i-1];
        int cur = numbers[i];
        if (cur == prev){
            std::cout << "The numbers are equal" << "\n";
        } else if (cur < prev){
            std::cout << "The smaller value is " << cur << ". The larger value is " << prev << "\n";
        } else {
            std::cout << "The smaller value is " << prev<< ". The larger value is " << cur << "\n";
        }

        if (prev < min){
            min = prev;
        }

        if (cur > max){
            max = cur;
        }

        std::cout << "The largest so far: " << max << "\n";
        std::cout << "The smallest so far: " << min << "\n";

    }

}