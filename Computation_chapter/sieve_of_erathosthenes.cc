#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


int main()
{
    std::vector<int> list(100); 
    for(int i = 0; i < list.size(); i++){
        list[i] = i;
    }
    
    for(int i = 2; i < sqrt(list.size()); i++){
        if(list[i] != 0){
            for(int j = i+i; j < list.size(); j+=i){
                list[j] = 0;
            }
        }
    }

    for (int i = 2; i < list.size(); i++){
        if(list[i] != 0) {
            std::cout << list[i] << " ";
        }
    }

}