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
    window.setFramerateLimit(30);

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

        float sqrt32 = sqrt(3.f) / 2.f;
        sf::ConvexShape s(6);
        s.setPoint(0, {sqrt32, -0.5f});
        s.setPoint(1, {0.f, -1.f});
        s.setPoint(2, {-sqrt32, -0.5f});
        s.setPoint(3, {-sqrt32, 0.5f});
        s.setPoint(4, {0.f, 1.f});
        s.setPoint(5, {sqrt32, 0.5f});
        // s.setFillColor(sf::Color::Green);
        s.setScale({200.f, 200.f});
        s.setPosition({400.f, 300.f});
        s.setTexture(&texture);
        s.setTextureRect(sf::IntRect({0, 0}, {(int)(sqrt32 * 2000), 2000}));
        // std::cout << "BBox: (" << s.getGlobalBounds().position.x << ", "
        //           << s.getGlobalBounds().position.y << ", "
        //           << s.getGlobalBounds().size.x << ", "
        //           << s.getGlobalBounds().size.y << ")\n";
        window.draw(s);
        window.display();
    }
}
