#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager {
public:
  static TextureManager& getInstance();
  bool loadTexture(const std::string& name, const std::string& filename);
  sf::Texture* getTexture(const std::string& name);
  bool loadFont(const std::string& name, const std::string& filename);
  sf::Texture* getFont(const std::string& name);
  void drawText(const std::string& text, unsigned short x, unsigned short y, sf::RenderWindow& window);

private:
  TextureManager() = default;
  std::unordered_map<std::string, sf::Texture> m_textures;
  std::unordered_map<std::string, sf::Texture> m_fonts;
};
