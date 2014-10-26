
#include "test_byte_array.h"
#include "test_byte_stream.h"

#include <iostream>

int main()
{
    byte_array_tester tester;
    tester.run_tests();

    byte_stream_tester tester1;
    tester1.run_tests();

    std::cout << "Test cases passed!" << std::endl;
    std::cin.ignore();
}
