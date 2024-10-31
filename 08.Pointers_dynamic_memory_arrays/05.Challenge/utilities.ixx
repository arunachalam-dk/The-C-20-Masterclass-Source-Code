/*
    . FTXUI Overview
        . FTXUI is a library for creating user interfaces in the terminal, focusing on ease of use and interactivity.
        . Layouts
            . Containers:
                . Use ftxui::Container to organize components into various layouts (e.g., horizontal, vertical).
                . Containers hold child components and define their arrangement in the UI.
        . Layout Definition:
            . Layouts are defined separately from rendering logic to enhance code organization.
            . Example: auto buttons_layout = ftxui::Container::Horizontal({ button1, button2, button3 });
        . Renderer
            . Renderer Functionality:
                . The ftxui::Renderer wraps around a layout and provides the logic to render UI components dynamically.
                . Allows for responsive updates based on user interaction and changing application state.
        . Rendering Logic:
            . Within the renderer, you can customize how components are displayed, including combining different UI elements and applying styles.
            . Example: auto renderer = ftxui::Renderer(buttons_layout, [&]() { ... });
        . Screen Object
            . Interactive Screen:
            . ftxui::ScreenInteractive enables the creation of interactive terminal applications, handling user input and updates to the display.
            . Initialized with FitComponent() to adapt the size of the screen to fit the UI components.
        . Rendering Loop:
            . The Loop() method on the ScreenInteractive object runs a continuous loop, managing input and rendering the UI.
            . Allows the application to respond to user actions and redraw the interface in real-time.
        . General Advantages
            .Separation of Concerns:
                . Clear distinction between layout definition and rendering logic improves code readability and maintainability.
            . Dynamic Updates:
                . Layouts and rendering logic can be updated independently, allowing for responsive interfaces based on user input.
            . Code Reusability:
                . Layouts can be reused across different renderers, promoting modular design and reducing code duplication.    
*/
module;

#include <ftxui/component/component.hpp> // for Button, Horizontal, Renderer, etc.
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp> // for text, gauge, hbox, etc.

export module utilities; 

namespace it_1{
    export void app(){
        int progress = 0;

            // Define three buttons
            auto button1 = ftxui::Button("Add 10", [&]() { progress += 10; });
            auto button2 = ftxui::Button("Add 20", [&]() { progress += 20; });
            auto button3 = ftxui::Button("Reset", [&]() { progress = 0; }); // Reset progress

            // Create a horizontal layout for the buttons
            auto buttons_layout = ftxui::Container::Horizontal({
                button1,
                button2,
                button3,
            });

            // Create a renderer to display the buttons and progress bar
            auto renderer = ftxui::Renderer(buttons_layout, [&]() {
                return ftxui::vbox({
                    ftxui::hbox({
                        button1->Render(),
                        button2->Render(),
                        button3->Render(),
                    }),
                    ftxui::text("Progress:") | ftxui::bold,
                    ftxui::gauge(progress / 100.0f), // Progress bar
                    ftxui::filler(),
                });
            });

            // Create an interactive screen
            auto screen = ftxui::ScreenInteractive::FitComponent();
            screen.Loop(renderer); // This triggers the event loop.
    }
}