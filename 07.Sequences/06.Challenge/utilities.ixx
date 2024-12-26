module;
#include <string_view>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>

export module utilities; 

/*
  1. Store Multiple Shapes Using Containers
    . Task: Modify the code so that it stores multiple sf::CircleShape objects in an std::vector. 
      The program should initialize the shapes with different radii and positions, and cycle through their colors.
    .  Hint: Use std::vector<sf::CircleShape> to store the shapes.
    .  Objective: Students should get used to working with dynamic containers like std::vector.
*/
namespace it_1{

  export void app(){
    // Store the data in predefined variables
    constexpr int width = 400;
    constexpr int height = 400;  
    constexpr float circleRadius = 50.f;
    constexpr float timerInterval = 5.f;
    const std::string title = "SFML works!";
    const sf::Color backgroundColor = sf::Color::Red;
    const sf::Color shapeColor = sf::Color::Green;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(width, height), title);

    // Create multiple shapes and store them in a vector
    std::vector<sf::CircleShape> shapes;
    for(int i = 0; i < 15; ++i) {
      sf::CircleShape shape(circleRadius + i * 10); // Vary radius slightly for each shape
      shape.setFillColor(shapeColor);
      shape.setPosition(i * 50.f, 50.f); // Set position of each shape
      shapes.push_back(shape);
    }

    while (window.isOpen()) {

      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed){
          window.close();
        }

        // Key press event
        if (event.type == sf::Event::KeyPressed){

          if (event.key.code == sf::Keyboard::Escape){
            window.close();
          }

          // Pressing A and B will change the color of all shapes
          if(event.key.code == sf::Keyboard::A){
            std::cout << "A was pressed" << std::endl;
            for (auto& shape : shapes) {
              shape.setFillColor(sf::Color::Blue);
            }
          }
          if(event.key.code == sf::Keyboard::B){
            std::cout << "B was pressed" << std::endl;
            for (auto& shape : shapes) {
              shape.setFillColor(sf::Color::Yellow);
            }
          }

          // Pressing C and D will change the radius of all shapes
          if(event.key.code == sf::Keyboard::C){
            for (auto& shape : shapes) {
              shape.setRadius(shape.getRadius() + 10.f);
            }
            std::cout << "C was pressed" << std::endl;
          }

          if(event.key.code == sf::Keyboard::D){
            for (auto& shape : shapes) {

              //Protect against negative radius
              if(shape.getRadius() > 10.f)
              {
                shape.setRadius(shape.getRadius() - 10.f);
              }
            }
            std::cout << "D was pressed" << std::endl;
          }

        }
      }

      window.clear(backgroundColor);

      // Draw all the shapes from the vector
      for (const auto& shape : shapes) {
        window.draw(shape);
      }

      window.display();
    }
  }

} // namespace it_1


