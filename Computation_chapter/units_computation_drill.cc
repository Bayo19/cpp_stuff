#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

double m_to_cm(double value){
    return value * 100.0;
}

double in_to_cm(double value){
    return value *2.54;
}

double ft_to_in(double value){
    return value * 12;
}

int main()
{
    double sum_of_values_cm;
    double smallest, largest;
    int num_of_valid_values_entered;
    int measurment;
    std::vector <double> valid_values_in_m;
    std::string unit;
    std::vector <int> measurments_list;
    std::vector <std::string> units_list;

    std::cout << "Enter some measurments\n";

    while(std::cin >> measurment && std::cin >> unit){
        if(unit == "cm" || unit == "in" || unit == "m" || unit == "ft"){
            units_list.push_back(unit);
            measurments_list.push_back(measurment);
        }
    }

    if (measurments_list.size() == units_list.size() && measurments_list.size() > 0){
        num_of_valid_values_entered = measurments_list.size();
        double current_value;

        for(int i = 0; i < measurments_list.size(); i++){
            if(units_list[i] == "cm"){
                current_value = measurments_list[i];
                sum_of_values_cm += current_value;
            } else if (units_list[i] == "m"){
                current_value = m_to_cm(measurments_list[i]);
                sum_of_values_cm += current_value;
            } else if (units_list[i] == "in"){
                current_value = in_to_cm(measurments_list[i]);
                sum_of_values_cm += current_value;
            } else { // unit is 'ft'
                current_value = in_to_cm(ft_to_in(measurments_list[i]));
                sum_of_values_cm += current_value;
            }   

            if (current_value > largest){
                    largest = current_value;
            } else if (current_value < smallest){
                smallest = current_value;
            }
            
            valid_values_in_m.push_back(current_value/100);

        }
    } else {
       std::cerr << "Invalid user input";
    }

    std::sort(valid_values_in_m.begin(), valid_values_in_m.end());
    std::cout << "Sum of values in metres: " << (sum_of_values_cm / 100) << "\n";
    for(double i:valid_values_in_m){
        std::cout << i << " ";
    }

    return 0;
}