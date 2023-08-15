#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

namespace X {
    int var{};
    void print(){
        std::cout << "X " << var << '\n';
    }
}


namespace Y {
    int var{};
    void print(){
        std::cout << "Y " <<var << '\n';
    }
}


namespace Z {
    int var{};
    void print(){
        std::cout << "Z " <<var << '\n';
    }
}

int main()
{
    X::var = 7;
    X::print();
    using namespace Y;
    var = 9;
    print();
    {
        using Z::var;
        using Z::print;
        var = 11;
        print();
    }
    print();
    X::print();
}