/*
  2. Track Key Press History with a Fixed-Size Container

    . Task: Track the last 5 keys pressed by the user and display the history in the console. 
      Use std::array<char, 5> to store the key history.
    . Hint: Use an index to cycle through the array and update it with the new key presses.
    . Objective: Practice with std::array for fixed-size containers and updating data circularly.
*/
namespace it_2{
  export void app(){
    // Store the data in predefined variables
    constexpr int width = 200;
    constexpr int height = 200;  
    constexpr float circleRadius = 100.f;
    constexpr float timerInterval = 5.f;
    const std::string title = "SFML works!";
    const sf::Color backgroundColor = sf::Color::Red;
    const sf::Color shapeColor = sf::Color::Green;

    // Create the window and shape
    sf::RenderWindow window(sf::VideoMode(width, height), title);
    sf::CircleShape shape(circleRadius);
    shape.setFillColor(shapeColor);

    // Array to track the last 5 keys pressed
    std::array<char, 5> keyHistory = {' ', ' ', ' ', ' ', ' '};
    size_t keyIndex = 0;

    while (window.isOpen()) {

      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed){
          window.close();
        }

        // Key press event
        if (event.type == sf::Event::KeyPressed){

          if (event.key.code == sf::Keyboard::Escape){
            window.close();
          }

          // Store the key pressed in the key history array
          char pressedKey = ' ';
          if (event.key.code == sf::Keyboard::A) {
            pressedKey = 'A';
            shape.setFillColor(sf::Color::Blue);
          } else if (event.key.code == sf::Keyboard::B) {
            pressedKey = 'B';
            shape.setFillColor(sf::Color::Yellow);
          } else if (event.key.code == sf::Keyboard::C) {
            pressedKey = 'C';
            shape.setRadius(shape.getRadius() + 10.f);
          } else if (event.key.code == sf::Keyboard::D) {
            pressedKey = 'D';
            shape.setRadius(shape.getRadius() - 10.f);
          }

          if (pressedKey != ' ') {
            /*
            //This places the most recent key and the current circular index. Not ideal.
            keyHistory[keyIndex] = pressedKey;
            keyIndex = (keyIndex + 1) % keyHistory.size(); // Update index circularly
            */

            //We want the most recent key to be at index 0
            // Shift all elements to the right
            for (size_t i = keyHistory.size() - 1; i > 0; --i) {
              keyHistory[i] = keyHistory[i - 1];
            }
            // Store the most recent key at index 0
            keyHistory[0] = pressedKey;

            // Display the last 5 keys pressed
            std::cout << "Key history: ";
            for (char key : keyHistory) {
              std::cout << key << ' ';
            }
            std::cout << std::endl;
          }
        }
      }

      window.clear(backgroundColor);
      window.draw(shape);
      window.display();
    }
  }  
} // namespace it_2


/*
  3. Store Color Changes in a Static Array

    . Task: Store a predefined sequence of colors in a built-in array, and cycle through them 
      each time a specific key (e.g., space bar) is pressed to change the shape's fill color.
    . Hint: Use a built-in array like sf::Color colors[4] to store the color sequence and manage the index.
    . Objective: Get familiar with accessing data in built-in arrays and manipulating the shape’s color.
*/
namespace it_3{
  export void app(){
    // Store the data in predefined variables
    constexpr int width = 400;
    constexpr int height = 400;  
    constexpr float circleRadius = 100.f;
    const std::string title = "SFML Color Cycler";
    const sf::Color backgroundColor = sf::Color::Black;

    // Create the window and shape
    sf::RenderWindow window(sf::VideoMode(width, height), title);
    sf::CircleShape shape(circleRadius);
    shape.setPosition(150.f, 150.f);

    // Built-in array to store predefined colors
    sf::Color colors[4] = {
      sf::Color::Red, 
      sf::Color::Green, 
      sf::Color::Blue, 
      sf::Color::Yellow
    };

    // Index to keep track of the current color
    int colorIndex = 0;
    shape.setFillColor(colors[colorIndex]);

    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed){
          window.close();
        }

        // Key press event
        if (event.type == sf::Event::KeyPressed){

          if (event.key.code == sf::Keyboard::Escape){
            window.close();
          }

          // Pressing the space bar will cycle through the colors
          if (event.key.code == sf::Keyboard::Space) {
            // Cycle to the next color
            colorIndex = (colorIndex + 1) % 4; // Wrap around the index
            shape.setFillColor(colors[colorIndex]);
            std::cout << "Color changed to index: " << colorIndex << std::endl;
          }
        }
      }

      window.clear(backgroundColor);
      window.draw(shape);
      window.display();
    }
  } 
} // namespace it_3


/*
  4. Animate Multiple Shapes with Timers and make them bounce when they hit the edges of the window
    . Fill in the details later
*/

namespace it_4
{
  export void app() {
    // Store the data in predefined variables
    constexpr int width = 600;
    constexpr int height = 600;  
    constexpr float circleRadius = 50.f;
    const std::string title = "SFML Multiple Shape Animator";
    const sf::Color backgroundColor = sf::Color::Black;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(width, height), title);

    // Vector to store multiple circles
    std::vector<sf::CircleShape> shapes;

    // Vector to store the movement direction for each shape
    std::vector<sf::Vector2f> directions;

