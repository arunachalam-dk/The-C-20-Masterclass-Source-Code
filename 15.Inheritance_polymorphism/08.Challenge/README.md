# TetrisSFML
Tetris Game using SFML

## Step 1. *Create a valid CMake project*

This step lays the foundation for your Tetris game project by setting up a proper build system and project structure.

1. **Set up vcpkg for dependency management:**
    - Install vcpkg if you haven't already (https://github.com/Microsoft/vcpkg)
    - Initialize vcpkg in your project directory or use a system-wide installation
   ```bash
   cd vcpkg && ./vcpkg integrate install
   ```
    - Create a `vcpkg.json` file in your project root to specify dependencies:

   ```json
   {
     "dependencies": [
       "sfml",
       "fmt"
     ]
   }
   ```

2. **Create the directory structure:**
   Create the following directories in your project root:
    - `Core`: For game logic independent of graphics
    - `Entity`: For game component classes
    - `Graphics`: For SFML-related rendering code

3. **Create CMakeLists.txt:**
   In the project root, create a `CMakeLists.txt` file with the following content:

   ```cmake
    cmake_minimum_required(VERSION 3.28)
    
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
    
    project(
    TetrisSFML
    VERSION 0.0.1
    DESCRIPTION "Tetris Game using SFML"
    LANGUAGES CXX C)
    
    set(CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_STANDARD 23)
    
    find_package(fmt CONFIG REQUIRED)
    find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
   ```

4. **Create CMakePresets.json:**
   This file helps configure CMake for different build types and environments:


## Step 2: Create the Game class and set up the main game loop

In this step, we create the basic structure for our Tetris game by implementing a `Game` class and setting up the main entry point. This lays the foundation for the game loop and window management.

1. **Create `main.cpp`:**
   In the project root, create `main.cpp` with the following content:

   ```c++
   #include "Game.hpp"

   int main()
   {
     Game game;
     game.run();
   }
   ```

   This file serves as the entry point for our application. It creates an instance of the `Game` class and calls its `run()` method to start the game loop.

2. **Create `Game.hpp`:**
   In the project root, create `Game.hpp` with the following content:

   ```c++
   #pragma once
   #include <SFML/Graphics.hpp>

   class Game {
   public:
     Game();
     void run();

   private:
     sf::RenderWindow m_window;
   };
   ```

   This header file declares the `Game` class:
   - The constructor initializes the game.
   - The `run()` method contains the main game loop.
   - We have a private member `m_window` of type `sf::RenderWindow` to manage the game window.

3. **Create `Game.cpp`:**
   In the project root, create `Game.cpp` with the following content:

   ```c++
   #include "Game.hpp"

   Game::Game()
       : m_window(sf::VideoMode(800, 600), "TetrisSFML")
   {}

   void Game::run() {
     while (m_window.isOpen()) {
       // Main game loop will be implemented here
     }
   }
   ```

   This implementation file defines the `Game` class methods:
   - The constructor initializes the SFML window with a size of 800x600 pixels and the title "TetrisSFML".
   - The `run()` method sets up a basic game loop that continues as long as the window is open.

4. **Update `CMakeLists.txt`:**
   Modify the `CMakeLists.txt` in the project root to include the new files:

   ```cmake
   cmake_minimum_required(VERSION 3.28)

   set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

   project(
           TetrisSFML
           VERSION 0.0.1
           DESCRIPTION "Tetris Game using SFML"
           LANGUAGES CXX C)

   set(CXX_STANDARD_REQUIRED ON)
   set(CMAKE_CXX_STANDARD 23)

   find_package(fmt CONFIG REQUIRED)
   find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

   add_executable(${PROJECT_NAME}
           main.cpp
           Game.cpp
   )

   target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
   ```

   This updated `CMakeLists.txt` file:
   - Adds `main.cpp` and `Game.cpp` to the project's source files.
   - Links the SFML graphics library to our project.

