#include <iostream>
#include "Vector.hpp"
#include <string>


int main() {
  Vector<int> v1;
  int n = 3;
  for (int i = 0; i < 100; i++) {
    v1.push_back(n);
    std::cout << v1.at(i) << " ";
  }
  std::cout << std::endl;
  std::cout << v1.size() << std::endl;

  Vector<std::string> v2;
  for (int i = 0; i < 100; i++) {
    v2.push_back("-");
  }
  v2.insert(0, "|");
  v2.insert(8, "|");
  v2.insert(5, "|");
  v2.push_back("a");



  for (int i = 0; i < v2.size(); i++) {
    std::cout << v2.at(i);

  }
  std::cout << v2.size() << std::endl;
  std::cout << std::endl;

}
