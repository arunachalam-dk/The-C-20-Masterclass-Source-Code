/*
    . Palindrome checker
        . Raw
        . Using the ftxui library
*/
module;
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include <ftxui/dom/elements.hpp>       // for text, Element, hbox, vbox, border
#include <ftxui/screen/screen.hpp>      // for Screen
#include <ftxui/component/component.hpp> // for Input, Renderer, ScreenInteractive
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive

export module utilities; 
/*
    . Raw palindrome checker
*/
namespace it_1{
    // Function to check if a string is a palindrome, ignoring spaces and case
    bool is_palindrome(const std::string& input) {
        // Remove spaces and convert to lowercase
        std::string cleaned;
        for (char ch : input) {
            if (!std::isspace(static_cast<unsigned char>(ch))) {
                cleaned += std::tolower(static_cast<unsigned char>(ch));
            }
        }

        // Use std::string_view for efficient comparison without creating new copies
        std::string_view view(cleaned);

        // Check if the string is a palindrome
        for (size_t i = 0; i < view.size() / 2; ++i) {
            if (view[i] != view[view.size() - 1 - i]) {
                return false;
            }
        }

        return true;
    }

    export void app(){

        std::string text;
        std::cout << "Enter a string to check if it is a palindrome: ";
        std::getline(std::cin, text);

        if (is_palindrome(text)) {
            std::cout << "The string is a palindrome.\n";
        } else {
            std::cout << "The string is not a palindrome.\n";
        }

    }
}   // namespace it_1

/*
    . Palindrome checker with ftxui
    . Using the is_palindrome function from it_1.
*/
namespace it_2{

    export void app(){
        using namespace ftxui;
        // Variables to store user input and result
        std::string user_input;
        std::string result;

        // FTXUI Input component
        auto input_component = Input(&user_input, "Enter text");

        // Renderer to display input and output
        auto renderer = Renderer(input_component, [&]() {
            // Check if input is a palindrome and update the result
            if (user_input.empty()) {
                result = "Enter a string to check if it is a palindrome.";
            } else if (it_1::is_palindrome(user_input)) {
                result = "The string is a palindrome!";
            } else {
                result = "The string is not a palindrome.";
            }

            // Render the FTXUI UI components
            return vbox({
                text("Palindrome Checker") | bold | color(Color::Yellow),
                separator(),
                hbox(text("Input: "), input_component->Render()) | border,
                separator(),
                text("Result: " + result) | color(it_1::is_palindrome(user_input) ? Color::Green : Color::Red),
            });
        });

        // Create the interactive screen and run the main loop
        auto screen = ScreenInteractive::TerminalOutput();
        screen.Loop(renderer);
    }
    
} // namespace it_2