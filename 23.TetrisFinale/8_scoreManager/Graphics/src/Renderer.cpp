#include "Renderer.hpp"

Renderer::Renderer(sf::RenderWindow &window) : m_window(window) {}

void Renderer::beginDraw() { m_window.clear(sf::Color::Black); }

void Renderer::draw(const Entity &entity) { entity.draw(m_window); }

void Renderer::endDraw() { m_window.display(); }

void Renderer::setView(const Camera &camera) { m_window.setView(camera.getView()); }