/*
    Example of overloading to handle arrays and pointers
*/
module;

#include <fmt/format.h>

export module overloading_2;

namespace overloading_2
{
    export void process(int* array, size_t size) {
        fmt::println("Processing array of size {}", size);
    }

    export void process(int value) {
        fmt::println("Processing single value: {}", value);
    }
    
} // namespace overloading_2
