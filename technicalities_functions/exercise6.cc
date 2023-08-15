#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<std::string> reverse_strings_list(std::vector<std::string> strings)
{
    std::vector<std::string> new_strings{};
    for(int i = strings.size() - 1; i >= 0; i--){
        new_strings.push_back(strings[i]);
    }

    return new_strings;
}

void reverse_strings_list_in_place(std::vector<std::string>& strings)
{
    int j = strings.size() - 1;
    std::string temp;
    for(int i = 0; i <= (strings.size() / 2); i++){
        temp = strings[i];
        strings[i] = strings[j];
        strings[j] = temp;
        j--;
    }

    for(std::string s : strings){
        std::cout << s << ' ';
    }   
    std::cout << '\n';
}


int main()
{
    std::vector<std::string> original_strings = {"Bethany", "Janet", "Naomi", "Darlene"};
    std::vector<std::string> reversed_strings = reverse_strings_list(original_strings);
    reverse_strings_list_in_place(original_strings);
    // for(std::string s : reversed_strings){
    //     std::cout << s << ' ';
    // }
    // std::cout << '\n';
}