#include "Camera.hpp"

Camera::Camera(float width, float height) : m_view(sf::FloatRect(0, 0, width, height)) {}


const sf::View &Camera::getView() const { return m_view; }