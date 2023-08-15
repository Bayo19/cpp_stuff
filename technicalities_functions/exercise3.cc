#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

void fibonacci(int x, int y, std::vector<int> v, int n)
{
    // x should be a number adjacent to y in a fibonacci sequence, 
    //      e.g. x = 1, y = 2 or x = 3, y = 5
    // v is an empty vetor
    // n is the number of fibonacci numbers to print
    int i = 0;
    int j = 2;
    v.push_back(x);
    v.push_back(y);

    while(i != n){
        int new_num = v[j-1] + v[j-2];
        v.push_back(new_num);
        i++;
        j++;
    }

    for(int num : v){
        std::cout << num << '\n';
    }
}


int main()
{   
    std::vector<int> empty_list;
    fibonacci(3, 5, empty_list, 6);
}