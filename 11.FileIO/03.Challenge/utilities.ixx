/*
    . Contact manager application using ftxui
        . adding contacts
        . deleting contacts
        . listing contacts
        . persisting contacts to a file
            . can read and write contacts to a file
*/

module;
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <filesystem>

#include <ftxui/dom/elements.hpp>       // for text, Element, hbox, vbox, border
#include <ftxui/screen/screen.hpp>      // for Screen
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/component/component.hpp>



export module utilities; 


namespace it_1{
    namespace fs = std::filesystem;
    using namespace ftxui;

    // File path for storing contacts
    const fs::path contacts_file = R"(D:\contacts.txt)";

    // On Linux, it could be something like:
    // const fs::path contacts_file = "/home/user/contacts.txt";

    // Ensure the contacts file exists
    void ensure_file_exists() {
        if (!fs::exists(contacts_file)) {
            std::ofstream file(contacts_file); // Creates the file if it doesn't exist
        }
    }

    // Load contacts from file
    std::vector<std::string> load_contacts() {
        std::vector<std::string> contacts;
        if (fs::exists(contacts_file)) {
            std::ifstream file(contacts_file);
            std::string line;
            while (std::getline(file, line)) {
                contacts.push_back(line);
            }
        }
        return contacts;
    }

    // Save contacts back to file
    void save_contacts(const std::vector<std::string>& contacts) {
        if (fs::exists(contacts_file)) {
            std::ofstream file(contacts_file);
            for (const auto& contact : contacts) {
                file << contact << '\n';
            }
        }
    }

    // Add a new contact to the file
    void add_contact(const std::string& name, const std::string& phone) {
        if (fs::exists(contacts_file)) {
            std::ofstream file(contacts_file, std::ios::app);
            file << name << ":" << phone << '\n';
        }
    }

    // Delete a contact by index
    void delete_contact(int index) {
        auto contacts = load_contacts();
        if (index >= 0 && index < contacts.size()) {
            contacts.erase(contacts.begin() + index);
            save_contacts(contacts);
        }
    }

    // Main application
    export void app() {
        // Ensure contacts file exists before application runs
        ensure_file_exists();

        auto screen = ScreenInteractive::TerminalOutput();

        // Load contacts
        std::vector<std::string> contacts = load_contacts();
        int selected = 0;  // Initially selected item index

        // Input fields for name and phone
        std::string name_input;
        std::string phone_input;
        auto name_input_box = Input(&name_input, "Enter name");
        auto phone_input_box = Input(&phone_input, "Enter phone");

        // Display contacts in a list
        auto display_contacts = Menu(&contacts, &selected);

        // Button to add contact
        auto add_button = Button("Add Contact", [&] {
            if (!name_input.empty() && !phone_input.empty()) {
                add_contact(name_input, phone_input);
                contacts = load_contacts();  // Reload contacts to update display
                name_input.clear();
                phone_input.clear();
            }
        });

        // Button to delete the selected contact
        auto delete_button = Button("Delete Contact", [&] {
            if (!contacts.empty() && selected >= 0) {
                delete_contact(selected);
                contacts = load_contacts();  // Reload contacts to update display
                selected = 0;
            }
        });

        // Create the layout container
        auto layout = Container::Vertical({
            name_input_box,
            phone_input_box,
            add_button,
            delete_button,
            display_contacts,
        });

        // Render the layout with elements
        auto renderer = Renderer(layout, [&] {
            return vbox({
                text("Contact Manager") | bold | center,
                separator(),
                hbox(text("Name: "), name_input_box->Render()),
                hbox(text("Phone: "), phone_input_box->Render()),
                hbox({
                    add_button->Render() | color(Color::Green),
                    delete_button->Render() | color(Color::Red),
                }) | center,
                separator(),
                text("Contacts:") | bold,
                display_contacts->Render(),
            }) | border;
        });

        // Run the application
        screen.Loop(renderer);

        return;
    } 

} // namespace it_1