5. **Build and Run:**
   - Create a build directory: `mkdir build && cd build`
   - Configure the project: `cmake ..`
   - Build the project: `cmake --build .`
   - Run the executable: `./TetrisSFML` (or `TetrisSFML.exe` on Windows)

   At this point, running the game should open an empty window titled "TetrisSFML".

- Noted issue:
   - Trouble closing the window - cause: our window does not recognize key presses
   - ... Let's fix that

### Step 2a: Implement event handling for window closure and key presses

In this step, we address the noted issue of the window not responding to key presses, which made it difficult to close. We'll implement proper event handling to make our game window responsive.

1. **Update `Game.hpp`:**
   Modify the `Game.hpp` file to include new private methods for event handling:

   ```c++
   #pragma once
   #include <SFML/Graphics.hpp>

   class Game {
   public:
     Game();
     void run();

   private:
     void processEvents();
     void handleKeyPress(sf::Keyboard::Key key);

     sf::RenderWindow m_window;
   };
   ```

   New additions:
   - `processEvents()`: A method to handle all window events.
   - `handleKeyPress(sf::Keyboard::Key key)`: A method specifically for handling key press events.

2. **Update `Game.cpp`:**
   Modify the `Game.cpp` file to implement the new methods:

   ```c++
   #include "Game.hpp"

   Game::Game()
       : m_window(sf::VideoMode(800, 600), "TetrisSFML")
   {}

   void Game::run()
   {
     while (m_window.isOpen()) {
       processEvents();
     }
   }

   void Game::processEvents()
   {
     sf::Event event;
     while (m_window.pollEvent(event)) {
       if (event.type == sf::Event::Closed) {
         m_window.close();
       } else if (event.type == sf::Event::KeyPressed) {
         handleKeyPress(event.key.code);
       }
     }
   }

   void Game::handleKeyPress(sf::Keyboard::Key key)
   {
     // TODO - Handle key presses
   }
   ```

   Changes and additions:
   - The `run()` method now calls `processEvents()` in each iteration of the game loop.
   - `processEvents()` method:
      - Uses `m_window.pollEvent(event)` to check for pending events.
      - Handles the window close event by calling `m_window.close()` when the close button is clicked.
      - Delegates key press events to the `handleKeyPress()` method.
   - `handleKeyPress()` method is added as a placeholder for future key press handling logic.

3. **Explanation of the changes:**
   - Event Polling: The `processEvents()` method continually checks for new events using a while loop. This ensures that all queued events are processed in each frame.
   - Window Closure: When the close button is clicked, it generates a `sf::Event::Closed` event, which we now handle by calling `m_window.close()`.
   - Key Press Handling: All key press events are now captured. While we don't have specific actions yet, the `handleKeyPress()` method provides a clear place to implement game controls in the future.

4. **Benefits of these changes:**
   - Responsiveness: The window now properly responds to the close button, allowing users to exit the game.
   - Extensibility: The `handleKeyPress()` method provides a foundation for implementing game controls (e.g., moving Tetris pieces, rotating them, etc.) in future steps.
   - Improved Structure: By separating event handling into its own method, we've improved the organization of our game loop, making it easier to manage and extend as the game grows more complex.


## Step 3: Implementing Board Rendering in Tetris

In this step, we'll create the necessary components to render the Tetris game board. We'll break this down into several key areas:

### Conceptual Overview

1. **Separation of Concerns**
   We're implementing a clear separation between the game's logic and its visual representation. This separation allows us to modify either part independently, making the code more maintainable and flexible.

2. **Core Game Logic**
   At the heart of our game is the concept of a "Board". This is purely logical - it doesn't know anything about how it will be displayed. It's essentially a grid that keeps track of which cells are occupied and by what type of block.

3. **Visual Representation**
   We then create a visual counterpart to our logical Board. This "BoardEntity" knows how to take the state of a Board and render it on the screen. It translates the logical grid into a grid of colored rectangles.

