#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

void people_sorted(std::vector<std::string>& names_list, std::vector<double>& ages_list)
{
    std::vector<std::string> names_list_copy = names_list;
    std::vector<double> ages_list_copy = ages_list;

    std::sort(names_list.begin(), names_list.end());

    for(int i = 0; i < names_list.size(); i++)
    {   
        std::string name = names_list[i];
        auto name_index = std::find(names_list_copy.begin(), names_list_copy.end(), name);

        if(name_index != names_list.end())
        {
           int index = name_index - names_list_copy.begin();
           ages_list[i] = ages_list_copy[index]; 
        }

    }

}


int main()
{
    std::vector<std::string> names;
    std::vector<double> ages;
    std::string name;
    int age;

    std::cout << "Please enter 5 names: \n";
    for(int i{}; i < 5; i++)
    {
        std::cout << (i+1) << ": ";
        std::cin >> name;
        names.push_back(name);
    }

    std::cout << "Please enter their ages: \n";

    for(int i{}; i < 5; i++)
    {
        std::cout << (i+1) << ": ";
        std::cin >> age;
        ages.push_back(age);
    }

    people_sorted(names, ages);
    for(int i{}; i < 5; i++)
    {
        std::cout << '(' << names[i] << ',' << ' ' << ages[i] << ')' << '\n';
    }

}