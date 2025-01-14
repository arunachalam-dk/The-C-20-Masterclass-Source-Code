module;

#include <iostream>
#include <cctype>
#include <cstring>

#include <iostream>
#include <string>
#include <limits>
#include <algorithm>

#include <fmt/format.h>

export module utilities;

/*
1. Character Analysis Tool

    Write a program in the main function that:

    * Asks the user to enter a line of text.
    * Counts and prints how many uppercase letters, lowercase letters, digits, and punctuation marks the text contains.
    * Use functions from <cctype> like isupper(), islower(), isdigit(), and ispunct().
    * The program should repeatedly ask the user if they want to continue and give them the option to enter another line of text, until they choose to stop.
    * The code should not use C++ types like std::string or std::vector.
    * It should use C-style strings and functions from <cctype> to analyze the input.

*/
namespace challenge_1{
    
    void analyze_text(const char* text) {
        int uppercase_count = 0;
        int lowercase_count = 0;
        int digit_count = 0;
        int punctuation_count = 0;

        for (size_t i = 0; text[i] != '\0'; ++i) {
            char ch = text[i];
            if (std::isupper(static_cast<unsigned char>(ch))) {
                ++uppercase_count;
            } else if (std::islower(static_cast<unsigned char>(ch))) {
                ++lowercase_count;
            } else if (std::isdigit(static_cast<unsigned char>(ch))) {
                ++digit_count;
            } else if (std::ispunct(static_cast<unsigned char>(ch))) {
                ++punctuation_count;
            }
        }

        fmt::println("Uppercase letters: {}", uppercase_count);
        fmt::println("Lowercase letters: {}", lowercase_count);
        fmt::println("Digits: {}", digit_count);
        fmt::println("Punctuation marks: {}", punctuation_count);
    }

    export void app(){

        const int MAX_LENGTH = 1024;
        char input[MAX_LENGTH] = {0}; // initialize all elements to 0

        bool end{false};

        while(!end){
            fmt::print("Enter a line of text:");
            std::cin.getline(input, MAX_LENGTH);

            analyze_text(input);

            fmt::print("Do you want to continue? (y/n): ");
            char go_on;
            std::cin >> go_on;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            end = !(go_on == 'y' || go_on == 'Y');
        }
        fmt::println("Goodbye!");

    }
}   // namespace challenge_1

/*
2. Manual String Copy

Write a program that does the following:

    * Ask the user to enter a C-string (up to 100 characters).
    * Dynamically allocate memory for another C-string of the same size.
    * Copy the content of the first string into the second one using <cstring> functions.
    * Print the copied string.
    * The program should repeatedly ask the user if they want to continue and give them the option to enter another string, until they choose to stop.
    * Before exiting, the program should free any dynamically allocated memory.
*/
namespace challenge_2
{

    export void app(){

        const int MAX_LENGTH = 1024;
        char input[MAX_LENGTH] = {0}; // initialize all elements to 0

        bool end{false};

        while (!end) {

            //Clear the input array and set all elements to 0
            std::memset(input, 0, MAX_LENGTH);

            // Ask the user to enter a C-string
            fmt::print("Enter a string (up to {} characters): ", MAX_LENGTH - 1);
            std::cin.getline(input, MAX_LENGTH);

            // Check if the user entered an empty string
            if (input[0] == '\0') {
                fmt::println("You entered an empty string. Try again!");
                continue;
            }

            // Dynamically allocate memory for the second string
            size_t length = std::strlen(input) + 1; // +1 for the null-terminator
            char* copied_string = new char[length];

            // Copy the content of the first string into the second string
            std::strcpy(copied_string, input);

            // Manually copy the characters from input to copied_string
            /*
            for (size_t i = 0; i < length; ++i) {
                copied_string[i] = input[i];  // Copy each character
            }
            */

            // Print the copied string
            fmt::println("Copied string: {}", copied_string);

            // Free the dynamically allocated memory
            delete[] copied_string;

            // Ask the user if they want to continue
            fmt::print("Do you want to enter another string? (y/n): ");
            char go_on;
            std::cin >> go_on;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            end = !(go_on == 'y' || go_on == 'Y');
        }

        fmt::println("Goodbye!");

    }
    
} // namespace challenge_2


/*
3. Word Reverser Program

    Write a program that does the following:

    * Ask the user to enter a sentence.
    * Reverse each word in the sentence but keep the order of the words.
    * Use std::string to manipulate the text.
    * The program should repeatedly ask the user if they want to continue and give them the option to enter another sentence, until they choose to stop.
*/

namespace challenge_3
{
    export void app() {
        bool end{false};

        while (!end) {
            // Ask the user to enter a sentence
            fmt::print("Enter a sentence: ");
            std::string sentence;
            std::getline(std::cin, sentence);

            std::string reversed_sentence;
            size_t start = 0;
            size_t end_pos;

            // Iterate through the sentence
            while ((end_pos = sentence.find(' ', start)) != std::string::npos) {
                // Extract the word
                std::string word = sentence.substr(start, end_pos - start);
                // Reverse the word
                std::reverse(word.begin(), word.end());
                // Append the reversed word to the sentence
                reversed_sentence += word + " ";
                start = end_pos + 1;
            }

            // Handle the last word (after the last space)
            std::string last_word = sentence.substr(start);
            std::reverse(last_word.begin(), last_word.end());
            reversed_sentence += last_word;

            // Print the reversed sentence
            fmt::println("Reversed sentence: {}", reversed_sentence);

            // Ask the user if they want to continue
            fmt::print("Do you want to enter another sentence? (y/n): ");
            char go_on;
            std::cin >> go_on;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            end = !(go_on == 'y' || go_on == 'Y');
        }

        fmt::println("Goodbye!");
    }   
    
} // namespace challenge_3


/*
4. Simple Palindrome Checker

    In the main function:

    * Ask the user to enter a word or phrase.
    * Check if it is a palindrome (reads the same forward and backward).
    * Ignore case and punctuation when checking.
    * Print whether it is a palindrome or not.
    * Use facilities from <string>
    * The program should repeatedly ask the user if they want to continue and give them the option to enter another word or phrase, until they choose to stop.
*/

namespace challenge_4
{

    bool is_palindrome(const std::string& str) {
        size_t start = 0;
        size_t end = str.size() - 1;

        while (start < end) {
            // Skip non-alphanumeric characters
            while (start < end && !std::isalnum(str[start])) {
                start++;
            }
            while (start < end && !std::isalnum(str[end])) {
                end--;
            }

            // Compare characters (case-insensitive)
            if (std::tolower(str[start]) != std::tolower(str[end])) {
                return false;
            }

            start++;
            end--;
        }

        return true;
    }

    export void app() {
        bool end{false};

        while (!end) {
            // Ask the user to enter a word or phrase
            std::cout << "Enter a word or phrase: ";
            std::string input;
            std::getline(std::cin, input);

            // Check if it's a palindrome
            if (is_palindrome(input)) {
                std::cout << "It is a palindrome!" << std::endl;
            } else {
                std::cout << "It is not a palindrome." << std::endl;
            }

            // Ask the user if they want to continue
            std::cout << "Do you want to enter another word or phrase? (y/n): ";
            char go_on;
            std::cin >> go_on;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            end = !(go_on == 'y' || go_on == 'Y');
        }

        std::cout << "Goodbye!" << std::endl;
    }

    
} // namespace challenge_4



