#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
  std::cout << "Please enter your first and second names\n";
  string first;
  string second;
  std::cin >> first >> second; // read two strings
  string name = first + ' ' + second; // concatenate strings
  std::cout << "Hello there, " << name << '\n';

}
