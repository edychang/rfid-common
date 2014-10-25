
#include "test_byte_array.h"

#include <iostream>

int main()
{
  byte_array_tester tester;
  tester.run_tests();
  std::cout << "Test cases passed!" << std::endl;
  std::cin.ignore();
}
