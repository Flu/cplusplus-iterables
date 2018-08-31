#include "cppit.cpp"

#include <functional>
#include <iostream>

int main() {
  cppit::String test_string("Hello, I am Batman!");
  cppit::String second_string = test_string;
  std::cout << test_string << ", " << second_string;
  return 0;
}
