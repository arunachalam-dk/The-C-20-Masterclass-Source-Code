module;

#include <ftxui/component/component.hpp> // for Button, Horizontal, Renderer, etc.
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp> // for text, gauge, hbox, etc.

export module utilities1;

namespace it_2 {


    export void app() {
        using namespace ftxui;

        // Create UI elements
        auto document = vbox({
            text("Hello, FTXUI!") | bold,
            text("This is a starter tutorial."),
        });

        // Create a screen and display the UI
        auto screen = ScreenInteractive::Fullscreen();
        screen.Loop(Renderer([&] { return document; }));
        
    }
}
