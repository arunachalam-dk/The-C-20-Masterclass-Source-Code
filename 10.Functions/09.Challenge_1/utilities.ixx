module;

#include <SFML/Graphics.hpp> // Global module fragment

export module utilities; 

namespace it_1
{
    export void app(){

        sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }

    }
    
} // namespace it_1

namespace it_2
{
    // Function to initialize the window and circle
    void init(sf::RenderWindow& window, sf::CircleShape& circle) {
        // Configure the window
        window.create(sf::VideoMode(800, 600), "SFML works!");

        // Configure the circle
        circle.setRadius(100.f);
        circle.setFillColor(sf::Color::Green); // Green circle
        circle.setPosition(300.f, 200.f);      // Centered in wider window
    }

    // Function to handle events
    void process_events(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    // Function to render the scene
    void render(sf::RenderWindow& window, const sf::CircleShape& shape) {
        window.clear(sf::Color::Black); // Black background
        window.draw(shape);
        window.display();
    }

    export void app() {
        sf::RenderWindow window;
        sf::CircleShape circle;

        // Initialize the window and circle
        init(window, circle);

        while (window.isOpen()) {
            process_events(window);  // Handle input
            render(window, circle);  // Render shapes
        }
    }
   
} // namespace it_2



