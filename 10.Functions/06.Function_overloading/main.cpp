/*
    . Function overloading:
        . Concept: Functions with the same name but different parameters.
            . The differences may be in the type of the parameters or the number of parameters.
            . The return type is not considered. 
        . Basic examples
        . Overloading to handle arrays and pointers
        . Overloading std::getline: an example.
        . Some fun examples


    . Build instructions: 
        . Bare hands with CMake: 
            . cmake -S . -B build
            . cmake --build build

        . With CMake presets (VS Code): 
            . Select configure preset
            . Select build preset
            . Use the run and debug buttons: We can debug application right from the start.

        . Can also use presets on the command line.
    . Dependencies: 
        . gcc 14 or up (can be official container)
        . cmake 3.29 or up
        . ninja 1.11 or up
        . vcpkg and setting up the VCPKG_ROOT environment variable
        . gdb any version

    . Philosophy: 
        . All non module looking code should be hidden away in the utilities module.

*/

#include <fmt/format.h>
import utilities;

int main() {

    //overloading_1_demo();
    //overloading_2_demo();
    //overloading_3_demo();
    overloading_4_demo();

    return 0;

   


}