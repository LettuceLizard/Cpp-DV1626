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
  if (v2.empty()) {
    std::cout << "1 is empty" << std::endl;
  }
  for (int i = 0; i < 100; i++) {
    v2.push_back("ya yeet");
    std::cout << v2.at(i) << " ";
  }
  std::cout << v2.size() << std::endl;
  std::cout << std::endl;

  if (v2.empty()) {
    std::cout << "2 is empty" << std::endl;
  }

}
