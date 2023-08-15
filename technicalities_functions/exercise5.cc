#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


std::vector<int> reverse_vector(std::vector<int> numbers)
{
    std::vector<int> reversed_numbers;
    int i = numbers.size() - 1;

    for(; i >= 0; i--){
        reversed_numbers.push_back(numbers[i]);
    }

    return reversed_numbers;
}


void reverse_vector_in_place(std::vector<int>& numbers)
{   
    int j = numbers.size() - 1;
    int temp;
    for(int i = 0; i <= (numbers.size() / 2); i++){
        temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
        j --;
    }

    for(int& num : numbers){
        std::cout << num << ' ';
    }   
    std::cout << '\n';
}


int main(){
    std::vector<int> original_numbers = {1,3,5,7,9,11,13};
    reverse_vector_in_place(original_numbers);
    // std::vector<int> new_numbers = reverse_vector(original_numbers);

    // for(int num: new_numbers){
    //     std::cout << num << ' ';
    // }
    // std::cout << '\n';
    return 0;
}