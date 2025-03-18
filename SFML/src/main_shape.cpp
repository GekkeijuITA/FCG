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
    window.setFramerateLimit(60);

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

        sf::CircleShape circle(50.f);
        circle.setFillColor(sf::Color::Red);
        circle.setScale({2.f, 2.f});
        circle.setPosition({400.f, 300.f});
        circle.rotate(sf::degrees(180));
        // std::cout << "BBox: (" << s.getGlobalBounds().position.x << ", "
        //           << s.getGlobalBounds().position.y << ", "
        //           << s.getGlobalBounds().size.x << ", "
        //           << s.getGlobalBounds().size.y << ")\n";
        window.draw(circle);

        circle.setOrigin({circle.getRadius(), circle.getRadius()});
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition({400.f, 300.f});
        window.draw(circle);
        circle.setPosition({200.f, 200.f});
        circle.setRadius(30.f);
        circle.setPointCount(3);
        window.draw(circle);
        circle.setPosition({100.f, 500.f});
        circle.setPointCount(4);
        circle.setFillColor(sf::Color::Green);
        circle.rotate(sf::degrees(45));
        window.draw(circle);
        window.display();
    }
}
