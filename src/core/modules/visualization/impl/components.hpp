#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

namespace core::modules::visualization::impl {

struct SfmlWindowInit {};

struct SfmlWindow {
  sf::RenderWindow window;

};

}
