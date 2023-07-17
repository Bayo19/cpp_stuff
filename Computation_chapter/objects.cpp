// #include "std_lib_facilities.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

inline void simple_error(string s)  // write ``error: s`` and exit program
{
    cerr << "error: " << s << '\n';
    exit(1);
}


int main()
{
  string name;
  string friend_name;
  int age;
  char friend_sex = 0;

  std::cout << "Enter the name of the person you want to write to\n"; 
  std::cin >> name;
  
  std::cout << "Enter the age of the recipient: ";
  std::cin >> age;

  std::cout << "Enter the name of a friend\n";
  std::cin >> friend_name;
  
  std::cout << "Enter m if the friend is a male or f if female\n";
  std::cin >> friend_sex;

  std::cout << "Dear " << name << ". How are you?\nI am fine. I miss you.\n";
  std::cout << "Have you seen " << friend_name << " lately?\n";

  if(friend_sex == 'm'){
    std::cout << "If you see " << friend_name << " please ask him to call me.\n";
  } else if (friend_sex == 'f'){
    std::cout << "If you see " << friend_name << " please ask her to call me.\n";
  }

  if (age <= 0 || age > 100){
    simple_error("you're kidding");
  } else {
    std::cout << "I heard you just had a birthday and you are " << age << " years old.\n";

    if (age <= 12) {
        std::cout << "Next year you will be age " << ++age << "\n"; 
    } else if(age > 17 && age < 70){
        std::cout << "Next year you will be able to vote\n";
    } else {
        std::cout << "Enjoy your retirement\n";
    }
  }

  std::cout << "Yours Sincerely,\n\n";
}
