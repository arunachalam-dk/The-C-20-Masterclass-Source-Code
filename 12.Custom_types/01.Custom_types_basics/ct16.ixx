/*
    . Add serialization to binary file for Pixel class
    . Flexes our muscles with file I/O
    . This approach works, but is not the best
        . reinterpret_cast is dangerous
        . RECOMENDATION: 
            . Use specialized file I/O Libraries for serialization tasks like these.
*/
module;

#include <cstdint>
#include <filesystem>
#include <memory>
#include <fmt/format.h>
#include <fstream>
#include <vector>

export module ct16;

namespace ct16{
      // Position struct definition
    export struct Position {
        unsigned int x{0};
        unsigned int y{0};

        Position() = default;
        Position(unsigned int x, unsigned int y) : x(x), y(y) {}
    };

    // Pixel class definition
    export class Pixel {
    public:
        Pixel() = default;
        Pixel(uint32_t color, unsigned int x, unsigned int y)
            : m_color(color), m_pos(x, y) {}

        uint32_t get_color() const { return m_color; }
        const Position& get_position() const { return m_pos; }

        void set_color(uint32_t color) { m_color = color; }
        void set_position(unsigned int x, unsigned int y) {
            m_pos.x = x;
            m_pos.y = y;
        }

        void serialize(std::ofstream& out) const {
            out.write(reinterpret_cast<const char*>(&m_color), sizeof(m_color));
            out.write(reinterpret_cast<const char*>(&m_pos.x), sizeof(m_pos.x));
            out.write(reinterpret_cast<const char*>(&m_pos.y), sizeof(m_pos.y));
        }

        void deserialize(std::ifstream& in) {
            in.read(reinterpret_cast<char*>(&m_color), sizeof(m_color));
            in.read(reinterpret_cast<char*>(&m_pos.x), sizeof(m_pos.x));
            in.read(reinterpret_cast<char*>(&m_pos.y), sizeof(m_pos.y));
        }

    private:
        uint32_t m_color{0xFF000000};
        Position m_pos; // Now directly embedded, no heap allocation
    };

    export void save_pixels(const std::vector<Pixel>& pixels, const std::filesystem::path& filepath) {
        std::ofstream out(filepath, std::ios::binary);
        if (!out) {
            fmt::println("Error opening file for writing: {}", filepath.string());
            return;
        }
        for (const auto& pixel : pixels) {
            pixel.serialize(out);
        }
    }

    export std::vector<Pixel> load_pixels(const std::filesystem::path& filepath) {
        std::vector<Pixel> pixels;
        std::ifstream in(filepath, std::ios::binary);
        if (!in) {
            fmt::println("Error opening file for reading: {}", filepath.string());
            return pixels;
        }
        while (true) {
            Pixel temp;
            temp.deserialize(in);
            if (in.eof()) break;
            pixels.push_back(temp);
        }
        return pixels;
    }  
} // namespace ct16