/*
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

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <sstream>

export module utilities; 

/*
    . Ftxui calculator.
*/
namespace it_1{

    using namespace ftxui;
    // Function overloads for basic calculator operations
    double add(double a, double b) { return a + b; }
    int add(int a, int b) { return a + b; }

    double subtract(double a, double b) { return a - b; }
    int subtract(int a, int b) { return a - b; }

    double multiply(double a, double b) { return a * b; }
    int multiply(int a, int b) { return a * b; }

    double divide(double a, double b) { return b != 0 ? a / b : 0.0; }
    int divide(int a, int b) { return b != 0 ? a / b : 0; }

    // Main calculator function
    export void app() {
        // UI state variables
        double num1 = 0;
        double num2 = 0;
        double result = 0;
        bool is_calculated = false;

        // Input boxes for numbers
        std::string num1_str = "0";
        std::string num2_str = "0";
        auto input1 = Input(&num1_str, "Enter first number");
        auto input2 = Input(&num2_str, "Enter second number");

        // Operation selector menu
        std::vector<std::string> operations = { "Add", "Subtract", "Multiply", "Divide" };
        int operation_index = 0; // 0 for Add, 1 for Subtract, etc.
        auto operation_menu = Menu(&operations, &operation_index);

        // Calculate button
        auto button = Button("Calculate", [&] {
            num1 = std::stod(num1_str);
            num2 = std::stod(num2_str);

            // Perform the selected operation using function overloading
            switch (operation_index) {
                case 0: result = add(num1, num2); break;
                case 1: result = subtract(num1, num2); break;
                case 2: result = multiply(num1, num2); break;
                case 3: result = divide(num1, num2); break;
            }

            is_calculated = true;
        });

        // Renderer for the UI components
        auto container = Container::Vertical({
            input1,
            input2,
            operation_menu,
            button
        });

        auto renderer = Renderer(container, [&]() {
            return vbox({
                text("Basic Calculator") | bold | center,
                separator(),
                hbox(text("First Number: "), input1->Render()) | center,
                hbox(text("Second Number: "), input2->Render()) | center,
                hbox(text("Operation: "), operation_menu->Render()) | center,
                button->Render() | center,
                separator(),
                is_calculated ? text("Result: " + std::to_string(result)) | bold | center : text("")
            }) | border;
        });

        // Launch the UI
        auto screen = ScreenInteractive::TerminalOutput();
        screen.Loop(renderer);
    }

} // namespace it_1



/*
    . Sfml show the distance between points.
    . Distance shown as text.
*/
namespace it_2{
    // Function to calculate the Euclidean distance between two points
    double calculate_distance(const double origin[2], const double mouse_position[2]) {
        double dx = mouse_position[0] - origin[0];
        double dy = mouse_position[1] - origin[1];
        return std::sqrt(dx * dx + dy * dy);
    }    

    export void app(){
        // Set the origin point (e.g., (100, 100))
        double origin[2] = {0.0, 0.0};

        // Create the main window
        sf::RenderWindow window(sf::VideoMode(800, 600), "Distance from Origin to Mouse Position");

        // Variables for the mouse position and distance
        double mouse_position[2] = {0.0, 0.0};
        double distance = 0.0;

        // Create font and text
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Error loading font. Make sure the font file is in the same directory as the binary.\n";
            return; // Make sure to have the Arial font in the same directory
        }

        sf::Text origin_text;
        origin_text.setFont(font);
        origin_text.setCharacterSize(24);
        origin_text.setFillColor(sf::Color::White);
        origin_text.setPosition(50, 50);
        
        sf::Text mouse_text;
        mouse_text.setFont(font);
        mouse_text.setCharacterSize(24);
        mouse_text.setFillColor(sf::Color::White);
        mouse_text.setPosition(50, 100);

        sf::Text distance_text;
        distance_text.setFont(font);
        distance_text.setCharacterSize(24);
        distance_text.setFillColor(sf::Color::White);
        distance_text.setPosition(50, 150);

        // Main loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // Get the mouse position
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            mouse_position[0] = static_cast<double>(mouse_pos.x);
            mouse_position[1] = static_cast<double>(mouse_pos.y);

            // Calculate distance from origin to mouse position
            distance = calculate_distance(origin, mouse_position);

            // Update the displayed text
            origin_text.setString("Origin Point: (" + std::to_string(origin[0]) + ", " + std::to_string(origin[1]) + ")");
            mouse_text.setString("Mouse Position: (" + std::to_string(mouse_position[0]) + ", " + std::to_string(mouse_position[1]) + ")");
            distance_text.setString("Distance from Origin: " + std::to_string(distance));

            // Clear the window
            window.clear(sf::Color::Black);

            // Draw everything
            window.draw(origin_text);
            window.draw(mouse_text);
            window.draw(distance_text);
            window.display();
        }        
    }
} // namespace it_2


namespace it_3{

    export void app(int argc, char* argv[]) {
        // Check command-line parameters
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <origin_x> <origin_y>" << std::endl;
            return ;
        }

        // Parse origin coordinates from command-line arguments
        double origin[2];
        origin[0] = std::stod(argv[1]); // Origin x-coordinate
        origin[1] = std::stod(argv[2]); // Origin y-coordinate

        // Create the main window
        sf::RenderWindow window(sf::VideoMode(800, 600), "Distance from Origin to Mouse Position");

        // Variables for the mouse position and distance
        double mouse_position[2] = {0.0, 0.0};
        double distance = 0.0;

        // Create font and text
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) { // Ensure the font is in the 'fonts' directory
            std::cerr << "Error loading font. Make sure the font file is in the 'fonts' directory." << std::endl;
            return; // Exit if the font cannot be loaded
        }

        sf::Text distance_text;
        distance_text.setFont(font);
        distance_text.setCharacterSize(24);
        distance_text.setFillColor(sf::Color::White);
        distance_text.setPosition(50, 550); // Position at the bottom of the window

        // Main loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // Get the mouse position
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            mouse_position[0] = static_cast<double>(mouse_pos.x);
            mouse_position[1] = static_cast<double>(mouse_pos.y);

            // Calculate distance from origin to mouse position
            distance = it_2::calculate_distance(origin, mouse_position);

            // Update the displayed distance text
            std::ostringstream oss;
            oss << "Distance from Origin: " << distance;
            distance_text.setString(oss.str());

            // Clear the window
            window.clear(sf::Color::Black);

            // Draw the origin point (red)
            sf::CircleShape origin_point(5); // Radius of 5 pixels
            origin_point.setFillColor(sf::Color::Red);
            origin_point.setPosition(origin[0] - origin_point.getRadius(), origin[1] - origin_point.getRadius()); // Center the point

            // Draw the mouse position point (green)
            sf::CircleShape mouse_point(5); // Radius of 5 pixels
            mouse_point.setFillColor(sf::Color::Green);
            mouse_point.setPosition(mouse_position[0] - mouse_point.getRadius(), mouse_position[1] - mouse_point.getRadius()); // Center the point

            // Draw everything
            window.draw(origin_point);
            window.draw(mouse_point);
            window.draw(distance_text);
            window.display();
        }
        return ;
    }

}   // namespace it_3
