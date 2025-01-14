Chapter 9: Characters and Strings: 
    * Challenges to flex your C++ muscles.
    * Note: 
      * Please carry out these challenges manually without using code generation tools like ChatGPT
      * Doing so will hurt your learning process and hinder your progress.

1. Character Analysis Tool

    Write a program in the main function that:

    * Asks the user to enter a line of text.
    * Counts and prints how many uppercase letters, lowercase letters, digits, and punctuation marks the text contains.
    * Use functions from <cctype> like isupper(), islower(), isdigit(), and ispunct().
    * The program should repeatedly ask the user if they want to continue and give them the option to enter another line of text, until they choose to stop.
    * The code should not use C++ types like std::string or std::vector.
    * It should use C-style strings and functions from <cctype> to analyze the input.

2. Manual String Copy

Write a program that does the following:

    *  Ask the user to enter a C-string (up to 100 characters).
    *  Dynamically allocate memory for another C-string of the same size.
    *  Copy the content of the first string into the second one using <cstring> functions.
    * Print the copied string.
    * The program should repeatedly ask the user if they want to continue and give them the option to enter another string, until they choose to stop.
    * Before exiting, the program should free any dynamically allocated memory.

3. Word Reverser Program

    Write a program that does the following:

    * Ask the user to enter a sentence.
    * Reverse each word in the sentence but keep the order of the words.
    * Use std::string to manipulate the text.
    * The program should repeatedly ask the user if they want to continue and give them the option to enter another sentence, until they choose to stop.
    * Program flow visualized: 
      * +--------------------------------------------------+
        | Initial sentence: "The sky is blue"              |
        +--------------------------------------------------+
                        |
                        v
        +----------------------------------+------------------+
        | Iterating through sentence...   | "The sky is blue"|
        | Start from index 0               |                  |
        +----------------------------------+------------------+
                        |
                        v
        +----------------------------------+------------------+
        | Find first space at index 3     | "The" (word)     |
        | Reverse "The" -> "ehT"          |                  |
        +----------------------------------+------------------+
                        |
                        v
        +----------------------------------+------------------+
        | Reversed sentence: "ehT"        | "sky is blue"    |
        +----------------------------------+------------------+
                        |
                        v
        +----------------------------------+------------------+
        | Find next space at index 7      | "sky" (word)     |
        | Reverse "sky" -> "yks"          |                  |
        +----------------------------------+------------------+
                        |
                        v
        +----------------------------------+------------------+
        | Reversed sentence: "ehT yks"    | "is blue"        |
        +----------------------------------+------------------+
                        |
                        v
        +----------------------------------+------------------+
        | Find next space at index 10     | "is" (word)      |
        | Reverse "is" -> "si"            |                  |
        +----------------------------------+------------------+
                        |
                        v
        +----------------------------------+------------------+
        | Reversed sentence: "ehT yks si" | "blue"           |
        +----------------------------------+------------------+
                        |
                        v
        +----------------------------------+------------------+
        | Find next space at index npos   | "blue" (last word)|
        | Reverse "blue" -> "eulb"        |                  |
        +----------------------------------+------------------+
                        |
                        v
        +----------------------------------+------------------+
        | Final Reversed sentence: "ehT yks si eulb"       |
        +----------------------------------+------------------+
                        |
                        v
        +----------------------------------+------------------+
        | Print "ehT yks si eulb"         |                  |
        +----------------------------------+------------------+


4. Simple Palindrome Checker

    In the main function:

    * Ask the user to enter a word or phrase.
    * Check if it is a palindrome (reads the same forward and backward).
    * Ignore case and punctuation when checking.
    * Print whether it is a palindrome or not.
    * Use facilities from <string>
    * The program should repeatedly ask the user if they want to continue and give them the option to enter another word or phrase, until they choose to stop.


