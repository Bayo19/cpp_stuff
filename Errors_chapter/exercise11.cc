#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits.h>

int main()
{
    // Print all fibo numbers that can fit into INT

    std::vector<int> fibo = {0,1,1};
    int i = 1, j = 2;
    unsigned long cur;
    std::cout << 1 << " " << 2 << " " << 3 << " ";
    while((cur = fibo[i] + fibo[j]) <= INT_MAX){
        std::cout << cur << " ";
        fibo.push_back(cur);
        i++, j++;
    }
}