    // Initialize the circles with different positions and colors
    for (int i = 0; i < 5; ++i) {
      sf::CircleShape shape(circleRadius);
      shape.setPosition(100.f * (i + 1), 100.f);
      shape.setFillColor(sf::Color(50 * i, 100 + (30 * i), 200 - (40 * i))); // Unique color for each shape
      shapes.push_back(shape);

      // Initial direction for each shape (moving diagonally)
      directions.emplace_back(20.f, 20.f);
    }

    // Timer setup
    sf::Clock clock;
    constexpr float moveInterval = 0.05f; // Move shapes every 50 milliseconds

    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
          window.close();
        }
      }

      // Timer-based movement
      if (clock.getElapsedTime().asSeconds() > moveInterval) {
        for (size_t i = 0; i < shapes.size(); ++i) {
          auto& shape = shapes[i];
          auto& direction = directions[i];

          // Get the current position of the shape
          sf::Vector2f position = shape.getPosition();

          // Check for collisions with window edges and reverse direction
          if (position.x <= 0.f || position.x + circleRadius * 2 >= width) {
            direction.x = -direction.x; // Reverse horizontal direction
          }
          if (position.y <= 0.f || position.y + circleRadius * 2 >= height) {
            direction.y = -direction.y; // Reverse vertical direction
          }

          // Move the shape in the current direction
          shape.move(direction);
        }

        clock.restart(); // Restart the timer
      }

      // Clear and render all shapes
      window.clear(backgroundColor);
      for (const auto& shape : shapes) {
        window.draw(shape);
      }
      window.display();
    }
  }  
} // namespace it_4

/*
  5. Resize Shape Array Based on Mouse Clicks
    . Task: Start with a fixed number of shapes stored in std::array or std::vector. Each time the 
        left mouse button is pressed, add a new shape to the container. When the right mouse button 
        is pressed, remove the last shape (if any).
    . Hint: Dynamically adjust the size of the container using std::vector and add/remove shapes as needed.
    . Objective: Work with dynamic container resizing, and understand how to manage adding and removing elements in std::vector.
*/

namespace it_5{
  export void app(){
    // Store the data in predefined variables
    constexpr int width = 600;
    constexpr int height = 600;  
    constexpr float circleRadius = 30.f;
    const std::string title = "SFML Shape Resizer";
    const sf::Color backgroundColor = sf::Color::Black;
    const sf::Color shapeColor = sf::Color::Green;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(width, height), title);

    // Vector to store multiple circles
    std::vector<sf::CircleShape> shapes;

    // Initialize the first shape
    shapes.push_back(sf::CircleShape(circleRadius));
    shapes.back().setPosition(100.f, 100.f);
    shapes.back().setFillColor(shapeColor);

    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed){
          window.close();
        }

        // Mouse click event
        if (event.type == sf::Event::MouseButtonPressed) {
          if (event.mouseButton.button == sf::Mouse::Left) {
            
            // Ensure the circle fits within the window boundaries
            float mouseX = static_cast<float>(event.mouseButton.x);
            float mouseY = static_cast<float>(event.mouseButton.y);

            // Adjust position to keep the shape fully within bounds
            if (mouseX + circleRadius > width) mouseX = width - circleRadius;
            if (mouseX - circleRadius < 0) mouseX = circleRadius;
            if (mouseY + circleRadius > height) mouseY = height - circleRadius;
            if (mouseY - circleRadius < 0) mouseY = circleRadius;

            // Add a new shape at the adjusted position
            sf::CircleShape newShape(circleRadius);
            newShape.setFillColor(shapeColor);
            newShape.setPosition(mouseX - circleRadius, mouseY - circleRadius); // Center the shape
            shapes.push_back(newShape);

            std::cout << "Added shape at: (" << mouseX << ", " << mouseY << ")\n";
          } 
          else if (event.mouseButton.button == sf::Mouse::Right) {
            // Remove the last shape if right-clicked
            if (!shapes.empty()) {
              shapes.pop_back();
              std::cout << "Removed the last shape.\n";
            }
          }
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
          window.close();
        }
      }

      // Clear and render all shapes
      window.clear(backgroundColor);
      for (const auto& shape : shapes) {
        window.draw(shape);
      }
      window.display();
    }
  }  
} // namespace it_5




