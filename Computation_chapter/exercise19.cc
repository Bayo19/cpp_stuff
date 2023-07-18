#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

int main()
{
    std::string name;
    int score{};
    std::vector<std::string> names;
    std::vector<int> scores;
    std::cout << "Enter a name and score:\n";

    while(true){
        std::cin >> name >> score;
        if(name == "NoName" || score == 0) break;
        for(std::string entered_name: names){
            if (entered_name == name){
                std::cout << "Name entered twice.\n";
                break;
            }
        }
        names.push_back(name);
        scores.push_back(score);
    }
    
    for(int i{}; i < names.size(); i++){
        std::cout << "Name: " << names[i] << " - " << scores[i] << '\n';
    }

}