#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

double sum_of_price_weight(std::vector<double> prices, std::vector<int> weights)
{
    double sum{};
    if (prices.size() == weights.size())
    {
        for(int i{}; i < prices.size(); i++)
        {
            sum += (prices[i] * weights[i]);   
        }

        return sum;
    }

    return -1;

}

int main() {}