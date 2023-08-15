#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

double maxv(std::vector<double>& numbers)
{
    double max{};
    for(double num: numbers)
    {
        if (num > max) max = num;
    }

    return max;
}

int main()
{
    std::vector<double> num_list = {3,6,5,8,2};
    std::cout << maxv(num_list) << '\n';
    
    return 0;
}