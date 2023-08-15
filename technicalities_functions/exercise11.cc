#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

struct Measurements {
    double min{};
    double max{};
    double mean{};
    double median{};
};

Measurements computer_measurments(std::vector<double>& vector_list)
{
    Measurements results;
    double sum_of_vector_list{};

    results.min = *std::min_element(vector_list.begin(), vector_list.end());
    results.max = *std::max_element(vector_list.begin(), vector_list.end());

    for(int i = 0; i < vector_list.size(); i++)
    {   
        sum_of_vector_list+= vector_list[i];
    }

    results.mean = sum_of_vector_list / vector_list.size();

    std::sort(vector_list.begin(), vector_list.end());
    if(vector_list.size() %2 != 0)
    {
        results.median = vector_list[(vector_list.size() / 2) + 1];
    } else {
        results.median = vector_list[
            ( (vector_list.size() / 2 + 1) +
            (vector_list.size() / 2 + 2) )
            / 2
        ];
    }
    return results;
}

int main()
{
    std::vector<double> numbers = {4, 2, 9 , 11, 1.48, 17, 5};
    std::cout << "min " << computer_measurments(numbers).min << '\n';
    std::cout << "max " << computer_measurments(numbers).max << '\n';
    std::cout << "mean " << computer_measurments(numbers).mean << '\n';
    std::cout << "median " << computer_measurments(numbers).median << '\n';

}