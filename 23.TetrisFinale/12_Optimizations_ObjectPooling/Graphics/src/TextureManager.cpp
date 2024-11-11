#include "TextureManager.hpp"

TextureManager& TextureManager::getInstance() {
  static TextureManager instance;
  return instance;
}

bool TextureManager::loadTexture(const std::string& name, const std::string& filename) {
  sf::Texture texture;
  if (!texture.loadFromFile(filename)) {
    return false;
  }
  m_textures[name] = texture;
  return true;
}

sf::Texture* TextureManager::getTexture(const std::string& name) {
  auto it = m_textures.find(name);
  if (it != m_textures.end()) {
    return &it->second;
  }
  return nullptr;
}

bool TextureManager::loadFont(const std::string& name, const std::string& filename) {
  sf::Texture font;
  if (!font.loadFromFile(filename)) {
    return false;
  }
  m_fonts[name] = font;
  return true;
}

sf::Texture* TextureManager::getFont(const std::string& name) {
  auto it = m_fonts.find(name);
  if (it != m_fonts.end()) {
    return &it->second;
  }
  return nullptr;
}

void TextureManager::drawText(const std::string& text, unsigned short x, unsigned short y, sf::RenderWindow& window) {
  sf::Texture* fontTexture = getFont("default");
  if (!fontTexture) return;

  unsigned char characterWidth = fontTexture->getSize().x / 96;
  sf::Sprite characterSprite(*fontTexture);

  for (const char a : text) {
    if (a == '\n') {
      x = x;  // Reset to initial x position
      y += fontTexture->getSize().y;
      continue;
    }

    characterSprite.setPosition(x, y);
    characterSprite.setTextureRect(sf::IntRect(characterWidth * (a - 32), 0, characterWidth, fontTexture->getSize().y));
    window.draw(characterSprite);

    x += characterWidth;
  }
}