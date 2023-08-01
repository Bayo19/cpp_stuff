#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


class Name_value {
public:
    std::string name;
    int value;
    Name_value(std::string name, int score)
        :name(name), value(score) {}
};


class Name_val_stream {
public:    
    bool seen(std::string name);
    void put(Name_value name_val);
    void print_all();

private:
    std::vector<Name_value> stream{};
};


bool Name_val_stream::seen(std::string name)
{
    for(Name_value taken_name: stream){
        if(taken_name.name == name){
            return true;
        }
    }

    return false;
}


void Name_val_stream::print_all()
{
    for(Name_value name_val: stream){
        std::cout << name_val.name << " " << name_val.value << '\n';
    }
}


void Name_val_stream::put(Name_value name_val)
{
    stream.push_back(name_val);
}


int main()
{   
    std::string name;
    int value;
    Name_val_stream nvs;

    std::cout << "Enter a name and score:\n";
    while(true){
        std::cin >> name >> value;
        
        if(name == "NoName" || value == 0){
            nvs.print_all();
            break;
        }

        if(nvs.seen(name)){
            std::cout << "Name entered twice.\n";
            nvs.print_all();
            break;
        }

        Name_value nv = Name_value(name, value);
        nvs.put(nv);
    }
}