4. **Rendering System**
   To manage the complexities of drawing to the screen, we're implementing a simple rendering system. This system handles the mechanics of when to draw and provides a consistent interface for drawing game objects.

5. **Camera System**
   While perhaps overkill for a simple Tetris game, we're including a basic camera system. This gives us flexibility for future enhancements, like zooming or panning the view.

6. **Tying it All Together**
   Our main Game class acts as the conductor, coordinating between these different systems. It maintains the game state, tells the renderer when to draw, and manages the main game loop.

### Implementation Strategy

1. We start by defining our Board class. This is a simple grid structure that can tell us what's in each cell.

2. We then create a GameState class that holds our Board. In the future, this will also manage other game state like score, current piece, etc.

3. Next, we define our visual elements. We create a generic Entity class as a base for all visual objects in our game. Our BoardEntity inherits from this and knows how to render a Board.

4. We implement a simple Renderer class that manages the drawing process. This abstracts away the details of SFML's drawing system and provides a clean interface for our game objects.

5. We add a Camera class to manage the view of our game world. For now, it's very simple, but it allows for future expansion.

6. Finally, we update our Game class to use all these new components. It creates instances of GameState, BoardEntity, Renderer, and Camera, and coordinates between them in the main game loop.

### Key Concepts

- **Encapsulation**: Each class has a specific responsibility and hides its implementation details.
- **Abstraction**: The Entity and Renderer classes provide abstract interfaces for game objects and rendering.
- **Separation of Logic and Presentation**: The Board class represents the game state, while BoardEntity handles its visual representation.
- **Extensibility**: This structure allows for easy addition of new features, like different game pieces or UI elements.

### 1. Core Game Logic

First, we'll establish the core game logic:

1. Create a `Board` class:
   - Define constants for board dimensions (e.g., 10x20 grid).
   - Implement a 2D vector to represent the game grid.
   - Add a method to access the grid state.

2. Create a `GameState` class:
   - This will hold the current state of the game, including the board.
   - For now, it just contains a `Board` instance.

These classes form the backbone of our game logic, separate from any graphical representation.

### 2. Entity Representation

Next, we'll create the visual representation of our game elements:

1. Create a base `Entity` class:
   - This will be an abstract class for all game objects.
   - Include virtual methods for updating and drawing.
   - Implement basic position management.

2. Create a `BoardEntity` class (inherits from `Entity`):
   - This class will visually represent our game board.
   - Create a grid of SFML `RectangleShape` objects to represent each cell.
   - Implement a method to update the visual state based on the logical `Board` state.
   - Override the draw method to render the board.

The `BoardEntity` acts as a bridge between our logical game state and its visual representation.

### 3. Graphics System

Now, let's set up our rendering system:

1. Create a `Camera` class:
   - This will manage the game's view.
   - For now, it's a simple wrapper around SFML's `View` class.

2. Create a `Renderer` class:
   - This class will handle the drawing process.
   - Include methods for beginning and ending the draw process.
   - Add a method to draw entities.

These classes provide a flexible system for managing how we view and render our game world.

### 4. Putting It All Together

Finally, we'll update our `Game` class to use these new components:

1. Add member variables for:
   - `GameState`
   - `BoardEntity`
   - `Renderer`
   - `Camera`

2. In the constructor:
   - Initialize these new components.
   - Set up the game window and camera.

3. Update the game loop:
   - Add a `render` method to handle drawing.
   - Call `processEvents`, then `render` in each frame.

4. In the `render` method:
   - Use the `Renderer` to draw the `BoardEntity`.

5. Add an `initializeGame` method:
   - Set up initial game state.
   - Position the board entity within the game window.

### 5. Building and Testing

After implementing these components:

1. Update CMakeLists.txt files to include new source files and dependencies.
2. Build the project and run it.
3. You should now see a grid representing the Tetris board rendered in the game window.

![window_grid.png](docs/window_grid.png)
