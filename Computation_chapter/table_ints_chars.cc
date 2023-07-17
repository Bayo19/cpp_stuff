#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int main()
{   
    char letter = 'a';
    char upper_letter = 'A';
    int upper_num = upper_letter;
    int max_upper_num = upper_num + 26;
    int num = letter;
    int max_int = num + 26;

    while(num < max_int){
        letter = num;
        std::cout << letter << ' ' << num << std::endl;
        ++num;
    }

    std::cout << "\n\n\n";
    
    for(int i = upper_letter; i < max_upper_num; i++){
        upper_letter = i;
        std::cout << upper_letter << ' ' << i << std::endl;
    }

    return 0;
    
}