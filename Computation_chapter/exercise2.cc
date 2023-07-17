#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int main()
{
    std::vector <double> distances;
    double distance, sum_of_all_distances;
    double smallest_distance, greatest_distance, mean_distance;

    while (std::cin >> distance){
        sum_of_all_distances += distance;
        distances.push_back(distance);
    }

    std::sort(distances.begin(), distances.end());
    smallest_distance = distances[0];
    greatest_distance = distances[distances.size() - 1];
    mean_distance = sum_of_all_distances / distances.size();

    std::cout << "Smallest distance: " << smallest_distance << "\n";
    std::cout << "Greatest distance: " << greatest_distance << "\n";
    std::cout << "Mean distance: " << mean_distance << "\n";

}