module;

#include <string_view>
#include <fmt/format.h>
#include <iostream>

export module utilities; 

import overloading_1;
import overloading_2;
import overloading_4;

export void overloading_1_demo(){
    using namespace overloading_1;
    print(42);          // Calls the int version
    print(3.14);        // Calls the double version
    print("Hello!");   // Calls the string version
}


export void overloading_2_demo(){
    using namespace overloading_2;
    int array[] = {1, 2, 3, 4, 5};
    process(array, 5);  // Calls the array version
    process(42);        // Calls the single value version
}

/*
    . Overloading std::getline
    . std::getline is overloaded in the C++ standard library to allow reading a whole line or reading up to a specific delimiter.
    . These are examples I picked up for this lecture, but the exhaustive list of overloads should be checked in the standard library documentation.
*/
export void overloading_3_demo(){
  std::string line;

  // Read a whole line from standard input
  fmt::print("Enter a line: ");
  std::getline(std::cin, line);
  fmt::println("You entered: {}", line);

  // Read up to a specific delimiter (comma)
  fmt::print("Enter values separated by commas: ");
  std::getline(std::cin, line, ',');
  fmt::println("First value: {}", line);  
}


export void overloading_4_demo(){
    using namespace overloading_4;
    fmt::print("Rolling a 6-sided die: {}\n", roll());
    fmt::print("Rolling a 20-sided die: {}\n", roll(20));
    fmt::print("Rolling 3 6-sided dice: {}\n", roll(6, 3));

    fmt::print("Area of a square with side 2.0: {}\n", area(2.0));
    fmt::print("Area of a rectangle with length 2.0 and width 3.0: {}\n", area(2.0, 3.0));
    fmt::print("Area of a circle with radius 1.0: {}\n", area(1.0, true));

    respond();
    respond("What is the meaning of life?");
}