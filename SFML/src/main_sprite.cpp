////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <math.h>
#include <iostream>

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CMake SFML Project", sf::Style::Default, sf::State::Windowed, settings);
    // window.setFramerateLimit(30);
    sf::Texture texture("../resources/1856-51_stone-texture-wall-charcoal-color.jpg");

    while (window.isOpen()) // main loop
    {
        while (const std::optional event = window.pollEvent())
        { // event loop + hevent handler
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                break;
            }
        }
        // Do graphics
        window.clear();

        sf::Sprite sprite(texture);
        sprite.setTextureRect(sf::IntRect({300, 200}, {500, 300}));
        sprite.setPosition({200.f, 100.f});
        sprite.scale({0.5f, 0.5f});
        sprite.setColor(sf::Color::Red);
        sprite.rotate(sf::degrees(60));
        window.draw(sprite);

        window.display();
    }
}
